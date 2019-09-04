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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct join_bss_param {int* supp_rates; int ht_capable; int wmm_cap; int uapsd_cap; int noa_enabled; int idx; int opp_enabled; int ct_window; int cnt; int mode_802_11i; int rsn_grp_policy; int* rsn_pcip_policy; int* rsn_auth_policy; int* rsn_cap; int rsn_found; int /*<<< orphan*/  start_time; int /*<<< orphan*/  interval; int /*<<< orphan*/  duration; int /*<<< orphan*/  tsf; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MAX_RATES_SUPPORTED ; 
 int WLAN_EID_EXT_SUPP_RATES ; 
 int WLAN_EID_HT_CAPABILITY ; 
 int WLAN_EID_RSN ; 
 int WLAN_EID_SUPP_RATES ; 
 int WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void host_int_fill_join_bss_param(struct join_bss_param *param, u8 *ies,
					 u16 *out_index, u8 *pcipher_tc,
					 u8 *auth_total_cnt, u32 tsf_lo,
					 u8 *rates_no)
{
	u8 ext_rates_no;
	u16 offset;
	u8 pcipher_cnt;
	u8 auth_cnt;
	u8 i, j;
	u16 index = *out_index;

	if (ies[index] == WLAN_EID_SUPP_RATES) {
		*rates_no = ies[index + 1];
		param->supp_rates[0] = *rates_no;
		index += 2;

		for (i = 0; i < *rates_no; i++)
			param->supp_rates[i + 1] = ies[index + i];

		index += *rates_no;
	} else if (ies[index] == WLAN_EID_EXT_SUPP_RATES) {
		ext_rates_no = ies[index + 1];
		if (ext_rates_no > (MAX_RATES_SUPPORTED - *rates_no))
			param->supp_rates[0] = MAX_RATES_SUPPORTED;
		else
			param->supp_rates[0] += ext_rates_no;
		index += 2;
		for (i = 0; i < (param->supp_rates[0] - *rates_no); i++)
			param->supp_rates[*rates_no + i + 1] = ies[index + i];

		index += ext_rates_no;
	} else if (ies[index] == WLAN_EID_HT_CAPABILITY) {
		param->ht_capable = true;
		index += ies[index + 1] + 2;
	} else if ((ies[index] == WLAN_EID_VENDOR_SPECIFIC) &&
		   (ies[index + 2] == 0x00) && (ies[index + 3] == 0x50) &&
		   (ies[index + 4] == 0xF2) && (ies[index + 5] == 0x02) &&
		   ((ies[index + 6] == 0x00) || (ies[index + 6] == 0x01)) &&
		   (ies[index + 7] == 0x01)) {
		param->wmm_cap = true;

		if (ies[index + 8] & BIT(7))
			param->uapsd_cap = true;
		index += ies[index + 1] + 2;
	} else if ((ies[index] == WLAN_EID_VENDOR_SPECIFIC) &&
		 (ies[index + 2] == 0x50) && (ies[index + 3] == 0x6f) &&
		 (ies[index + 4] == 0x9a) &&
		 (ies[index + 5] == 0x09) && (ies[index + 6] == 0x0c)) {
		u16 p2p_cnt;

		param->tsf = tsf_lo;
		param->noa_enabled = 1;
		param->idx = ies[index + 9];

		if (ies[index + 10] & BIT(7)) {
			param->opp_enabled = 1;
			param->ct_window = ies[index + 10];
		} else {
			param->opp_enabled = 0;
		}

		param->cnt = ies[index + 11];
		p2p_cnt = index + 12;

		memcpy(param->duration, ies + p2p_cnt, 4);
		p2p_cnt += 4;

		memcpy(param->interval, ies + p2p_cnt, 4);
		p2p_cnt += 4;

		memcpy(param->start_time, ies + p2p_cnt, 4);

		index += ies[index + 1] + 2;
	} else if ((ies[index] == WLAN_EID_RSN) ||
		 ((ies[index] == WLAN_EID_VENDOR_SPECIFIC) &&
		  (ies[index + 2] == 0x00) &&
		  (ies[index + 3] == 0x50) && (ies[index + 4] == 0xF2) &&
		  (ies[index + 5] == 0x01))) {
		u16 rsn_idx = index;

		if (ies[rsn_idx] == WLAN_EID_RSN) {
			param->mode_802_11i = 2;
		} else {
			if (param->mode_802_11i == 0)
				param->mode_802_11i = 1;
			rsn_idx += 4;
		}

		rsn_idx += 7;
		param->rsn_grp_policy = ies[rsn_idx];
		rsn_idx++;
		offset = ies[rsn_idx] * 4;
		pcipher_cnt = (ies[rsn_idx] > 3) ? 3 : ies[rsn_idx];
		rsn_idx += 2;

		i = *pcipher_tc;
		j = 0;
		for (; i < (pcipher_cnt + *pcipher_tc) && i < 3; i++, j++) {
			u8 *policy =  &param->rsn_pcip_policy[i];

			*policy = ies[rsn_idx + ((j + 1) * 4) - 1];
		}

		*pcipher_tc += pcipher_cnt;
		rsn_idx += offset;

		offset = ies[rsn_idx] * 4;

		auth_cnt = (ies[rsn_idx] > 3) ? 3 : ies[rsn_idx];
		rsn_idx += 2;
		i = *auth_total_cnt;
		j = 0;
		for (; i < (*auth_total_cnt + auth_cnt); i++, j++) {
			u8 *policy =  &param->rsn_auth_policy[i];

			*policy = ies[rsn_idx + ((j + 1) * 4) - 1];
		}

		*auth_total_cnt += auth_cnt;
		rsn_idx += offset;

		if (ies[index] == WLAN_EID_RSN) {
			param->rsn_cap[0] = ies[rsn_idx];
			param->rsn_cap[1] = ies[rsn_idx + 1];
			rsn_idx += 2;
		}
		param->rsn_found = true;
		index += ies[index + 1] + 2;
	} else {
		index += ies[index + 1] + 2;
	}

	*out_index = index;
}