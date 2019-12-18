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
 int /*<<< orphan*/  pr_debug (char*,char*,char const*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  zfree (char**) ; 

__attribute__((used)) static void perf_pmu_assign_str(char *name, const char *field, char **old_str,
				char **new_str)
{
	if (!*old_str)
		goto set_new;

	if (*new_str) {	/* Have new string, check with old */
		if (strcasecmp(*old_str, *new_str))
			pr_debug("alias %s differs in field '%s'\n",
				 name, field);
		zfree(old_str);
	} else		/* Nothing new --> keep old string */
		return;
set_new:
	*old_str = *new_str;
	*new_str = NULL;
}