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
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
#define  ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED 134 
#define  ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED 133 
#define  ALUA_ACCESS_STATE_LBA_DEPENDENT 132 
#define  ALUA_ACCESS_STATE_OFFLINE 131 
#define  ALUA_ACCESS_STATE_STANDBY 130 
#define  ALUA_ACCESS_STATE_TRANSITION 129 
#define  ALUA_ACCESS_STATE_UNAVAILABLE 128 
 int ALUA_AN_SUP ; 
 int ALUA_AO_SUP ; 
 int ALUA_LBD_SUP ; 
 int ALUA_O_SUP ; 
 int ALUA_S_SUP ; 
 int ALUA_T_SUP ; 
 int ALUA_U_SUP ; 
 int /*<<< orphan*/  TCM_INVALID_PARAMETER_LIST ; 
 int core_alua_dump_state (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static sense_reason_t
core_alua_check_transition(int state, int valid, int *primary, int explicit)
{
	/*
	 * OPTIMIZED, NON-OPTIMIZED, STANDBY and UNAVAILABLE are
	 * defined as primary target port asymmetric access states.
	 */
	switch (state) {
	case ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED:
		if (!(valid & ALUA_AO_SUP))
			goto not_supported;
		*primary = 1;
		break;
	case ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED:
		if (!(valid & ALUA_AN_SUP))
			goto not_supported;
		*primary = 1;
		break;
	case ALUA_ACCESS_STATE_STANDBY:
		if (!(valid & ALUA_S_SUP))
			goto not_supported;
		*primary = 1;
		break;
	case ALUA_ACCESS_STATE_UNAVAILABLE:
		if (!(valid & ALUA_U_SUP))
			goto not_supported;
		*primary = 1;
		break;
	case ALUA_ACCESS_STATE_LBA_DEPENDENT:
		if (!(valid & ALUA_LBD_SUP))
			goto not_supported;
		*primary = 1;
		break;
	case ALUA_ACCESS_STATE_OFFLINE:
		/*
		 * OFFLINE state is defined as a secondary target port
		 * asymmetric access state.
		 */
		if (!(valid & ALUA_O_SUP))
			goto not_supported;
		*primary = 0;
		break;
	case ALUA_ACCESS_STATE_TRANSITION:
		if (!(valid & ALUA_T_SUP) || explicit)
			/*
			 * Transitioning is set internally and by tcmu daemon,
			 * and cannot be selected through a STPG.
			 */
			goto not_supported;
		*primary = 0;
		break;
	default:
		pr_err("Unknown ALUA access state: 0x%02x\n", state);
		return TCM_INVALID_PARAMETER_LIST;
	}

	return 0;

not_supported:
	pr_err("ALUA access state %s not supported",
	       core_alua_dump_state(state));
	return TCM_INVALID_PARAMETER_LIST;
}