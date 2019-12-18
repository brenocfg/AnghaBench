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

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 void* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int parse_config_arg(char *arg, char **var, char **value)
{
	const char *last_dot = strchr(arg, '.');

	/*
	 * Since "var" actually contains the section name and the real
	 * config variable name separated by a dot, we have to know where the dot is.
	 */
	if (last_dot == NULL || last_dot == arg) {
		pr_err("The config variable does not contain a section name: %s\n", arg);
		return -1;
	}
	if (!last_dot[1]) {
		pr_err("The config variable does not contain a variable name: %s\n", arg);
		return -1;
	}

	*value = strchr(arg, '=');
	if (*value == NULL)
		*var = arg;
	else if (!strcmp(*value, "=")) {
		pr_err("The config variable does not contain a value: %s\n", arg);
		return -1;
	} else {
		*value = *value + 1; /* excluding a first character '=' */
		*var = strsep(&arg, "=");
		if (*var[0] == '\0') {
			pr_err("invalid config variable: %s\n", arg);
			return -1;
		}
	}

	return 0;
}