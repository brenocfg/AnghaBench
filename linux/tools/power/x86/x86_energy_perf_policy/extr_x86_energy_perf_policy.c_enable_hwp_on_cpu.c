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
 int /*<<< orphan*/  get_msr (int,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  printf (char*,int,unsigned int,int) ; 
 int /*<<< orphan*/  put_msr (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ verbose ; 

int enable_hwp_on_cpu(int cpu)
{
	unsigned long long msr;

	get_msr(cpu, MSR_PM_ENABLE, &msr);
	put_msr(cpu, MSR_PM_ENABLE, 1);

	if (verbose)
		printf("cpu%d: MSR_PM_ENABLE old: %d new: %d\n", cpu, (unsigned int) msr, 1);

	return 0;
}