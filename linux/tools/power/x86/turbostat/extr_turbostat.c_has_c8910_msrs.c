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
#define  INTEL_FAM6_ATOM_GOLDMONT 133 
#define  INTEL_FAM6_ATOM_GOLDMONT_PLUS 132 
#define  INTEL_FAM6_BROADWELL 131 
#define  INTEL_FAM6_CANNONLAKE_L 130 
#define  INTEL_FAM6_HASWELL_L 129 
#define  INTEL_FAM6_SKYLAKE_L 128 
 int /*<<< orphan*/  genuine_intel ; 

int has_c8910_msrs(unsigned int family, unsigned int model)
{
	if (!genuine_intel)
		return 0;

	switch (model) {
	case INTEL_FAM6_HASWELL_L:	/* HSW */
	case INTEL_FAM6_BROADWELL:	/* BDW */
	case INTEL_FAM6_SKYLAKE_L:	/* SKL */
	case INTEL_FAM6_CANNONLAKE_L:	/* CNL */
	case INTEL_FAM6_ATOM_GOLDMONT:	/* BXT */
	case INTEL_FAM6_ATOM_GOLDMONT_PLUS:
		return 1;
	}
	return 0;
}