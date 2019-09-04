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
 int /*<<< orphan*/  MSR_PM_ENABLE ; 
 int /*<<< orphan*/  base_cpu ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_msr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 scalar_t__ has_hwp ; 
 int /*<<< orphan*/  stderr ; 

void verify_hwp_is_enabled(void)
{
	unsigned long long msr;

	if (!has_hwp)	/* set in early_cpuid() */
		return;

	/* MSR_PM_ENABLE[1] == 1 if HWP is enabled and MSRs visible */
	get_msr(base_cpu, MSR_PM_ENABLE, &msr);
	if ((msr & 1) == 0) {
		fprintf(stderr, "HWP can be enabled using '--hwp-enable'\n");
		has_hwp = 0;
		return;
	}
}