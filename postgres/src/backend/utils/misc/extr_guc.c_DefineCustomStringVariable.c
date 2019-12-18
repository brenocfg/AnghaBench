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
struct config_string {char** variable; char const* boot_val; int /*<<< orphan*/  gen; int /*<<< orphan*/  show_hook; int /*<<< orphan*/  assign_hook; int /*<<< orphan*/  check_hook; } ;
typedef  int /*<<< orphan*/  GucStringCheckHook ;
typedef  int /*<<< orphan*/  GucStringAssignHook ;
typedef  int /*<<< orphan*/  GucShowHook ;
typedef  int /*<<< orphan*/  GucContext ;

/* Variables and functions */
 int /*<<< orphan*/  PGC_STRING ; 
 int /*<<< orphan*/  define_custom_variable (int /*<<< orphan*/ *) ; 
 scalar_t__ init_custom_variable (char const*,char const*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void
DefineCustomStringVariable(const char *name,
						   const char *short_desc,
						   const char *long_desc,
						   char **valueAddr,
						   const char *bootValue,
						   GucContext context,
						   int flags,
						   GucStringCheckHook check_hook,
						   GucStringAssignHook assign_hook,
						   GucShowHook show_hook)
{
	struct config_string *var;

	var = (struct config_string *)
		init_custom_variable(name, short_desc, long_desc, context, flags,
							 PGC_STRING, sizeof(struct config_string));
	var->variable = valueAddr;
	var->boot_val = bootValue;
	var->check_hook = check_hook;
	var->assign_hook = assign_hook;
	var->show_hook = show_hook;
	define_custom_variable(&var->gen);
}