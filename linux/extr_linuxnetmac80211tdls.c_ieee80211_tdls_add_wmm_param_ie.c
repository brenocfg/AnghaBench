#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct ieee80211_wmm_param_ie {int len; int* oui; int oui_type; int oui_subtype; int version; TYPE_1__* ac; scalar_t__ qos_info; int /*<<< orphan*/  element_id; } ;
struct ieee80211_tx_queue_params {int /*<<< orphan*/  txop; int /*<<< orphan*/  cw_max; int /*<<< orphan*/  cw_min; int /*<<< orphan*/  acm; int /*<<< orphan*/  aifs; } ;
struct ieee80211_sub_if_data {struct ieee80211_tx_queue_params* tx_conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  txop_limit; int /*<<< orphan*/  cw; int /*<<< orphan*/  aci_aifsn; } ;

/* Variables and functions */
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 size_t ieee80211_ac_from_wmm (int) ; 
 int /*<<< orphan*/  ieee80211_wmm_aci_aifsn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_wmm_ecw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_wmm_param_ie* skb_put_zero (struct sk_buff*,int) ; 

__attribute__((used)) static void ieee80211_tdls_add_wmm_param_ie(struct ieee80211_sub_if_data *sdata,
					    struct sk_buff *skb)
{
	struct ieee80211_wmm_param_ie *wmm;
	struct ieee80211_tx_queue_params *txq;
	int i;

	wmm = skb_put_zero(skb, sizeof(*wmm));

	wmm->element_id = WLAN_EID_VENDOR_SPECIFIC;
	wmm->len = sizeof(*wmm) - 2;

	wmm->oui[0] = 0x00; /* Microsoft OUI 00:50:F2 */
	wmm->oui[1] = 0x50;
	wmm->oui[2] = 0xf2;
	wmm->oui_type = 2; /* WME */
	wmm->oui_subtype = 1; /* WME param */
	wmm->version = 1; /* WME ver */
	wmm->qos_info = 0; /* U-APSD not in use */

	/*
	 * Use the EDCA parameters defined for the BSS, or default if the AP
	 * doesn't support it, as mandated by 802.11-2012 section 10.22.4
	 */
	for (i = 0; i < IEEE80211_NUM_ACS; i++) {
		txq = &sdata->tx_conf[ieee80211_ac_from_wmm(i)];
		wmm->ac[i].aci_aifsn = ieee80211_wmm_aci_aifsn(txq->aifs,
							       txq->acm, i);
		wmm->ac[i].cw = ieee80211_wmm_ecw(txq->cw_min, txq->cw_max);
		wmm->ac[i].txop_limit = cpu_to_le16(txq->txop);
	}
}