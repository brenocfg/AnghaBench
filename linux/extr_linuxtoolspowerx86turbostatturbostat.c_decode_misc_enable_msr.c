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
 int /*<<< orphan*/  MSR_IA32_MISC_ENABLE ; 
 unsigned long long MSR_IA32_MISC_ENABLE_ENHANCED_SPEEDSTEP ; 
 unsigned long long MSR_IA32_MISC_ENABLE_MWAIT ; 
 unsigned long long MSR_IA32_MISC_ENABLE_PREFETCH_DISABLE ; 
 unsigned long long MSR_IA32_MISC_ENABLE_TM1 ; 
 unsigned long long MSR_IA32_MISC_ENABLE_TURBO_DISABLE ; 
 int base_cpu ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,unsigned long long,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  genuine_intel ; 
 int /*<<< orphan*/  get_msr (int,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  outf ; 

void decode_misc_enable_msr(void)
{
	unsigned long long msr;

	if (!genuine_intel)
		return;

	if (!get_msr(base_cpu, MSR_IA32_MISC_ENABLE, &msr))
		fprintf(outf, "cpu%d: MSR_IA32_MISC_ENABLE: 0x%08llx (%sTCC %sEIST %sMWAIT %sPREFETCH %sTURBO)\n",
			base_cpu, msr,
			msr & MSR_IA32_MISC_ENABLE_TM1 ? "" : "No-",
			msr & MSR_IA32_MISC_ENABLE_ENHANCED_SPEEDSTEP ? "" : "No-",
			msr & MSR_IA32_MISC_ENABLE_MWAIT ? "" : "No-",
			msr & MSR_IA32_MISC_ENABLE_PREFETCH_DISABLE ? "No-" : "",
			msr & MSR_IA32_MISC_ENABLE_TURBO_DISABLE ? "No-" : "");
}