#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
struct ieee80211_vht_operation {int dummy; } ;
struct ieee80211_vht_cap {int dummy; } ;
struct TYPE_12__ {scalar_t__ vht_supported; } ;
struct TYPE_11__ {scalar_t__ ht_supported; } ;
struct ieee80211_supported_band {size_t n_channels; TYPE_6__* channels; TYPE_5__ vht_cap; TYPE_4__ ht_cap; } ;
struct ieee80211_if_managed {int flags; } ;
struct TYPE_8__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  smps_mode; int /*<<< orphan*/  needed_rx_chains; TYPE_1__ u; struct ieee80211_local* local; } ;
struct TYPE_10__ {TYPE_2__* wiphy; } ;
struct ieee80211_local {int /*<<< orphan*/  mtx; int /*<<< orphan*/  rx_chains; TYPE_3__ hw; } ;
struct ieee80211_ht_operation {int dummy; } ;
struct ieee80211_ht_cap {int dummy; } ;
struct ieee80211_he_operation {int dummy; } ;
struct cfg80211_chan_def {scalar_t__ width; } ;
struct cfg80211_bss_ies {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct cfg80211_bss {TYPE_7__* channel; int /*<<< orphan*/  ies; } ;
struct TYPE_14__ {size_t band; } ;
struct TYPE_13__ {int flags; } ;
struct TYPE_9__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHANCTX_SHARED ; 
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_CHAN_NO_80MHZ ; 
 int /*<<< orphan*/  IEEE80211_SMPS_OFF ; 
 int IEEE80211_STA_DISABLE_160MHZ ; 
 int IEEE80211_STA_DISABLE_40MHZ ; 
 int IEEE80211_STA_DISABLE_80P80MHZ ; 
 int IEEE80211_STA_DISABLE_HE ; 
 int IEEE80211_STA_DISABLE_HT ; 
 int IEEE80211_STA_DISABLE_VHT ; 
 scalar_t__ NL80211_CHAN_WIDTH_10 ; 
 scalar_t__ NL80211_CHAN_WIDTH_20_NOHT ; 
 scalar_t__ NL80211_CHAN_WIDTH_5 ; 
 int /*<<< orphan*/  WLAN_EID_EXT_HE_OPERATION ; 
 int /*<<< orphan*/  WLAN_EID_HT_CAPABILITY ; 
 int /*<<< orphan*/  WLAN_EID_HT_OPERATION ; 
 int /*<<< orphan*/  WLAN_EID_VHT_CAPABILITY ; 
 int /*<<< orphan*/  WLAN_EID_VHT_OPERATION ; 
 int* cfg80211_find_ext_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* ieee80211_bss_get_ie (struct cfg80211_bss*,int /*<<< orphan*/ ) ; 
 int ieee80211_chandef_downgrade (struct cfg80211_chan_def*) ; 
 int ieee80211_determine_chantype (struct ieee80211_sub_if_data*,struct ieee80211_supported_band*,TYPE_7__*,struct ieee80211_ht_operation const*,struct ieee80211_vht_operation const*,struct ieee80211_he_operation const*,struct cfg80211_chan_def*,int) ; 
 int /*<<< orphan*/  ieee80211_get_he_sta_cap (struct ieee80211_supported_band*) ; 
 int const ieee80211_he_oper_size (int const*) ; 
 int /*<<< orphan*/  ieee80211_ht_vht_rx_chains (struct ieee80211_sub_if_data*,struct cfg80211_bss*) ; 
 int /*<<< orphan*/  ieee80211_verify_sta_he_mcs_support (struct ieee80211_supported_band*,struct ieee80211_he_operation const*) ; 
 int ieee80211_vif_use_channel (struct ieee80211_sub_if_data*,struct cfg80211_chan_def*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cfg80211_bss_ies* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*) ; 

__attribute__((used)) static int ieee80211_prep_channel(struct ieee80211_sub_if_data *sdata,
				  struct cfg80211_bss *cbss)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	const struct ieee80211_ht_cap *ht_cap = NULL;
	const struct ieee80211_ht_operation *ht_oper = NULL;
	const struct ieee80211_vht_operation *vht_oper = NULL;
	const struct ieee80211_he_operation *he_oper = NULL;
	struct ieee80211_supported_band *sband;
	struct cfg80211_chan_def chandef;
	int ret;
	u32 i;
	bool have_80mhz;

	sband = local->hw.wiphy->bands[cbss->channel->band];

	ifmgd->flags &= ~(IEEE80211_STA_DISABLE_40MHZ |
			  IEEE80211_STA_DISABLE_80P80MHZ |
			  IEEE80211_STA_DISABLE_160MHZ);

	rcu_read_lock();

