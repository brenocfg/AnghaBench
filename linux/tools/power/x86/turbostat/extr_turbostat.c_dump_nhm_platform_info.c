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
 int /*<<< orphan*/  MSR_IA32_POWER_CTL ; 
 int /*<<< orphan*/  MSR_PLATFORM_INFO ; 
 int base_cpu ; 
 unsigned int bclk ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,unsigned long long,...) ; 
 int /*<<< orphan*/  get_msr (int,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  outf ; 

__attribute__((used)) static void
dump_nhm_platform_info(void)
{
	unsigned long long msr;
	unsigned int ratio;

	get_msr(base_cpu, MSR_PLATFORM_INFO, &msr);

	fprintf(outf, "cpu%d: MSR_PLATFORM_INFO: 0x%08llx\n", base_cpu, msr);

	ratio = (msr >> 40) & 0xFF;
	fprintf(outf, "%d * %.1f = %.1f MHz max efficiency frequency\n",
		ratio, bclk, ratio * bclk);

	ratio = (msr >> 8) & 0xFF;
	fprintf(outf, "%d * %.1f = %.1f MHz base frequency\n",
		ratio, bclk, ratio * bclk);

	get_msr(base_cpu, MSR_IA32_POWER_CTL, &msr);
	fprintf(outf, "cpu%d: MSR_IA32_POWER_CTL: 0x%08llx (C1E auto-promotion: %sabled)\n",
		base_cpu, msr, msr & 0x2 ? "EN" : "DIS");

	return;
}