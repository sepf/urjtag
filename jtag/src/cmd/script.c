/*
 * $Id$
 *
 * Copyright (C) 2003 ETC s.r.o.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * Written by Marcel Telka <marcel@telka.sk>, 2003.
 *
 */

#include "sysdep.h"

#include <stdio.h>

#include "jtag.h"

#include "cmd.h"

static int
cmd_script_run( char *params[] )
{
int i,j;

	int go;
	i = 0; j = 1;
	if (cmd_params( params ) == 3) {
		sscanf(params[2],"%d",&j);	/* loop n times option */
	}
	else if (cmd_params( params ) != 2)
		return -1;

	for(i=0;i<j;i++) {
		go = jtag_parse_file( params[1] );

		if (go < 0) {
			if(go != -99)printf( _("Unable to open file `%s go=%s'!\n"), params[1], go );
			break;
		}
	}
	if(debug_mode & 1)printf("Return at cmd_script_run\n");
	return go ? 1 : 0;
}

static void
cmd_script_help( void )
{
	printf( _(
		"Usage: %s FILENAME [n] \n"
		"Run command sequence n times from external FILENAME.\n"
		"\n"
		"FILENAME      Name of the file with commands\n"
	), "script" );
}

cmd_t cmd_script = {
	"script",
	N_("run command sequence from external file"),
	cmd_script_help,
	cmd_script_run
};
