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
 int /*<<< orphan*/  MSR_MISC_FEATURE_CONTROL ; 
 int base_cpu ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,unsigned long long,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  get_msr (int,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  has_misc_feature_control ; 
 int /*<<< orphan*/  outf ; 

void decode_misc_feature_control(void)
{
	unsigned long long msr;

	if (!has_misc_feature_control)
		return;

	if (!get_msr(base_cpu, MSR_MISC_FEATURE_CONTROL, &msr))
		fprintf(outf, "cpu%d: MSR_MISC_FEATURE_CONTROL: 0x%08llx (%sL2-Prefetch %sL2-Prefetch-pair %sL1-Prefetch %sL1-IP-Prefetch)\n",
			base_cpu, msr,
			msr & (0 << 0) ? "No-" : "",
			msr & (1 << 0) ? "No-" : "",
			msr & (2 << 0) ? "No-" : "",
			msr & (3 << 0) ? "No-" : "");
}