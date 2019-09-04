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
struct module {int async_probe_requested; } ;

/* Variables and functions */
 int ddebug_dyndbg_module_param_cb (char*,char*,char const*) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int unknown_module_param_cb(char *param, char *val, const char *modname,
				   void *arg)
{
	struct module *mod = arg;
	int ret;

	if (strcmp(param, "async_probe") == 0) {
		mod->async_probe_requested = true;
		return 0;
	}

	/* Check for magic 'dyndbg' arg */
	ret = ddebug_dyndbg_module_param_cb(param, val, modname);
	if (ret != 0)
		pr_warn("%s: unknown parameter '%s' ignored\n", modname, param);
	return 0;
}