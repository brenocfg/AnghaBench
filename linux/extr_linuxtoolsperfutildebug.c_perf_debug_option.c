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
struct debug_variable {int* ptr; scalar_t__ name; } ;

/* Variables and functions */
 int atoi (char*) ; 
 struct debug_variable* debug_variables ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 scalar_t__ quiet ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,scalar_t__) ; 
 char* strdup (char const*) ; 

int perf_debug_option(const char *str)
{
	struct debug_variable *var = &debug_variables[0];
	char *vstr, *s = strdup(str);
	int v = 1;

	vstr = strchr(s, '=');
	if (vstr)
		*vstr++ = 0;

	while (var->name) {
		if (!strcmp(s, var->name))
			break;
		var++;
	}

	if (!var->name) {
		pr_err("Unknown debug variable name '%s'\n", s);
		free(s);
		return -1;
	}

	if (vstr) {
		v = atoi(vstr);
		/*
		 * Allow only values in range (0, 10),
		 * otherwise set 0.
		 */
		v = (v < 0) || (v > 10) ? 0 : v;
	}

	if (quiet)
		v = -1;

	*var->ptr = v;
	free(s);
	return 0;
}