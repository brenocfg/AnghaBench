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
#define  INTEL_FAM6_ATOM_DENVERTON 148 
#define  INTEL_FAM6_ATOM_GEMINI_LAKE 147 
#define  INTEL_FAM6_ATOM_GOLDMONT 146 
#define  INTEL_FAM6_BROADWELL_CORE 145 
#define  INTEL_FAM6_BROADWELL_GT3E 144 
#define  INTEL_FAM6_BROADWELL_X 143 
#define  INTEL_FAM6_BROADWELL_XEON_D 142 
#define  INTEL_FAM6_CANNONLAKE_MOBILE 141 
#define  INTEL_FAM6_HASWELL_CORE 140 
#define  INTEL_FAM6_HASWELL_GT3E 139 
#define  INTEL_FAM6_HASWELL_ULT 138 
#define  INTEL_FAM6_HASWELL_X 137 
#define  INTEL_FAM6_IVYBRIDGE 136 
#define  INTEL_FAM6_IVYBRIDGE_X 135 
#define  INTEL_FAM6_KABYLAKE_DESKTOP 134 
#define  INTEL_FAM6_KABYLAKE_MOBILE 133 
#define  INTEL_FAM6_SANDYBRIDGE 132 
#define  INTEL_FAM6_SANDYBRIDGE_X 131 
#define  INTEL_FAM6_SKYLAKE_DESKTOP 130 
#define  INTEL_FAM6_SKYLAKE_MOBILE 129 
#define  INTEL_FAM6_SKYLAKE_X 128 
 int /*<<< orphan*/  genuine_intel ; 

int has_snb_msrs(unsigned int family, unsigned int model)
{
	if (!genuine_intel)
		return 0;

	switch (model) {
	case INTEL_FAM6_SANDYBRIDGE:
	case INTEL_FAM6_SANDYBRIDGE_X:
	case INTEL_FAM6_IVYBRIDGE:	/* IVB */
	case INTEL_FAM6_IVYBRIDGE_X:	/* IVB Xeon */
	case INTEL_FAM6_HASWELL_CORE:	/* HSW */
	case INTEL_FAM6_HASWELL_X:	/* HSW */
	case INTEL_FAM6_HASWELL_ULT:	/* HSW */
	case INTEL_FAM6_HASWELL_GT3E:	/* HSW */
	case INTEL_FAM6_BROADWELL_CORE:	/* BDW */
	case INTEL_FAM6_BROADWELL_GT3E:	/* BDW */
	case INTEL_FAM6_BROADWELL_X:	/* BDX */
	case INTEL_FAM6_BROADWELL_XEON_D:	/* BDX-DE */
	case INTEL_FAM6_SKYLAKE_MOBILE:	/* SKL */
	case INTEL_FAM6_SKYLAKE_DESKTOP:	/* SKL */
	case INTEL_FAM6_KABYLAKE_MOBILE:	/* KBL */
	case INTEL_FAM6_KABYLAKE_DESKTOP:	/* KBL */
	case INTEL_FAM6_CANNONLAKE_MOBILE:	/* CNL */
	case INTEL_FAM6_SKYLAKE_X:	/* SKX */
	case INTEL_FAM6_ATOM_GOLDMONT:	/* BXT */
	case INTEL_FAM6_ATOM_GEMINI_LAKE:
	case INTEL_FAM6_ATOM_DENVERTON:	/* DNV */
		return 1;
	}
	return 0;
}