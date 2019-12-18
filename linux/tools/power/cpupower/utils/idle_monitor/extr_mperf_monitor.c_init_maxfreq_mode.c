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
struct TYPE_2__ {int caps; scalar_t__ vendor; } ;

/* Variables and functions */
 int CPUPOWER_CAP_INV_TSC ; 
 int /*<<< orphan*/  MAX_FREQ_SYSFS ; 
 int /*<<< orphan*/  MAX_FREQ_TSC_REF ; 
 int /*<<< orphan*/  MSR_AMD_HWCR ; 
 scalar_t__ X86_VENDOR_AMD ; 
 scalar_t__ X86_VENDOR_HYGON ; 
 scalar_t__ X86_VENDOR_INTEL ; 
 scalar_t__ cpufreq_get_hardware_limits (int /*<<< orphan*/ ,unsigned long*,int*) ; 
 TYPE_1__ cpupower_cpu_info ; 
 int /*<<< orphan*/  dprint (char*,...) ; 
 int /*<<< orphan*/  max_freq_mode ; 
 int max_frequency ; 
 int read_msr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 

__attribute__((used)) static int init_maxfreq_mode(void)
{
	int ret;
	unsigned long long hwcr;
	unsigned long min;

	if (!(cpupower_cpu_info.caps & CPUPOWER_CAP_INV_TSC))
		goto use_sysfs;

	if (cpupower_cpu_info.vendor == X86_VENDOR_AMD ||
	    cpupower_cpu_info.vendor == X86_VENDOR_HYGON) {
		/* MSR_AMD_HWCR tells us whether TSC runs at P0/mperf
		 * freq.
		 * A test whether hwcr is accessable/available would be:
		 * (cpupower_cpu_info.family > 0x10 ||
		 *   cpupower_cpu_info.family == 0x10 &&
		 *   cpupower_cpu_info.model >= 0x2))
		 * This should be the case for all aperf/mperf
		 * capable AMD machines and is therefore safe to test here.
		 * Compare with Linus kernel git commit: acf01734b1747b1ec4
		 */
		ret = read_msr(0, MSR_AMD_HWCR, &hwcr);
		/*
		 * If the MSR read failed, assume a Xen system that did
		 * not explicitly provide access to it and assume TSC works
		*/
		if (ret != 0) {
			dprint("TSC read 0x%x failed - assume TSC working\n",
			       MSR_AMD_HWCR);
			return 0;
		} else if (1 & (hwcr >> 24)) {
			max_freq_mode = MAX_FREQ_TSC_REF;
			return 0;
		} else { /* Use sysfs max frequency if available */ }
	} else if (cpupower_cpu_info.vendor == X86_VENDOR_INTEL) {
		/*
		 * On Intel we assume mperf (in C0) is ticking at same
		 * rate than TSC
		 */
		max_freq_mode = MAX_FREQ_TSC_REF;
		return 0;
	}
use_sysfs:
	if (cpufreq_get_hardware_limits(0, &min, &max_frequency)) {
		dprint("Cannot retrieve max freq from cpufreq kernel "
		       "subsystem\n");
		return -1;
	}
	max_freq_mode = MAX_FREQ_SYSFS;
	max_frequency /= 1000; /* Default automatically to MHz value */
	return 0;
}