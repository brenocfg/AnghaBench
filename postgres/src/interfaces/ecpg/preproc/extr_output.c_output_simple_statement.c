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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  output_escaped_str (char*,int) ; 
 int /*<<< orphan*/  output_line_number () ; 
 int /*<<< orphan*/  whenever_action (int) ; 

void
output_simple_statement(char *stmt, int whenever_mode)
{
	output_escaped_str(stmt, false);
	if (whenever_mode)
		whenever_action(whenever_mode);
	output_line_number();
	free(stmt);
}