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
struct module {int dummy; } ;

/* Variables and functions */
 int ENOEXEC ; 

__attribute__((used)) static int try_to_force_load(struct module *mod, const char *reason)
{
#ifdef CONFIG_MODULE_FORCE_LOAD
	if (!test_taint(TAINT_FORCED_MODULE))
		pr_warn("%s: %s: kernel tainted.\n", mod->name, reason);
	add_taint_module(mod, TAINT_FORCED_MODULE, LOCKDEP_NOW_UNRELIABLE);
	return 0;
#else
	return -ENOEXEC;
#endif
}