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
typedef  int u8 ;
typedef  int u32 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_RA_MASK ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int PHYDM_BW_20 ; 
 int PHYDM_BW_40 ; 
 int PHYDM_RF_1T1R ; 
 int PHYDM_RF_2T2R ; 
 int PHYDM_RF_2T3R ; 
 int PHYDM_RF_2T4R ; 
#define  PHYDM_WIRELESS_MODE_A 134 
#define  PHYDM_WIRELESS_MODE_AC_24G 133 
#define  PHYDM_WIRELESS_MODE_AC_5G 132 
#define  PHYDM_WIRELESS_MODE_B 131 
#define  PHYDM_WIRELESS_MODE_G 130 
#define  PHYDM_WIRELESS_MODE_N_24G 129 
#define  PHYDM_WIRELESS_MODE_N_5G 128 
 int phydm_trans_platform_bw (struct phy_dm_struct*,int) ; 
 int phydm_trans_platform_rf_type (struct phy_dm_struct*,int) ; 
 int phydm_trans_platform_wireless_mode (struct phy_dm_struct*,int) ; 

void phydm_update_hal_ra_mask(void *dm_void, u32 wireless_mode, u8 rf_type,
			      u8 BW, u8 mimo_ps_enable, u8 disable_cck_rate,
			      u32 *ratr_bitmap_msb_in, u32 *ratr_bitmap_lsb_in,
			      u8 tx_rate_level)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 phydm_rf_type;
	u8 phydm_BW;
	u32 ratr_bitmap = *ratr_bitmap_lsb_in,
	    ratr_bitmap_msb = *ratr_bitmap_msb_in;

	wireless_mode = phydm_trans_platform_wireless_mode(dm, wireless_mode);

	phydm_rf_type = phydm_trans_platform_rf_type(dm, rf_type);
	phydm_BW = phydm_trans_platform_bw(dm, BW);

	ODM_RT_TRACE(dm, ODM_COMP_RA_MASK,
		     "Platform original RA Mask = (( 0x %x | %x ))\n",
		     ratr_bitmap_msb, ratr_bitmap);

	switch (wireless_mode) {
	case PHYDM_WIRELESS_MODE_B: {
		ratr_bitmap &= 0x0000000f;
	} break;

	case PHYDM_WIRELESS_MODE_G: {
		ratr_bitmap &= 0x00000ff5;
	} break;

	case PHYDM_WIRELESS_MODE_A: {
		ratr_bitmap &= 0x00000ff0;
	} break;

	case PHYDM_WIRELESS_MODE_N_24G:
	case PHYDM_WIRELESS_MODE_N_5G: {
		if (mimo_ps_enable)
			phydm_rf_type = PHYDM_RF_1T1R;

		if (phydm_rf_type == PHYDM_RF_1T1R) {
			if (phydm_BW == PHYDM_BW_40)
				ratr_bitmap &= 0x000ff015;
			else
				ratr_bitmap &= 0x000ff005;
		} else if (phydm_rf_type == PHYDM_RF_2T2R ||
			   phydm_rf_type == PHYDM_RF_2T4R ||
			   phydm_rf_type == PHYDM_RF_2T3R) {
			if (phydm_BW == PHYDM_BW_40)
				ratr_bitmap &= 0x0ffff015;
			else
				ratr_bitmap &= 0x0ffff005;
		} else { /*3T*/

			ratr_bitmap &= 0xfffff015;
			ratr_bitmap_msb &= 0xf;
		}
	} break;

	case PHYDM_WIRELESS_MODE_AC_24G: {
		if (phydm_rf_type == PHYDM_RF_1T1R) {
			ratr_bitmap &= 0x003ff015;
		} else if (phydm_rf_type == PHYDM_RF_2T2R ||
			   phydm_rf_type == PHYDM_RF_2T4R ||
			   phydm_rf_type == PHYDM_RF_2T3R) {
			ratr_bitmap &= 0xfffff015;
		} else { /*3T*/

			ratr_bitmap &= 0xfffff010;
			ratr_bitmap_msb &= 0x3ff;
		}

		if (phydm_BW ==
		    PHYDM_BW_20) { /* AC 20MHz doesn't support MCS9 */
			ratr_bitmap &= 0x7fdfffff;
			ratr_bitmap_msb &= 0x1ff;
		}
	} break;

	case PHYDM_WIRELESS_MODE_AC_5G: {
		if (phydm_rf_type == PHYDM_RF_1T1R) {
			ratr_bitmap &= 0x003ff010;
		} else if (phydm_rf_type == PHYDM_RF_2T2R ||
			   phydm_rf_type == PHYDM_RF_2T4R ||
			   phydm_rf_type == PHYDM_RF_2T3R) {
			ratr_bitmap &= 0xfffff010;
		} else { /*3T*/

			ratr_bitmap &= 0xfffff010;
			ratr_bitmap_msb &= 0x3ff;
		}

		if (phydm_BW ==
		    PHYDM_BW_20) { /* AC 20MHz doesn't support MCS9 */
			ratr_bitmap &= 0x7fdfffff;
			ratr_bitmap_msb &= 0x1ff;
		}
	} break;

	default:
		break;
	}

	if (wireless_mode != PHYDM_WIRELESS_MODE_B) {
		if (tx_rate_level == 0)
			ratr_bitmap &= 0xffffffff;
		else if (tx_rate_level == 1)
			ratr_bitmap &= 0xfffffff0;
		else if (tx_rate_level == 2)
			ratr_bitmap &= 0xffffefe0;
		else if (tx_rate_level == 3)
			ratr_bitmap &= 0xffffcfc0;
		else if (tx_rate_level == 4)
			ratr_bitmap &= 0xffff8f80;
		else if (tx_rate_level >= 5)
			ratr_bitmap &= 0xffff0f00;
	}

	if (disable_cck_rate)
		ratr_bitmap &= 0xfffffff0;

	ODM_RT_TRACE(
		dm, ODM_COMP_RA_MASK,
		"wireless_mode= (( 0x%x )), rf_type = (( 0x%x )), BW = (( 0x%x )), MimoPs_en = (( %d )), tx_rate_level= (( 0x%x ))\n",
		wireless_mode, phydm_rf_type, phydm_BW, mimo_ps_enable,
		tx_rate_level);

	*ratr_bitmap_lsb_in = ratr_bitmap;
	*ratr_bitmap_msb_in = ratr_bitmap_msb;
	ODM_RT_TRACE(dm, ODM_COMP_RA_MASK,
		     "Phydm modified RA Mask = (( 0x %x | %x ))\n",
		     *ratr_bitmap_msb_in, *ratr_bitmap_lsb_in);
}