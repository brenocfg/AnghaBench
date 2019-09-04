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
typedef  enum intel_nhm_id { ____Placeholder_intel_nhm_id } intel_nhm_id ;

/* Variables and functions */
#define  C3 132 
#define  C6 131 
 int MSR_CORE_C3_RESIDENCY ; 
 int MSR_CORE_C6_RESIDENCY ; 
 int MSR_PKG_C3_RESIDENCY ; 
 int MSR_PKG_C6_RESIDENCY ; 
 int MSR_TSC ; 
#define  PC3 130 
#define  PC6 129 
#define  TSC 128 
 scalar_t__ read_msr (unsigned int,int,unsigned long long*) ; 

__attribute__((used)) static int nhm_get_count(enum intel_nhm_id id, unsigned long long *val,
			unsigned int cpu)
{
	int msr;

	switch (id) {
	case C3:
		msr = MSR_CORE_C3_RESIDENCY;
		break;
	case C6:
		msr = MSR_CORE_C6_RESIDENCY;
		break;
	case PC3:
		msr = MSR_PKG_C3_RESIDENCY;
		break;
	case PC6:
		msr = MSR_PKG_C6_RESIDENCY;
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