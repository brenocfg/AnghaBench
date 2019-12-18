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
 int /*<<< orphan*/  MSR_TURBO_RATIO_LIMIT ; 
 int /*<<< orphan*/  base_cpu ; 
 unsigned long long bdx_highest_ratio ; 
 int /*<<< orphan*/  get_cpuid_or_exit (int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  get_msr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 unsigned int has_epb ; 
 unsigned int has_hwp ; 
 unsigned int turbo_is_enabled ; 

void early_cpuid(void)
{
	unsigned int eax, ebx, ecx, edx;
	unsigned int fms, family, model;

	get_cpuid_or_exit(1, &fms, &ebx, &ecx, &edx);
	family = (fms >> 8) & 0xf;
	model = (fms >> 4) & 0xf;
	if (family == 6 || family == 0xf)
		model += ((fms >> 16) & 0xf) << 4;

	if (model == 0x4F) {
		unsigned long long msr;

		get_msr(base_cpu, MSR_TURBO_RATIO_LIMIT, &msr);

		bdx_highest_ratio = msr & 0xFF;
	}

	get_cpuid_or_exit(0x6, &eax, &ebx, &ecx, &edx);
	turbo_is_enabled = (eax >> 1) & 1;
	has_hwp = (eax >> 7) & 1;
	has_epb = (ecx >> 3) & 1;
}