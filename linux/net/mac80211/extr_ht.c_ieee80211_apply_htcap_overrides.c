#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_11__ {int /*<<< orphan*/  rx_mask; } ;
struct ieee80211_ht_cap {int cap_info; int ampdu_params_info; TYPE_5__ mcs; } ;
struct TYPE_9__ {struct ieee80211_ht_cap ht_capa_mask; struct ieee80211_ht_cap ht_capa; } ;
struct TYPE_8__ {struct ieee80211_ht_cap ht_capa_mask; struct ieee80211_ht_cap ht_capa; } ;
struct TYPE_10__ {TYPE_3__ ibss; TYPE_2__ mgd; } ;
struct TYPE_7__ {int type; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; TYPE_1__ vif; } ;
struct TYPE_12__ {scalar_t__* rx_mask; } ;
struct ieee80211_sta_ht_cap {int cap; scalar_t__ ampdu_factor; scalar_t__ ampdu_density; TYPE_6__ mcs; int /*<<< orphan*/  ht_supported; } ;

/* Variables and functions */
 int IEEE80211_HT_AMPDU_PARM_DENSITY ; 
 int IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT ; 
 int IEEE80211_HT_AMPDU_PARM_FACTOR ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_40MHZ_INTOLERANT ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_LDPC_CODING ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_MAX_AMSDU ; 
 int IEEE80211_HT_CAP_RX_STBC ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_20 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_40 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_TX_STBC ; 
 int IEEE80211_HT_MCS_MASK_LEN ; 
#define  NL80211_IFTYPE_ADHOC 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __check_htcap_disable (struct ieee80211_ht_cap*,struct ieee80211_ht_cap*,struct ieee80211_sta_ht_cap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __check_htcap_enable (struct ieee80211_ht_cap*,struct ieee80211_ht_cap*,struct ieee80211_sta_ht_cap*,int /*<<< orphan*/ ) ; 
 int cpu_to_le16 (int) ; 
 int le16_to_cpu (int) ; 

void ieee80211_apply_htcap_overrides(struct ieee80211_sub_if_data *sdata,
				     struct ieee80211_sta_ht_cap *ht_cap)
{
	struct ieee80211_ht_cap *ht_capa, *ht_capa_mask;
	u8 *scaps, *smask;
	int i;

	if (!ht_cap->ht_supported)
		return;

	switch (sdata->vif.type) {
	case NL80211_IFTYPE_STATION:
		ht_capa = &sdata->u.mgd.ht_capa;
		ht_capa_mask = &sdata->u.mgd.ht_capa_mask;
		break;
	case NL80211_IFTYPE_ADHOC:
		ht_capa = &sdata->u.ibss.ht_capa;
		ht_capa_mask = &sdata->u.ibss.ht_capa_mask;
		break;
	default:
		WARN_ON_ONCE(1);
		return;
	}

	scaps = (u8 *)(&ht_capa->mcs.rx_mask);
	smask = (u8 *)(&ht_capa_mask->mcs.rx_mask);

	/* NOTE:  If you add more over-rides here, update register_hw
	 * ht_capa_mod_mask logic in main.c as well.
	 * And, if this method can ever change ht_cap.ht_supported, fix
	 * the check in ieee80211_add_ht_ie.
	 */

	/* check for HT over-rides, MCS rates first. */
	for (i = 0; i < IEEE80211_HT_MCS_MASK_LEN; i++) {
		u8 m = smask[i];
		ht_cap->mcs.rx_mask[i] &= ~m; /* turn off all masked bits */
		/* Add back rates that are supported */
		ht_cap->mcs.rx_mask[i] |= (m & scaps[i]);
	}

	/* Force removal of HT-40 capabilities? */
	__check_htcap_disable(ht_capa, ht_capa_mask, ht_cap,
			      IEEE80211_HT_CAP_SUP_WIDTH_20_40);
	__check_htcap_disable(ht_capa, ht_capa_mask, ht_cap,
			      IEEE80211_HT_CAP_SGI_40);

	/* Allow user to disable SGI-20 (SGI-40 is handled above) */
	__check_htcap_disable(ht_capa, ht_capa_mask, ht_cap,
			      IEEE80211_HT_CAP_SGI_20);

	/* Allow user to disable the max-AMSDU bit. */
	__check_htcap_disable(ht_capa, ht_capa_mask, ht_cap,
			      IEEE80211_HT_CAP_MAX_AMSDU);

	/* Allow user to disable LDPC */
	__check_htcap_disable(ht_capa, ht_capa_mask, ht_cap,
			      IEEE80211_HT_CAP_LDPC_CODING);

	/* Allow user to enable 40 MHz intolerant bit. */
	__check_htcap_enable(ht_capa, ht_capa_mask, ht_cap,
			     IEEE80211_HT_CAP_40MHZ_INTOLERANT);

	/* Allow user to enable TX STBC bit  */
	__check_htcap_enable(ht_capa, ht_capa_mask, ht_cap,
			     IEEE80211_HT_CAP_TX_STBC);

	/* Allow user to configure RX STBC bits */
	if (ht_capa_mask->cap_info & cpu_to_le16(IEEE80211_HT_CAP_RX_STBC))
		ht_cap->cap |= le16_to_cpu(ht_capa->cap_info) &
					IEEE80211_HT_CAP_RX_STBC;

	/* Allow user to decrease AMPDU factor */
	if (ht_capa_mask->ampdu_params_info &
	    IEEE80211_HT_AMPDU_PARM_FACTOR) {
		u8 n = ht_capa->ampdu_params_info &
		       IEEE80211_HT_AMPDU_PARM_FACTOR;
		if (n < ht_cap->ampdu_factor)
			ht_cap->ampdu_factor = n;
	}

	/* Allow the user to increase AMPDU density. */
	if (ht_capa_mask->ampdu_params_info &
	    IEEE80211_HT_AMPDU_PARM_DENSITY) {
		u8 n = (ht_capa->ampdu_params_info &
			IEEE80211_HT_AMPDU_PARM_DENSITY)
			>> IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT;
		if (n > ht_cap->ampdu_density)
			ht_cap->ampdu_density = n;
	}
}