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
#define  INTEL_FAM6_ATOM_AIRMONT 150 
#define  INTEL_FAM6_ATOM_GOLDMONT 149 
#define  INTEL_FAM6_ATOM_GOLDMONT_D 148 
#define  INTEL_FAM6_ATOM_GOLDMONT_PLUS 147 
#define  INTEL_FAM6_ATOM_SILVERMONT 146 
#define  INTEL_FAM6_ATOM_SILVERMONT_D 145 
#define  INTEL_FAM6_BROADWELL 144 
#define  INTEL_FAM6_BROADWELL_G 143 
#define  INTEL_FAM6_BROADWELL_X 142 
#define  INTEL_FAM6_CANNONLAKE_L 141 
#define  INTEL_FAM6_HASWELL 140 
#define  INTEL_FAM6_HASWELL_G 139 
#define  INTEL_FAM6_HASWELL_L 138 
#define  INTEL_FAM6_HASWELL_X 137 
#define  INTEL_FAM6_IVYBRIDGE 136 
#define  INTEL_FAM6_IVYBRIDGE_X 135 
#define  INTEL_FAM6_NEHALEM 134 
#define  INTEL_FAM6_NEHALEM_EX 133 
#define  INTEL_FAM6_SANDYBRIDGE 132 
#define  INTEL_FAM6_SANDYBRIDGE_X 131 
#define  INTEL_FAM6_SKYLAKE_L 130 
#define  INTEL_FAM6_SKYLAKE_X 129 
#define  INTEL_FAM6_XEON_PHI_KNL 128 
 int /*<<< orphan*/  MSR_PKG_CST_CONFIG_CONTROL ; 
 int /*<<< orphan*/  MSR_PLATFORM_INFO ; 
 int* amt_pkg_cstate_limits ; 
 int /*<<< orphan*/  base_cpu ; 
 unsigned int base_hz ; 
 unsigned int bclk ; 
 unsigned int discover_bclk (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  genuine_intel ; 
 int /*<<< orphan*/  get_msr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 int* glm_pkg_cstate_limits ; 
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
	case INTEL_FAM6_NEHALEM:	/* Core i7 and i5 Processor - Clarksfield, Lynnfield, Jasper Forest */
	case INTEL_FAM6_NEHALEM_EX:	/* Nehalem-EX Xeon - Beckton */
		pkg_cstate_limits = nhm_pkg_cstate_limits;
		break;
	case INTEL_FAM6_SANDYBRIDGE:	/* SNB */
	case INTEL_FAM6_SANDYBRIDGE_X:	/* SNB Xeon */
	case INTEL_FAM6_IVYBRIDGE:	/* IVB */
	case INTEL_FAM6_IVYBRIDGE_X:	/* IVB Xeon */
		pkg_cstate_limits = snb_pkg_cstate_limits;
		has_misc_feature_control = 1;
		break;
	case INTEL_FAM6_HASWELL:	/* HSW */
	case INTEL_FAM6_HASWELL_G:	/* HSW */
	case INTEL_FAM6_HASWELL_X:	/* HSX */
	case INTEL_FAM6_HASWELL_L:	/* HSW */
	case INTEL_FAM6_BROADWELL:	/* BDW */
	case INTEL_FAM6_BROADWELL_G:	/* BDW */
	case INTEL_FAM6_BROADWELL_X:	/* BDX */
	case INTEL_FAM6_SKYLAKE_L:	/* SKL */
	case INTEL_FAM6_CANNONLAKE_L:	/* CNL */
		pkg_cstate_limits = hsw_pkg_cstate_limits;
		has_misc_feature_control = 1;
		break;
	case INTEL_FAM6_SKYLAKE_X:	/* SKX */
		pkg_cstate_limits = skx_pkg_cstate_limits;
		has_misc_feature_control = 1;
		break;
	case INTEL_FAM6_ATOM_SILVERMONT:	/* BYT */
		no_MSR_MISC_PWR_MGMT = 1;
	case INTEL_FAM6_ATOM_SILVERMONT_D:	/* AVN */
		pkg_cstate_limits = slv_pkg_cstate_limits;
		break;
	case INTEL_FAM6_ATOM_AIRMONT:	/* AMT */
		pkg_cstate_limits = amt_pkg_cstate_limits;
		no_MSR_MISC_PWR_MGMT = 1;
		break;
	case INTEL_FAM6_XEON_PHI_KNL:	/* PHI */
		pkg_cstate_limits = phi_pkg_cstate_limits;
		break;
	case INTEL_FAM6_ATOM_GOLDMONT:	/* BXT */
	case INTEL_FAM6_ATOM_GOLDMONT_PLUS:
	case INTEL_FAM6_ATOM_GOLDMONT_D:	/* DNV */
		pkg_cstate_limits = glm_pkg_cstate_limits;
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