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
typedef  enum intel_snb_id { ____Placeholder_intel_snb_id } intel_snb_id ;

/* Variables and functions */
#define  C7 131 
 int MSR_CORE_C7_RESIDENCY ; 
 int MSR_PKG_C2_RESIDENCY ; 
 int MSR_PKG_C7_RESIDENCY ; 
 int MSR_TSC ; 
#define  PC2 130 
#define  PC7 129 
#define  TSC 128 
 scalar_t__ read_msr (unsigned int,int,unsigned long long*) ; 

__attribute__((used)) static int snb_get_count(enum intel_snb_id id, unsigned long long *val,
			unsigned int cpu)
{
	int msr;

	switch (id) {
	case C7:
		msr = MSR_CORE_C7_RESIDENCY;
		break;
	case PC2:
		msr = MSR_PKG_C2_RESIDENCY;
		break;
	case PC7:
		msr = MSR_PKG_C7_RESIDENCY;
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