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
 int /*<<< orphan*/  puts (char*) ; 

void
print_copyright(void)
{
	puts(
		 "PostgreSQL Database Management System\n"
		 "(formerly known as Postgres, then as Postgres95)\n\n"
		 "Portions Copyright (c) 1996-2019, PostgreSQL Global Development Group\n\n"
		 "Portions Copyright (c) 1994, The Regents of the University of California\n\n"
		 "Permission to use, copy, modify, and distribute this software and its\n"
		 "documentation for any purpose, without fee, and without a written agreement\n"
		 "is hereby granted, provided that the above copyright notice and this\n"
		 "paragraph and the following two paragraphs appear in all copies.\n\n"
		 "IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR\n"
		 "DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING\n"
		 "LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS\n"
		 "DOCUMENTATION, EVEN IF THE UNIVERSITY OF CALIFORNIA HAS BEEN ADVISED OF THE\n"
		 "POSSIBILITY OF SUCH DAMAGE.\n\n"
		 "THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,\n"
		 "INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY\n"
		 "AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS\n"
		 "ON AN \"AS IS\" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATIONS TO\n"
		 "PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.\n"
		);
}