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
 unsigned long long FEATURE_CONTROL_LOCKED ; 
 int /*<<< orphan*/  MSR_IA32_FEATURE_CONTROL ; 
 int base_cpu ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,unsigned long long,char*,char*) ; 
 int /*<<< orphan*/  get_msr (int,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  outf ; 

void decode_feature_control_msr(void)
{
	unsigned long long msr;

	if (!get_msr(base_cpu, MSR_IA32_FEATURE_CONTROL, &msr))
		fprintf(outf, "cpu%d: MSR_IA32_FEATURE_CONTROL: 0x%08llx (%sLocked %s)\n",
			base_cpu, msr,
			msr & FEATURE_CONTROL_LOCKED ? "" : "UN-",
			msr & (1 << 18) ? "SGX" : "");
}