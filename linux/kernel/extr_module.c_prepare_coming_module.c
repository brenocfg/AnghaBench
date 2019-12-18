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
 int /*<<< orphan*/  MODULE_STATE_COMING ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct module*) ; 
 int /*<<< orphan*/  ftrace_module_enable (struct module*) ; 
 int klp_module_coming (struct module*) ; 
 int /*<<< orphan*/  module_notify_list ; 

__attribute__((used)) static int prepare_coming_module(struct module *mod)
{
	int err;

	ftrace_module_enable(mod);
	err = klp_module_coming(mod);
	if (err)
		return err;

	blocking_notifier_call_chain(&module_notify_list,
				     MODULE_STATE_COMING, mod);
	return 0;
}