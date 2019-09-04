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
#define  INTEL_FAM6_NEHALEM_EX 131 
#define  INTEL_FAM6_WESTMERE_EX 130 
#define  INTEL_FAM6_XEON_PHI_KNL 129 
#define  INTEL_FAM6_XEON_PHI_KNM 128 
 scalar_t__ has_slv_msrs (unsigned int,unsigned int) ; 

int has_turbo_ratio_limit(unsigned int family, unsigned int model)
{
	if (has_slv_msrs(family, model))
		return 0;

	switch (model) {
	/* Nehalem compatible, but do not include turbo-ratio limit support */
	case INTEL_FAM6_NEHALEM_EX:	/* Nehalem-EX Xeon - Beckton */
	case INTEL_FAM6_WESTMERE_EX:	/* Westmere-EX Xeon - Eagleton */
	case INTEL_FAM6_XEON_PHI_KNL:	/* PHI - Knights Landing (different MSR definition) */
	case INTEL_FAM6_XEON_PHI_KNM:
		return 0;
	default:
		return 1;
	}
}