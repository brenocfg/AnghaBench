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
struct module {int /*<<< orphan*/  num_exentries; int /*<<< orphan*/  extable; } ;
struct exception_table_entry {int dummy; } ;

/* Variables and functions */
 struct module* __module_address (unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct exception_table_entry* search_extable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

const struct exception_table_entry *search_module_extables(unsigned long addr)
{
	const struct exception_table_entry *e = NULL;
	struct module *mod;

	preempt_disable();
	mod = __module_address(addr);
	if (!mod)
		goto out;

	if (!mod->num_exentries)
		goto out;

	e = search_extable(mod->extable,
			   mod->num_exentries,
			   addr);
out:
	preempt_enable();

	/*
	 * Now, if we found one, we are running inside it now, hence
	 * we cannot unload the module, hence no refcnt needed.
	 */
	return e;
}