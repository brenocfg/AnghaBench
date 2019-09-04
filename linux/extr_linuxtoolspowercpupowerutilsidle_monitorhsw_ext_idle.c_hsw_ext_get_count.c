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
typedef  enum intel_hsw_ext_id { ____Placeholder_intel_hsw_ext_id } intel_hsw_ext_id ;

/* Variables and functions */
 int MSR_PKG_C10_RESIDENCY ; 
 int MSR_PKG_C8_RESIDENCY ; 
 int MSR_PKG_C9_RESIDENCY ; 
 int MSR_TSC ; 
#define  PC10 131 
#define  PC8 130 
#define  PC9 129 
#define  TSC 128 
 scalar_t__ read_msr (unsigned int,int,unsigned long long*) ; 

__attribute__((used)) static int hsw_ext_get_count(enum intel_hsw_ext_id id, unsigned long long *val,
			unsigned int cpu)
{
	int msr;

	switch (id) {
	case PC8:
		msr = MSR_PKG_C8_RESIDENCY;
		break;
	case PC9:
		msr = MSR_PKG_C9_RESIDENCY;
		break;
	case PC10:
		msr = MSR_PKG_C10_RESIDENCY;
		break;
	case TSC:
		msr = MSR_TSC;
		break;
	default:
		return -1;
	};
	if (read_msr(cpu, msr, val))
		return -1;
	return 0;
}