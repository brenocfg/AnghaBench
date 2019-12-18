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
struct TYPE_2__ {int caps; } ;

/* Variables and functions */
 int CPUPOWER_CAP_HAS_TURBO_RATIO ; 
 int /*<<< orphan*/  MSR_NEHALEM_TURBO_RATIO_LIMIT ; 
 TYPE_1__ cpupower_cpu_info ; 
 int read_msr (unsigned int,int /*<<< orphan*/ ,unsigned long long*) ; 

unsigned long long msr_intel_get_turbo_ratio(unsigned int cpu)
{
	unsigned long long val;
	int ret;

	if (!(cpupower_cpu_info.caps & CPUPOWER_CAP_HAS_TURBO_RATIO))
		return -1;

	ret = read_msr(cpu, MSR_NEHALEM_TURBO_RATIO_LIMIT, &val);
	if (ret)
		return ret;
	return val;
}