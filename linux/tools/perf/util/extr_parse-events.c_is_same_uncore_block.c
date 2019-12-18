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
 scalar_t__ strncmp (char const*,char const*,int) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static bool is_same_uncore_block(const char *pmu_name_a, const char *pmu_name_b)
{
	char *end_a, *end_b;

	end_a = strrchr(pmu_name_a, '_');
	end_b = strrchr(pmu_name_b, '_');

	if (!end_a || !end_b)
		return false;

	if ((end_a - pmu_name_a) != (end_b - pmu_name_b))
		return false;

	return (strncmp(pmu_name_a, pmu_name_b, end_a - pmu_name_a) == 0);
}