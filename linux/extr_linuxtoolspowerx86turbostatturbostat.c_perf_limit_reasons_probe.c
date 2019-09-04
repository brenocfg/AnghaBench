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
#define  INTEL_FAM6_HASWELL_CORE 131 
#define  INTEL_FAM6_HASWELL_GT3E 130 
#define  INTEL_FAM6_HASWELL_ULT 129 
#define  INTEL_FAM6_HASWELL_X 128 
 int do_core_perf_limit_reasons ; 
 int do_gfx_perf_limit_reasons ; 
 int do_ring_perf_limit_reasons ; 
 int /*<<< orphan*/  genuine_intel ; 

void perf_limit_reasons_probe(unsigned int family, unsigned int model)
{
	if (!genuine_intel)
		return;

	if (family != 6)
		return;

	switch (model) {
	case INTEL_FAM6_HASWELL_CORE:	/* HSW */
	case INTEL_FAM6_HASWELL_ULT:	/* HSW */
	case INTEL_FAM6_HASWELL_GT3E:	/* HSW */
		do_gfx_perf_limit_reasons = 1;
	case INTEL_FAM6_HASWELL_X:	/* HSX */
		do_core_perf_limit_reasons = 1;
		do_ring_perf_limit_reasons = 1;
	default:
		return;
	}
}