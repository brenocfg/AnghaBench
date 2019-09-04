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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_RA_MASK ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  PHYDM_ARFR0_AC_2SS ; 
 int /*<<< orphan*/  PHYDM_ARFR1_AC_1SS ; 
 int /*<<< orphan*/  PHYDM_ARFR2_AC_2G_1SS ; 
 int /*<<< orphan*/  PHYDM_ARFR3_AC_2G_2SS ; 
 int /*<<< orphan*/  PHYDM_ARFR4_AC_3SS ; 
 int /*<<< orphan*/  PHYDM_ARFR5_N_3SS ; 
 int /*<<< orphan*/  PHYDM_BG ; 
 int /*<<< orphan*/  PHYDM_BGN_20M_1SS ; 
 int /*<<< orphan*/  PHYDM_BGN_20M_2SS ; 
 int /*<<< orphan*/  PHYDM_BGN_40M_1SS ; 
 int /*<<< orphan*/  PHYDM_BGN_40M_2SS ; 
 int /*<<< orphan*/  PHYDM_BW_40 ; 
 int /*<<< orphan*/  PHYDM_BW_80 ; 
 int /*<<< orphan*/  PHYDM_B_20M ; 
 int /*<<< orphan*/  PHYDM_G ; 
 int /*<<< orphan*/  PHYDM_GN_N1SS ; 
 int /*<<< orphan*/  PHYDM_GN_N2SS ; 
 int /*<<< orphan*/  PHYDM_RF_1T1R ; 
 int /*<<< orphan*/  PHYDM_RF_2T2R ; 
#define  PHYDM_WIRELESS_MODE_A 135 
#define  PHYDM_WIRELESS_MODE_AC_24G 134 
#define  PHYDM_WIRELESS_MODE_AC_5G 133 
#define  PHYDM_WIRELESS_MODE_AC_ONLY 132 
#define  PHYDM_WIRELESS_MODE_B 131 
#define  PHYDM_WIRELESS_MODE_G 130 
#define  PHYDM_WIRELESS_MODE_N_24G 129 
#define  PHYDM_WIRELESS_MODE_N_5G 128 
 int /*<<< orphan*/  phydm_trans_platform_bw (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_trans_platform_rf_type (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_trans_platform_wireless_mode (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 

u8 phydm_rate_id_mapping(void *dm_void, u32 wireless_mode, u8 rf_type, u8 bw)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 rate_id_idx = 0;
	u8 phydm_BW;
	u8 phydm_rf_type;

	phydm_BW = phydm_trans_platform_bw(dm, bw);
	phydm_rf_type = phydm_trans_platform_rf_type(dm, rf_type);
	wireless_mode = phydm_trans_platform_wireless_mode(dm, wireless_mode);

	ODM_RT_TRACE(
		dm, ODM_COMP_RA_MASK,
		"wireless_mode= (( 0x%x )), rf_type = (( 0x%x )), BW = (( 0x%x ))\n",
		wireless_mode, phydm_rf_type, phydm_BW);

	switch (wireless_mode) {
	case PHYDM_WIRELESS_MODE_N_24G: {
		if (phydm_BW == PHYDM_BW_40) {
			if (phydm_rf_type == PHYDM_RF_1T1R)
				rate_id_idx = PHYDM_BGN_40M_1SS;
			else if (phydm_rf_type == PHYDM_RF_2T2R)
				rate_id_idx = PHYDM_BGN_40M_2SS;
			else
				rate_id_idx = PHYDM_ARFR5_N_3SS;

		} else {
			if (phydm_rf_type == PHYDM_RF_1T1R)
				rate_id_idx = PHYDM_BGN_20M_1SS;
			else if (phydm_rf_type == PHYDM_RF_2T2R)
				rate_id_idx = PHYDM_BGN_20M_2SS;
			else
				rate_id_idx = PHYDM_ARFR5_N_3SS;
		}
	} break;

	case PHYDM_WIRELESS_MODE_N_5G: {
		if (phydm_rf_type == PHYDM_RF_1T1R)
			rate_id_idx = PHYDM_GN_N1SS;
		else if (phydm_rf_type == PHYDM_RF_2T2R)
			rate_id_idx = PHYDM_GN_N2SS;
		else
			rate_id_idx = PHYDM_ARFR5_N_3SS;
	}

	break;

	case PHYDM_WIRELESS_MODE_G:
		rate_id_idx = PHYDM_BG;
		break;

	case PHYDM_WIRELESS_MODE_A:
		rate_id_idx = PHYDM_G;
		break;

	case PHYDM_WIRELESS_MODE_B:
		rate_id_idx = PHYDM_B_20M;
		break;

	case PHYDM_WIRELESS_MODE_AC_5G:
	case PHYDM_WIRELESS_MODE_AC_ONLY: {
		if (phydm_rf_type == PHYDM_RF_1T1R)
			rate_id_idx = PHYDM_ARFR1_AC_1SS;
		else if (phydm_rf_type == PHYDM_RF_2T2R)
			rate_id_idx = PHYDM_ARFR0_AC_2SS;
		else
			rate_id_idx = PHYDM_ARFR4_AC_3SS;
	} break;

	case PHYDM_WIRELESS_MODE_AC_24G: {
		/*Becareful to set "Lowest rate" while using PHYDM_ARFR4_AC_3SS
		 *in 2.4G/5G
		 */
		if (phydm_BW >= PHYDM_BW_80) {
			if (phydm_rf_type == PHYDM_RF_1T1R)
				rate_id_idx = PHYDM_ARFR1_AC_1SS;
			else if (phydm_rf_type == PHYDM_RF_2T2R)
				rate_id_idx = PHYDM_ARFR0_AC_2SS;
			else
				rate_id_idx = PHYDM_ARFR4_AC_3SS;
		} else {
			if (phydm_rf_type == PHYDM_RF_1T1R)
				rate_id_idx = PHYDM_ARFR2_AC_2G_1SS;
			else if (phydm_rf_type == PHYDM_RF_2T2R)
				rate_id_idx = PHYDM_ARFR3_AC_2G_2SS;
			else
				rate_id_idx = PHYDM_ARFR4_AC_3SS;
		}
	} break;

	default:
		rate_id_idx = 0;
		break;
	}

	ODM_RT_TRACE(dm, ODM_COMP_RA_MASK, "RA rate ID = (( 0x%x ))\n",
		     rate_id_idx);

	return rate_id_idx;
}