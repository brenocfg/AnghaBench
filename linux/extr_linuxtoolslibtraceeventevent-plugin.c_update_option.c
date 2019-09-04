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
struct trace_plugin_options {int /*<<< orphan*/  value; scalar_t__ option; scalar_t__ plugin; struct trace_plugin_options* next; } ;
struct tep_plugin_option {char const* plugin_alias; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 char* strdup (char const*) ; 
 char* strstr (char*,char*) ; 
 struct trace_plugin_options* trace_plugin_options ; 
 int update_option_value (struct tep_plugin_option*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
update_option(const char *file, struct tep_plugin_option *option)
{
	struct trace_plugin_options *op;
	char *plugin;
	int ret = 0;

	if (option->plugin_alias) {
		plugin = strdup(option->plugin_alias);
		if (!plugin)
			return -1;
	} else {
		char *p;
		plugin = strdup(file);
		if (!plugin)
			return -1;
		p = strstr(plugin, ".");
		if (p)
			*p = '\0';
	}

	/* first look for named options */
	for (op = trace_plugin_options; op; op = op->next) {
		if (!op->plugin)
			continue;
		if (strcmp(op->plugin, plugin) != 0)
			continue;
		if (strcmp(op->option, option->name) != 0)
			continue;

		ret = update_option_value(option, op->value);
		if (ret)
			goto out;
		break;
	}

	/* first look for unnamed options */
	for (op = trace_plugin_options; op; op = op->next) {
		if (op->plugin)
			continue;
		if (strcmp(op->option, option->name) != 0)
			continue;

		ret = update_option_value(option, op->value);
		break;
	}

 out:
	free(plugin);
	return ret;
}