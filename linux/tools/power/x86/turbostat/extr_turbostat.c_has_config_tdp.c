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
#define  INTEL_FAM6_BROADWELL 139 
#define  INTEL_FAM6_BROADWELL_G 138 
#define  INTEL_FAM6_BROADWELL_X 137 
#define  INTEL_FAM6_CANNONLAKE_L 136 
#define  INTEL_FAM6_HASWELL 135 
#define  INTEL_FAM6_HASWELL_G 134 
#define  INTEL_FAM6_HASWELL_L 133 
#define  INTEL_FAM6_HASWELL_X 132 
#define  INTEL_FAM6_IVYBRIDGE 131 
#define  INTEL_FAM6_SKYLAKE_L 130 
#define  INTEL_FAM6_SKYLAKE_X 129 
#define  INTEL_FAM6_XEON_PHI_KNL 128 
 int /*<<< orphan*/  genuine_intel ; 

int has_config_tdp(unsigned int family, unsigned int model)
{
	if (!genuine_intel)
		return 0;

	if (family != 6)
		return 0;

	switch (model) {
	case INTEL_FAM6_IVYBRIDGE:	/* IVB */
	case INTEL_FAM6_HASWELL:	/* HSW */
	case INTEL_FAM6_HASWELL_X:	/* HSX */
	case INTEL_FAM6_HASWELL_L:	/* HSW */
	case INTEL_FAM6_HASWELL_G:	/* HSW */
	case INTEL_FAM6_BROADWELL:	/* BDW */
	case INTEL_FAM6_BROADWELL_G:	/* BDW */
	case INTEL_FAM6_BROADWELL_X:	/* BDX */
	case INTEL_FAM6_SKYLAKE_L:	/* SKL */
	case INTEL_FAM6_CANNONLAKE_L:	/* CNL */
	case INTEL_FAM6_SKYLAKE_X:	/* SKX */

	case INTEL_FAM6_XEON_PHI_KNL:	/* Knights Landing */
		return 1;
	default:
		return 0;
	}
}