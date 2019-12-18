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
struct obs_module {struct obs_module* next; int /*<<< orphan*/  (* set_locale ) (char const*) ;} ;
struct TYPE_2__ {struct obs_module* first_module; scalar_t__ locale; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (scalar_t__) ; 
 scalar_t__ bstrdup (char const*) ; 
 TYPE_1__* obs ; 
 int /*<<< orphan*/  stub1 (char const*) ; 

void obs_set_locale(const char *locale)
{
	struct obs_module *module;
	if (!obs)
		return;

	if (obs->locale)
		bfree(obs->locale);
	obs->locale = bstrdup(locale);

	module = obs->first_module;
	while (module) {
		if (module->set_locale)
			module->set_locale(locale);

		module = module->next;
	}
}