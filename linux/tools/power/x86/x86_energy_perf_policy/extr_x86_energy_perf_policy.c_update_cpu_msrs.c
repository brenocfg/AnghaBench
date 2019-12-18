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
 int /*<<< orphan*/  MSR_IA32_ENERGY_PERF_BIAS ; 
 int /*<<< orphan*/  MSR_IA32_MISC_ENABLE ; 
 unsigned long long MSR_IA32_MISC_ENABLE_TURBO_DISABLE ; 
 int /*<<< orphan*/  get_msr (int,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  has_hwp ; 
 int /*<<< orphan*/  hwp_update_enabled () ; 
 unsigned long long new_epb ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  put_msr (int,int /*<<< orphan*/ ,unsigned long long) ; 
 int turbo_update_value ; 
 scalar_t__ update_epb ; 
 int /*<<< orphan*/  update_hwp_request (int) ; 
 scalar_t__ update_turbo ; 
 scalar_t__ verbose ; 

int update_cpu_msrs(int cpu)
{
	unsigned long long msr;


	if (update_epb) {
		get_msr(cpu, MSR_IA32_ENERGY_PERF_BIAS, &msr);
		put_msr(cpu, MSR_IA32_ENERGY_PERF_BIAS, new_epb);

		if (verbose)
			printf("cpu%d: ENERGY_PERF_BIAS old: %d new: %d\n",
				cpu, (unsigned int) msr, (unsigned int) new_epb);
	}

	if (update_turbo) {
		int turbo_is_present_and_disabled;

		get_msr(cpu, MSR_IA32_MISC_ENABLE, &msr);

		turbo_is_present_and_disabled = ((msr & MSR_IA32_MISC_ENABLE_TURBO_DISABLE) != 0);

		if (turbo_update_value == 1)	{
			if (turbo_is_present_and_disabled) {
				msr &= ~MSR_IA32_MISC_ENABLE_TURBO_DISABLE;
				put_msr(cpu, MSR_IA32_MISC_ENABLE, msr);
				if (verbose)
					printf("cpu%d: turbo ENABLE\n", cpu);
			}
		} else {
			/*
			 * if "turbo_is_enabled" were known to be describe this cpu
			 * then we could use it here to skip redundant disable requests.
			 * but cpu may be in a different package, so we always write.
			 */
			msr |= MSR_IA32_MISC_ENABLE_TURBO_DISABLE;
			put_msr(cpu, MSR_IA32_MISC_ENABLE, msr);
			if (verbose)
				printf("cpu%d: turbo DISABLE\n", cpu);
		}
	}

	if (!has_hwp)
		return 0;

	if (!hwp_update_enabled())
		return 0;

	update_hwp_request(cpu);
	return 0;
}