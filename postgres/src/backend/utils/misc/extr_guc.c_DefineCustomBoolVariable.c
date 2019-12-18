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
struct config_bool {int* variable; int boot_val; int reset_val; int /*<<< orphan*/  gen; int /*<<< orphan*/  show_hook; int /*<<< orphan*/  assign_hook; int /*<<< orphan*/  check_hook; } ;
typedef  int /*<<< orphan*/  GucShowHook ;
typedef  int /*<<< orphan*/  GucContext ;
typedef  int /*<<< orphan*/  GucBoolCheckHook ;
typedef  int /*<<< orphan*/  GucBoolAssignHook ;

/* Variables and functions */
 int /*<<< orphan*/  PGC_BOOL ; 
 int /*<<< orphan*/  define_custom_variable (int /*<<< orphan*/ *) ; 
 scalar_t__ init_custom_variable (char const*,char const*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void
DefineCustomBoolVariable(const char *name,
						 const char *short_desc,
						 const char *long_desc,
						 bool *valueAddr,
						 bool bootValue,
						 GucContext context,
						 int flags,
						 GucBoolCheckHook check_hook,
						 GucBoolAssignHook assign_hook,
						 GucShowHook show_hook)
{
	struct config_bool *var;

	var = (struct config_bool *)
		init_custom_variable(name, short_desc, long_desc, context, flags,
							 PGC_BOOL, sizeof(struct config_bool));
	var->variable = valueAddr;
	var->boot_val = bootValue;
	var->reset_val = bootValue;
	var->check_hook = check_hook;
	var->assign_hook = assign_hook;
	var->show_hook = show_hook;
	define_custom_variable(&var->gen);
}