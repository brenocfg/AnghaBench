#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

void acado_printHeader( )
{
	printf(
		"\nACADO Toolkit -- A Toolkit for Automatic Control and Dynamic Optimization.\n"
		"Copyright (C) 2008-2015 by Boris Houska, Hans Joachim Ferreau,\n" 
		"Milan Vukov and Rien Quirynen, KU Leuven.\n"
	);
	
	printf(
		"Developed within the Optimization in Engineering Center (OPTEC) under\n"
		"supervision of Moritz Diehl. All rights reserved.\n\n"
		"ACADO Toolkit is distributed under the terms of the GNU Lesser\n"
		"General Public License 3 in the hope that it will be useful,\n"
		"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n"
		"GNU Lesser General Public License for more details.\n\n"
	);
}