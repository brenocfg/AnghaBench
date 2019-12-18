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
 int /*<<< orphan*/  MSR_MISC_PWR_MGMT ; 
 int base_cpu ; 
 int /*<<< orphan*/  do_nhm_platform_info ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,unsigned long long,char*,char*,char*) ; 
 int /*<<< orphan*/  get_msr (int,int /*<<< orphan*/ ,unsigned long long*) ; 
 scalar_t__ no_MSR_MISC_PWR_MGMT ; 
 int /*<<< orphan*/  outf ; 

void decode_misc_pwr_mgmt_msr(void)
{
	unsigned long long msr;

	if (!do_nhm_platform_info)
		return;

	if (no_MSR_MISC_PWR_MGMT)
		return;

	if (!get_msr(base_cpu, MSR_MISC_PWR_MGMT, &msr))
		fprintf(outf, "cpu%d: MSR_MISC_PWR_MGMT: 0x%08llx (%sable-EIST_Coordination %sable-EPB %sable-OOB)\n",
			base_cpu, msr,
			msr & (1 << 0) ? "DIS" : "EN",
			msr & (1 << 1) ? "EN" : "DIS",
			msr & (1 << 8) ? "EN" : "DIS");
}