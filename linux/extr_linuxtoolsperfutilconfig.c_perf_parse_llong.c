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
 int /*<<< orphan*/  parse_unit_factor (char*,unsigned long*) ; 
 long long strtoll (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_parse_llong(const char *value, long long *ret)
{
	if (value && *value) {
		char *end;
		long long val = strtoll(value, &end, 0);
		unsigned long factor = 1;

		if (!parse_unit_factor(end, &factor))
			return 0;
		*ret = val * factor;
		return 1;
	}
	return 0;
}