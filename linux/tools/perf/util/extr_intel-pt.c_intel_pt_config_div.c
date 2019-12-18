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
 long INT_MAX ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 long strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pt_config_div(const char *var, const char *value, void *data)
{
	int *d = data;
	long val;

	if (!strcmp(var, "intel-pt.cache-divisor")) {
		val = strtol(value, NULL, 0);
		if (val > 0 && val <= INT_MAX)
			*d = val;
	}

	return 0;
}