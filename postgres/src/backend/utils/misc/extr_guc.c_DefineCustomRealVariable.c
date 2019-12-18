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
struct config_real {double* variable; double boot_val; double reset_val; double min; double max; int /*<<< orphan*/  gen; int /*<<< orphan*/  show_hook; int /*<<< orphan*/  assign_hook; int /*<<< orphan*/  check_hook; } ;
typedef  int /*<<< orphan*/  GucShowHook ;
typedef  int /*<<< orphan*/  GucRealCheckHook ;
typedef  int /*<<< orphan*/  GucRealAssignHook ;
typedef  int /*<<< orphan*/  GucContext ;

/* Variables and functions */
 int /*<<< orphan*/  PGC_REAL ; 
 int /*<<< orphan*/  define_custom_variable (int /*<<< orphan*/ *) ; 
 scalar_t__ init_custom_variable (char const*,char const*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void
DefineCustomRealVariable(const char *name,
						 const char *short_desc,
						 const char *long_desc,
						 double *valueAddr,
						 double bootValue,
						 double minValue,
						 double maxValue,
						 GucContext context,
						 int flags,
						 GucRealCheckHook check_hook,
						 GucRealAssignHook assign_hook,
						 GucShowHook show_hook)
{
	struct config_real *var;

	var = (struct config_real *)
		init_custom_variable(name, short_desc, long_desc, context, flags,
							 PGC_REAL, sizeof(struct config_real));
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