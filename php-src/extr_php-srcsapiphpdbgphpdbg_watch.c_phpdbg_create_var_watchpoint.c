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
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  phpdbg_create_simple_watchpoint ; 
 scalar_t__ phpdbg_rebuild_symtable () ; 
 int phpdbg_watchpoint_parse_symtables (char*,size_t,int /*<<< orphan*/ ) ; 

int phpdbg_create_var_watchpoint(char *input, size_t len) {
	if (phpdbg_rebuild_symtable() == FAILURE) {
		return FAILURE;
	}

	return phpdbg_watchpoint_parse_symtables(input, len, phpdbg_create_simple_watchpoint);
}