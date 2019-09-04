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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int CSI_MASK_DISABLE ; 
 scalar_t__ FREQ_NEGATIVE ; 
 scalar_t__ FREQ_POSITIVE ; 
 int /*<<< orphan*/  ODM_COMP_API ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int,int,int,char*) ; 
 int PHYDM_ABOVE ; 
 scalar_t__ SET_ERROR ; 
 scalar_t__ SET_NO_NEED ; 
 scalar_t__ SET_SUCCESS ; 
 scalar_t__ phydm_calculate_fc (struct phy_dm_struct*,int,int,int,int*) ; 
 scalar_t__ phydm_calculate_intf_distance (struct phy_dm_struct*,int,int,int,int*) ; 
 int /*<<< orphan*/  phydm_clean_all_csi_mask (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_csi_mask_enable (struct phy_dm_struct*,int) ; 
 int /*<<< orphan*/  phydm_set_csi_mask_reg (struct phy_dm_struct*,int,scalar_t__) ; 

__attribute__((used)) static u8 phydm_csi_mask_setting(void *dm_void, u32 enable, u32 channel, u32 bw,
				 u32 f_interference, u32 second_ch)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 fc;
	u8 tone_direction;
	u32 tone_idx_tmp;
	u8 set_result = SET_SUCCESS;

	if (enable == CSI_MASK_DISABLE) {
		set_result = SET_SUCCESS;
		phydm_clean_all_csi_mask(dm);

	} else {
		ODM_RT_TRACE(
			dm, ODM_COMP_API,
			"[Set CSI MASK_] CH = ((%d)), BW = ((%d)), f_intf = ((%d)), Scnd_CH = ((%s))\n",
			channel, bw, f_interference,
			(((bw == 20) || (channel > 14)) ?
				 "Don't care" :
				 (second_ch == PHYDM_ABOVE) ? "H" : "L"));

		/*calculate fc*/
		if (phydm_calculate_fc(dm, channel, bw, second_ch, &fc) ==
		    SET_ERROR) {
			set_result = SET_ERROR;
		} else {
			/*calculate interference distance*/
			if (phydm_calculate_intf_distance(
				    dm, bw, fc, f_interference,
				    &tone_idx_tmp) == SET_SUCCESS) {
				tone_direction = (f_interference >= fc) ?
							 FREQ_POSITIVE :
							 FREQ_NEGATIVE;
				phydm_set_csi_mask_reg(dm, tone_idx_tmp,
						       tone_direction);
				set_result = SET_SUCCESS;
			} else {
				set_result = SET_NO_NEED;
			}
		}
	}

	if (set_result == SET_SUCCESS)
		phydm_csi_mask_enable(dm, enable);
	else
		phydm_csi_mask_enable(dm, CSI_MASK_DISABLE);

	return set_result;
}