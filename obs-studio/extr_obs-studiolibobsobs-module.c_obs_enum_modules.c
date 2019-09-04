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
struct obs_module {struct obs_module* next; } ;
typedef  int /*<<< orphan*/  (* obs_enum_module_callback_t ) (void*,struct obs_module*) ;
struct TYPE_2__ {struct obs_module* first_module; } ;

/* Variables and functions */
 TYPE_1__* obs ; 

void obs_enum_modules(obs_enum_module_callback_t callback, void *param)
{
	struct obs_module *module;
	if (!obs)
		return;

	module = obs->first_module;
	while (module) {
		callback(param, module);
		module = module->next;
	}
}