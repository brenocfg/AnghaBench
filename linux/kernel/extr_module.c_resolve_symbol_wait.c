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
struct module {int /*<<< orphan*/  name; } ;
struct load_info {int dummy; } ;
struct kernel_symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int HZ ; 
 int /*<<< orphan*/  IS_ERR (struct kernel_symbol const*) ; 
 int MODULE_NAME_LEN ; 
 int /*<<< orphan*/  PTR_ERR (struct kernel_symbol const*) ; 
 int /*<<< orphan*/  module_wq ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,char*) ; 
 struct kernel_symbol* resolve_symbol (struct module*,struct load_info const*,char const*,char*) ; 
 scalar_t__ wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static const struct kernel_symbol *
resolve_symbol_wait(struct module *mod,
		    const struct load_info *info,
		    const char *name)
{
	const struct kernel_symbol *ksym;
	char owner[MODULE_NAME_LEN];

	if (wait_event_interruptible_timeout(module_wq,
			!IS_ERR(ksym = resolve_symbol(mod, info, name, owner))
			|| PTR_ERR(ksym) != -EBUSY,
					     30 * HZ) <= 0) {
		pr_warn("%s: gave up waiting for init of module %s.\n",
			mod->name, owner);
	}
	return ksym;
}