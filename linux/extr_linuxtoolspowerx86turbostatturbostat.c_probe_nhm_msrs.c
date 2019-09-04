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
#define  INTEL_FAM6_ATOM_AIRMONT 159 
#define  INTEL_FAM6_ATOM_DENVERTON 158 
#define  INTEL_FAM6_ATOM_GEMINI_LAKE 157 
#define  INTEL_FAM6_ATOM_GOLDMONT 156 
#define  INTEL_FAM6_ATOM_SILVERMONT1 155 
#define  INTEL_FAM6_ATOM_SILVERMONT2 154 
#define  INTEL_FAM6_BROADWELL_CORE 153 
#define  INTEL_FAM6_BROADWELL_GT3E 152 
#define  INTEL_FAM6_BROADWELL_X 151 
#define  INTEL_FAM6_BROADWELL_XEON_D 150 
#define  INTEL_FAM6_CANNONLAKE_MOBILE 149 
#define  INTEL_FAM6_HASWELL_CORE 148 
#define  INTEL_FAM6_HASWELL_GT3E 147 
#define  INTEL_FAM6_HASWELL_ULT 146 
#define  INTEL_FAM6_HASWELL_X 145 
#define  INTEL_FAM6_IVYBRIDGE 144 
#define  INTEL_FAM6_IVYBRIDGE_X 143 
#define  INTEL_FAM6_KABYLAKE_DESKTOP 142 
#define  INTEL_FAM6_KABYLAKE_MOBILE 141 
#define  INTEL_FAM6_NEHALEM 140 
#define  INTEL_FAM6_NEHALEM_EP 139 
#define  INTEL_FAM6_NEHALEM_EX 138 
#define  INTEL_FAM6_SANDYBRIDGE 137 
#define  INTEL_FAM6_SANDYBRIDGE_X 136 
#define  INTEL_FAM6_SKYLAKE_DESKTOP 135 
#define  INTEL_FAM6_SKYLAKE_MOBILE 134 
#define  INTEL_FAM6_SKYLAKE_X 133 
#define  INTEL_FAM6_WESTMERE 132 
#define  INTEL_FAM6_WESTMERE_EP 131 
#define  INTEL_FAM6_WESTMERE_EX 130 
#define  INTEL_FAM6_XEON_PHI_KNL 129 
#define  INTEL_FAM6_XEON_PHI_KNM 128 
 int /*<<< orphan*/  MSR_PKG_CST_CONFIG_CONTROL ; 
 int /*<<< orphan*/  MSR_PLATFORM_INFO ; 
 int* amt_pkg_cstate_limits ; 
 int /*<<< orphan*/  base_cpu ; 
 unsigned int base_hz ; 
 unsigned int bclk ; 
 int* bxt_pkg_cstate_limits ; 
 unsigned int discover_bclk (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  genuine_intel ; 
 int /*<<< orphan*/  get_msr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 int has_base_hz ; 
 int has_misc_feature_control ; 
 int* hsw_pkg_cstate_limits ; 
 int* nhm_pkg_cstate_limits ; 
 int no_MSR_MISC_PWR_MGMT ; 
 int* phi_pkg_cstate_limits ; 
 int pkg_cstate_limit ; 
 int* skx_pkg_cstate_limits ; 
 int* slv_pkg_cstate_limits ; 
 int* snb_pkg_cstate_limits ; 

int probe_nhm_msrs(unsigned int family, unsigned int model)
{
	unsigned long long msr;
	unsigned int base_ratio;
	int *pkg_cstate_limits;

	if (!genuine_intel)
		return 0;

	if (family != 6)
		return 0;

	bclk = discover_bclk(family, model);

	switch (model) {
	case INTEL_FAM6_NEHALEM_EP:	/* Core i7, Xeon 5500 series - Bloomfield, Gainstown NHM-EP */
	case INTEL_FAM6_NEHALEM:	/* Core i7 and i5 Processor - Clarksfield, Lynnfield, Jasper Forest */
	case 0x1F:	/* Core i7 and i5 Processor - Nehalem */
	case INTEL_FAM6_WESTMERE:	/* Westmere Client - Clarkdale, Arrandale */
	case INTEL_FAM6_WESTMERE_EP:	/* Westmere EP - Gulftown */
	case INTEL_FAM6_NEHALEM_EX:	/* Nehalem-EX Xeon - Beckton */
	case INTEL_FAM6_WESTMERE_EX:	/* Westmere-EX Xeon - Eagleton */
		pkg_cstate_limits = nhm_pkg_cstate_limits;
		break;
	case INTEL_FAM6_SANDYBRIDGE:	/* SNB */
	case INTEL_FAM6_SANDYBRIDGE_X:	/* SNB Xeon */
	case INTEL_FAM6_IVYBRIDGE:	/* IVB */
	case INTEL_FAM6_IVYBRIDGE_X:	/* IVB Xeon */
		pkg_cstate_limits = snb_pkg_cstate_limits;
		has_misc_feature_control = 1;
		break;
	case INTEL_FAM6_HASWELL_CORE:	/* HSW */
	case INTEL_FAM6_HASWELL_X:	/* HSX */
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
		pkg_cstate_limits = hsw_pkg_cstate_limits;
		has_misc_feature_control = 1;
		break;
	case INTEL_FAM6_SKYLAKE_X:	/* SKX */
		pkg_cstate_limits = skx_pkg_cstate_limits;
		has_misc_feature_control = 1;
		break;
	case INTEL_FAM6_ATOM_SILVERMONT1:	/* BYT */
		no_MSR_MISC_PWR_MGMT = 1;
	case INTEL_FAM6_ATOM_SILVERMONT2:	/* AVN */
		pkg_cstate_limits = slv_pkg_cstate_limits;
		break;
	case INTEL_FAM6_ATOM_AIRMONT:	/* AMT */
		pkg_cstate_limits = amt_pkg_cstate_limits;
		no_MSR_MISC_PWR_MGMT = 1;
		break;
	case INTEL_FAM6_XEON_PHI_KNL:	/* PHI */
	case INTEL_FAM6_XEON_PHI_KNM:
		pkg_cstate_limits = phi_pkg_cstate_limits;
		break;
	case INTEL_FAM6_ATOM_GOLDMONT:	/* BXT */
	case INTEL_FAM6_ATOM_GEMINI_LAKE:
	case INTEL_FAM6_ATOM_DENVERTON:	/* DNV */
		pkg_cstate_limits = bxt_pkg_cstate_limits;
		break;
	default:
		return 0;
	}
	get_msr(base_cpu, MSR_PKG_CST_CONFIG_CONTROL, &msr);
	pkg_cstate_limit = pkg_cstate_limits[msr & 0xF];

	get_msr(base_cpu, MSR_PLATFORM_INFO, &msr);
	base_ratio = (msr >> 8) & 0xFF;

	base_hz = base_ratio * bclk * 1000000;
	has_base_hz = 1;
	return 1;
}