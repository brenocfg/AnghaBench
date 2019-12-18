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
#define  INTEL_FAM6_ATOM_SILVERMONT 129 
#define  INTEL_FAM6_ATOM_SILVERMONT_D 128 
 int /*<<< orphan*/  MSR_PKG_POWER_INFO ; 
 int RAPL_PKG_POWER_INFO ; 
 unsigned long long RAPL_POWER_GRANULARITY ; 
 int /*<<< orphan*/  base_cpu ; 
 int do_rapl ; 
 int /*<<< orphan*/  get_msr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 unsigned long long rapl_power_units ; 

double get_tdp_intel(unsigned int model)
{
	unsigned long long msr;

	if (do_rapl & RAPL_PKG_POWER_INFO)
		if (!get_msr(base_cpu, MSR_PKG_POWER_INFO, &msr))
			return ((msr >> 0) & RAPL_POWER_GRANULARITY) * rapl_power_units;

	switch (model) {
	case INTEL_FAM6_ATOM_SILVERMONT:
	case INTEL_FAM6_ATOM_SILVERMONT_D:
		return 30.0;
	default:
		return 135.0;
	}
}