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
#define  INTEL_FAM6_ATOM_GEMINI_LAKE 136 
#define  INTEL_FAM6_ATOM_GOLDMONT 135 
#define  INTEL_FAM6_BROADWELL_CORE 134 
#define  INTEL_FAM6_CANNONLAKE_MOBILE 133 
#define  INTEL_FAM6_HASWELL_ULT 132 
#define  INTEL_FAM6_KABYLAKE_DESKTOP 131 
#define  INTEL_FAM6_KABYLAKE_MOBILE 130 
#define  INTEL_FAM6_SKYLAKE_DESKTOP 129 
#define  INTEL_FAM6_SKYLAKE_MOBILE 128 
 int /*<<< orphan*/  genuine_intel ; 

int has_hsw_msrs(unsigned int family, unsigned int model)
{
	if (!genuine_intel)
		return 0;

	switch (model) {
	case INTEL_FAM6_HASWELL_ULT:	/* HSW */
	case INTEL_FAM6_BROADWELL_CORE:	/* BDW */
	case INTEL_FAM6_SKYLAKE_MOBILE:	/* SKL */
	case INTEL_FAM6_SKYLAKE_DESKTOP:	/* SKL */
	case INTEL_FAM6_KABYLAKE_MOBILE:	/* KBL */
	case INTEL_FAM6_KABYLAKE_DESKTOP:	/* KBL */
	case INTEL_FAM6_CANNONLAKE_MOBILE:	/* CNL */
	case INTEL_FAM6_ATOM_GOLDMONT:	/* BXT */
	case INTEL_FAM6_ATOM_GEMINI_LAKE:
		return 1;
	}
	return 0;
}