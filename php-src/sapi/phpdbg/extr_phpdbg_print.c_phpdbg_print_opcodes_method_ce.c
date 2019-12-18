#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_function ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__* name; int /*<<< orphan*/  function_table; } ;
typedef  TYPE_2__ zend_class_entry ;
struct TYPE_4__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 scalar_t__ ZEND_USER_CLASS ; 
 int /*<<< orphan*/  phpdbg_out (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  phpdbg_print_function_helper (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/ * zend_hash_str_find_ptr (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phpdbg_print_opcodes_method_ce(zend_class_entry *ce, const char *function) {
	zend_function *func;

	if (ce->type != ZEND_USER_CLASS) {
		phpdbg_out("function name: %s::%s (internal)\n", ce->name->val, function);
		return;
	}

	if (!(func = zend_hash_str_find_ptr(&ce->function_table, function, strlen(function)))) {
		return;
	}

	phpdbg_out("function name: %s::%s\n", ce->name->val, function);
	phpdbg_print_function_helper(func);
}