	if (!(ifmgd->flags & IEEE80211_STA_DISABLE_HT) &&
	    sband->ht_cap.ht_supported) {
		const u8 *ht_oper_ie, *ht_cap_ie;

		ht_oper_ie = ieee80211_bss_get_ie(cbss, WLAN_EID_HT_OPERATION);
		if (ht_oper_ie && ht_oper_ie[1] >= sizeof(*ht_oper))
			ht_oper = (void *)(ht_oper_ie + 2);

		ht_cap_ie = ieee80211_bss_get_ie(cbss, WLAN_EID_HT_CAPABILITY);
		if (ht_cap_ie && ht_cap_ie[1] >= sizeof(*ht_cap))
			ht_cap = (void *)(ht_cap_ie + 2);

		if (!ht_cap) {
			ifmgd->flags |= IEEE80211_STA_DISABLE_HT;
			ht_oper = NULL;
		}
	}

	if (!(ifmgd->flags & IEEE80211_STA_DISABLE_VHT) &&
	    sband->vht_cap.vht_supported) {
		const u8 *vht_oper_ie, *vht_cap;

		vht_oper_ie = ieee80211_bss_get_ie(cbss,
						   WLAN_EID_VHT_OPERATION);
		if (vht_oper_ie && vht_oper_ie[1] >= sizeof(*vht_oper))
			vht_oper = (void *)(vht_oper_ie + 2);
		if (vht_oper && !ht_oper) {
			vht_oper = NULL;
			sdata_info(sdata,
				   "AP advertised VHT without HT, disabling both\n");
			ifmgd->flags |= IEEE80211_STA_DISABLE_HT;
			ifmgd->flags |= IEEE80211_STA_DISABLE_VHT;
		}

		vht_cap = ieee80211_bss_get_ie(cbss, WLAN_EID_VHT_CAPABILITY);
		if (!vht_cap || vht_cap[1] < sizeof(struct ieee80211_vht_cap)) {
			ifmgd->flags |= IEEE80211_STA_DISABLE_VHT;
			vht_oper = NULL;
		}
	}

	if (!ieee80211_get_he_sta_cap(sband))
		ifmgd->flags |= IEEE80211_STA_DISABLE_HE;

	if (!(ifmgd->flags & IEEE80211_STA_DISABLE_HE)) {
		const struct cfg80211_bss_ies *ies;
		const u8 *he_oper_ie;

		ies = rcu_dereference(cbss->ies);
		he_oper_ie = cfg80211_find_ext_ie(WLAN_EID_EXT_HE_OPERATION,
						  ies->data, ies->len);
		if (he_oper_ie &&
		    he_oper_ie[1] == ieee80211_he_oper_size(&he_oper_ie[3]))
			he_oper = (void *)(he_oper_ie + 3);
		else
			he_oper = NULL;

		if (!ieee80211_verify_sta_he_mcs_support(sband, he_oper))
			ifmgd->flags |= IEEE80211_STA_DISABLE_HE;
	}

	/* Allow VHT if at least one channel on the sband supports 80 MHz */
	have_80mhz = false;
	for (i = 0; i < sband->n_channels; i++) {
		if (sband->channels[i].flags & (IEEE80211_CHAN_DISABLED |
						IEEE80211_CHAN_NO_80MHZ))
			continue;

		have_80mhz = true;
		break;
	}

	if (!have_80mhz)
		ifmgd->flags |= IEEE80211_STA_DISABLE_VHT;

	ifmgd->flags |= ieee80211_determine_chantype(sdata, sband,
						     cbss->channel,
						     ht_oper, vht_oper, he_oper,
						     &chandef, false);

	sdata->needed_rx_chains = min(ieee80211_ht_vht_rx_chains(sdata, cbss),
				      local->rx_chains);

	rcu_read_unlock();

	/* will change later if needed */
	sdata->smps_mode = IEEE80211_SMPS_OFF;

	mutex_lock(&local->mtx);
	/*
	 * If this fails (possibly due to channel context sharing
	 * on incompatible channels, e.g. 80+80 and 160 sharing the
	 * same control channel) try to use a smaller bandwidth.
	 */
	ret = ieee80211_vif_use_channel(sdata, &chandef,
					IEEE80211_CHANCTX_SHARED);

	/* don't downgrade for 5 and 10 MHz channels, though. */
	if (chandef.width == NL80211_CHAN_WIDTH_5 ||
	    chandef.width == NL80211_CHAN_WIDTH_10)
		goto out;

	while (ret && chandef.width != NL80211_CHAN_WIDTH_20_NOHT) {
		ifmgd->flags |= ieee80211_chandef_downgrade(&chandef);
		ret = ieee80211_vif_use_channel(sdata, &chandef,
						IEEE80211_CHANCTX_SHARED);
	}
 out:
	mutex_unlock(&local->mtx);
	return ret;
}