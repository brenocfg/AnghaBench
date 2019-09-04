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
#define  INTEL_FAM6_BROADWELL_X 132 
#define  INTEL_FAM6_BROADWELL_XEON_D 131 
#define  INTEL_FAM6_HASWELL_X 130 
#define  INTEL_FAM6_XEON_PHI_KNL 129 
#define  INTEL_FAM6_XEON_PHI_KNM 128 
 double rapl_dram_energy_units ; 

__attribute__((used)) static double
rapl_dram_energy_units_probe(int  model, double rapl_energy_units)
{
	/* only called for genuine_intel, family 6 */

	switch (model) {
	case INTEL_FAM6_HASWELL_X:	/* HSX */
	case INTEL_FAM6_BROADWELL_X:	/* BDX */
	case INTEL_FAM6_BROADWELL_XEON_D:	/* BDX-DE */
	case INTEL_FAM6_XEON_PHI_KNL:	/* KNL */
	case INTEL_FAM6_XEON_PHI_KNM:
		return (rapl_dram_energy_units = 15.3 / 1000000);
	default:
		return (rapl_energy_units);
	}
}