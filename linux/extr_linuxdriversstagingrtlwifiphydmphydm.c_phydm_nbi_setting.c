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
 int NBI_DISABLE ; 
 int /*<<< orphan*/  ODM_COMP_API ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int,int,int,char*) ; 
 int PHYDM_ABOVE ; 
 int PHYDM_DONT_CARE ; 
 scalar_t__ SET_ERROR ; 
 scalar_t__ SET_NO_NEED ; 
 scalar_t__ SET_SUCCESS ; 
 scalar_t__ phydm_calculate_fc (struct phy_dm_struct*,int,int,int,int*) ; 
 scalar_t__ phydm_calculate_intf_distance (struct phy_dm_struct*,int,int,int,int*) ; 
 int /*<<< orphan*/  phydm_nbi_enable (struct phy_dm_struct*,int) ; 
 int /*<<< orphan*/  phydm_set_nbi_reg (struct phy_dm_struct*,int,int) ; 

u8 phydm_nbi_setting(void *dm_void, u32 enable, u32 channel, u32 bw,
		     u32 f_interference, u32 second_ch)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 fc;
	u32 tone_idx_tmp;
	u8 set_result = SET_SUCCESS;

	if (enable == NBI_DISABLE) {
		set_result = SET_SUCCESS;
	} else {
		ODM_RT_TRACE(
			dm, ODM_COMP_API,
			"[Set NBI] CH = ((%d)), BW = ((%d)), f_intf = ((%d)), Scnd_CH = ((%s))\n",
			channel, bw, f_interference,
			(((second_ch == PHYDM_DONT_CARE) || (bw == 20) ||
			  (channel > 14)) ?
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
				phydm_set_nbi_reg(dm, tone_idx_tmp, bw);
				set_result = SET_SUCCESS;
			} else {
				set_result = SET_NO_NEED;
			}
		}
	}

	if (set_result == SET_SUCCESS)
		phydm_nbi_enable(dm, enable);
	else
		phydm_nbi_enable(dm, NBI_DISABLE);

	return set_result;
}