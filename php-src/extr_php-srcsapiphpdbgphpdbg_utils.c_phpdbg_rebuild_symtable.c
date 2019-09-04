#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 TYPE_1__* EG (int /*<<< orphan*/ ) ; 
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  current_execute_data ; 
 int /*<<< orphan*/  phpdbg_error (char*,char*,char*) ; 
 int /*<<< orphan*/  zend_rebuild_symbol_table () ; 

int phpdbg_rebuild_symtable(void) {
	if (!EG(current_execute_data) || !EG(current_execute_data)->func) {
		phpdbg_error("inactive", "type=\"op_array\"", "No active op array!");
		return FAILURE;
	}

	if (!zend_rebuild_symbol_table()) {
		phpdbg_error("inactive", "type=\"symbol_table\"", "No active symbol table!");
		return FAILURE;
	}

	return SUCCESS;
}