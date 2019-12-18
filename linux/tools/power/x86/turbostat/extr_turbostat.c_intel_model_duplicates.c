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
 unsigned int INTEL_FAM6_ATOM_GOLDMONT_D ; 
#define  INTEL_FAM6_ATOM_TREMONT_D 143 
#define  INTEL_FAM6_BROADWELL_D 142 
#define  INTEL_FAM6_BROADWELL_X 141 
 unsigned int INTEL_FAM6_CANNONLAKE_L ; 
#define  INTEL_FAM6_ICELAKE_L 140 
#define  INTEL_FAM6_ICELAKE_NNPI 139 
#define  INTEL_FAM6_KABYLAKE 138 
#define  INTEL_FAM6_KABYLAKE_L 137 
#define  INTEL_FAM6_NEHALEM 136 
#define  INTEL_FAM6_NEHALEM_EP 135 
#define  INTEL_FAM6_NEHALEM_EX 134 
#define  INTEL_FAM6_SKYLAKE 133 
#define  INTEL_FAM6_SKYLAKE_L 132 
#define  INTEL_FAM6_WESTMERE 131 
#define  INTEL_FAM6_WESTMERE_EP 130 
#define  INTEL_FAM6_WESTMERE_EX 129 
 unsigned int INTEL_FAM6_XEON_PHI_KNL ; 
#define  INTEL_FAM6_XEON_PHI_KNM 128 

unsigned int intel_model_duplicates(unsigned int model)
{

	switch(model) {
	case INTEL_FAM6_NEHALEM_EP:	/* Core i7, Xeon 5500 series - Bloomfield, Gainstown NHM-EP */
	case INTEL_FAM6_NEHALEM:	/* Core i7 and i5 Processor - Clarksfield, Lynnfield, Jasper Forest */
	case 0x1F:	/* Core i7 and i5 Processor - Nehalem */
	case INTEL_FAM6_WESTMERE:	/* Westmere Client - Clarkdale, Arrandale */
	case INTEL_FAM6_WESTMERE_EP:	/* Westmere EP - Gulftown */
		return INTEL_FAM6_NEHALEM;

	case INTEL_FAM6_NEHALEM_EX:	/* Nehalem-EX Xeon - Beckton */
	case INTEL_FAM6_WESTMERE_EX:	/* Westmere-EX Xeon - Eagleton */
		return INTEL_FAM6_NEHALEM_EX;

	case INTEL_FAM6_XEON_PHI_KNM:
		return INTEL_FAM6_XEON_PHI_KNL;

	case INTEL_FAM6_BROADWELL_X:
	case INTEL_FAM6_BROADWELL_D:	/* BDX-DE */
		return INTEL_FAM6_BROADWELL_X;

	case INTEL_FAM6_SKYLAKE_L:
	case INTEL_FAM6_SKYLAKE:
	case INTEL_FAM6_KABYLAKE_L:
	case INTEL_FAM6_KABYLAKE:
		return INTEL_FAM6_SKYLAKE_L;

	case INTEL_FAM6_ICELAKE_L:
	case INTEL_FAM6_ICELAKE_NNPI:
		return INTEL_FAM6_CANNONLAKE_L;

	case INTEL_FAM6_ATOM_TREMONT_D:
		return INTEL_FAM6_ATOM_GOLDMONT_D;
	}
	return model;
}