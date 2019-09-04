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
typedef  int u32 ;
struct ieee80211_ht_cap {int dummy; } ;
struct add_sta_param {int aid; int rates_len; int flags_mask; int flags_set; int /*<<< orphan*/  ht_capa; int /*<<< orphan*/  ht_supported; int /*<<< orphan*/ * rates; int /*<<< orphan*/ * bssid; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u32 wilc_hif_pack_sta_param(u8 *buff, struct add_sta_param *param)
{
	u8 *cur_byte;

	cur_byte = buff;

	memcpy(cur_byte, param->bssid, ETH_ALEN);
	cur_byte +=  ETH_ALEN;

	*cur_byte++ = param->aid & 0xFF;
	*cur_byte++ = (param->aid >> 8) & 0xFF;

	*cur_byte++ = param->rates_len;
	if (param->rates_len > 0)
		memcpy(cur_byte, param->rates, param->rates_len);
	cur_byte += param->rates_len;

	*cur_byte++ = param->ht_supported;
	memcpy(cur_byte, &param->ht_capa, sizeof(struct ieee80211_ht_cap));
	cur_byte += sizeof(struct ieee80211_ht_cap);

	*cur_byte++ = param->flags_mask & 0xFF;
	*cur_byte++ = (param->flags_mask >> 8) & 0xFF;

	*cur_byte++ = param->flags_set & 0xFF;
	*cur_byte++ = (param->flags_set >> 8) & 0xFF;

	return cur_byte - buff;
}