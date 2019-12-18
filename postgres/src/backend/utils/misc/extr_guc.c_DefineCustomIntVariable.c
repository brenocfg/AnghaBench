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
struct config_int {int* variable; int boot_val; int reset_val; int min; int max; int /*<<< orphan*/  gen; int /*<<< orphan*/  show_hook; int /*<<< orphan*/  assign_hook; int /*<<< orphan*/  check_hook; } ;
typedef  int /*<<< orphan*/  GucShowHook ;
typedef  int /*<<< orphan*/  GucIntCheckHook ;
typedef  int /*<<< orphan*/  GucIntAssignHook ;
typedef  int /*<<< orphan*/  GucContext ;

/* Variables and functions */
 int /*<<< orphan*/  PGC_INT ; 
 int /*<<< orphan*/  define_custom_variable (int /*<<< orphan*/ *) ; 
 scalar_t__ init_custom_variable (char const*,char const*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void
DefineCustomIntVariable(const char *name,
						const char *short_desc,
						const char *long_desc,
						int *valueAddr,
						int bootValue,
						int minValue,
						int maxValue,
						GucContext context,
						int flags,
						GucIntCheckHook check_hook,
						GucIntAssignHook assign_hook,
						GucShowHook show_hook)
{
	struct config_int *var;

	var = (struct config_int *)
		init_custom_variable(name, short_desc, long_desc, context, flags,
							 PGC_INT, sizeof(struct config_int));
	var->variable = valueAddr;
	var->boot_val = bootValue;
	var->reset_val = bootValue;
	var->min = minValue;
	var->max = maxValue;
	var->check_hook = check_hook;
	var->assign_hook = assign_hook;
	var->show_hook = show_hook;
	define_custom_variable(&var->gen);
}