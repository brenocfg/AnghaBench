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
typedef  scalar_t__ u32 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ CSI_MASK_DISABLE ; 
 scalar_t__ CSI_MASK_ENABLE ; 
 scalar_t__ NBI_DISABLE ; 
 scalar_t__ NBI_ENABLE ; 
 scalar_t__ PHYDM_ABOVE ; 
 scalar_t__ PHYDM_API_CSI_MASK ; 
 scalar_t__ PHYDM_API_NBI ; 
 scalar_t__ PHYDM_DONT_CARE ; 
 int /*<<< orphan*/  PHYDM_SNPRINTF (char*,scalar_t__,char*,...) ; 
 scalar_t__ SET_ERROR ; 
 scalar_t__ SET_NO_NEED ; 
 scalar_t__ SET_SUCCESS ; 
 scalar_t__ phydm_csi_mask_setting (struct phy_dm_struct*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ phydm_nbi_setting (struct phy_dm_struct*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

void phydm_api_debug(void *dm_void, u32 function_map, u32 *const dm_value,
		     u32 *_used, char *output, u32 *_out_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 used = *_used;
	u32 out_len = *_out_len;
	u32 channel = dm_value[1];
	u32 bw = dm_value[2];
	u32 f_interference = dm_value[3];
	u32 second_ch = dm_value[4];
	u8 set_result = 0;

	/*PHYDM_API_NBI*/
	/*--------------------------------------------------------------------*/
	if (function_map == PHYDM_API_NBI) {
		if (dm_value[0] == 100) {
			PHYDM_SNPRINTF(
				output + used, out_len - used,
				"[HELP-NBI]  EN(on=1, off=2)   CH   BW(20/40/80)  f_intf(Mhz)    Scnd_CH(L=1, H=2)\n");
			return;

		} else if (dm_value[0] == NBI_ENABLE) {
			PHYDM_SNPRINTF(
				output + used, out_len - used,
				"[Enable NBI] CH = ((%d)), BW = ((%d)), f_intf = ((%d)), Scnd_CH = ((%s))\n",
				channel, bw, f_interference,
				((second_ch == PHYDM_DONT_CARE) || (bw == 20) ||
				 (channel > 14)) ?
					"Don't care" :
					((second_ch == PHYDM_ABOVE) ? "H" :
								      "L"));
			set_result =
				phydm_nbi_setting(dm, NBI_ENABLE, channel, bw,
						  f_interference, second_ch);

		} else if (dm_value[0] == NBI_DISABLE) {
			PHYDM_SNPRINTF(output + used, out_len - used,
				       "[Disable NBI]\n");
			set_result =
				phydm_nbi_setting(dm, NBI_DISABLE, channel, bw,
						  f_interference, second_ch);

		} else {
			set_result = SET_ERROR;
		}

		PHYDM_SNPRINTF(
			output + used, out_len - used, "[NBI set result: %s]\n",
			(set_result == SET_SUCCESS) ?
				"Success" :
				((set_result == SET_NO_NEED) ? "No need" :
							       "Error"));
	}

	/*PHYDM_CSI_MASK*/
	/*--------------------------------------------------------------------*/
	else if (function_map == PHYDM_API_CSI_MASK) {
		if (dm_value[0] == 100) {
			PHYDM_SNPRINTF(
				output + used, out_len - used,
				"[HELP-CSI MASK]  EN(on=1, off=2)   CH   BW(20/40/80)  f_intf(Mhz)    Scnd_CH(L=1, H=2)\n");
			return;

		} else if (dm_value[0] == CSI_MASK_ENABLE) {
			PHYDM_SNPRINTF(
				output + used, out_len - used,
				"[Enable CSI MASK] CH = ((%d)), BW = ((%d)), f_intf = ((%d)), Scnd_CH = ((%s))\n",
				channel, bw, f_interference,
				(channel > 14) ?
					"Don't care" :
					(((second_ch == PHYDM_DONT_CARE) ||
					  (bw == 20) || (channel > 14)) ?
						 "H" :
						 "L"));
			set_result = phydm_csi_mask_setting(
				dm, CSI_MASK_ENABLE, channel, bw,
				f_interference, second_ch);

		} else if (dm_value[0] == CSI_MASK_DISABLE) {
			PHYDM_SNPRINTF(output + used, out_len - used,
				       "[Disable CSI MASK]\n");
			set_result = phydm_csi_mask_setting(
				dm, CSI_MASK_DISABLE, channel, bw,
				f_interference, second_ch);

		} else {
			set_result = SET_ERROR;
		}

		PHYDM_SNPRINTF(output + used, out_len - used,
			       "[CSI MASK set result: %s]\n",
			       (set_result == SET_SUCCESS) ?
				       "Success" :
				       ((set_result == SET_NO_NEED) ?
						"No need" :
						"Error"));
	}
}