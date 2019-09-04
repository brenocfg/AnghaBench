#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ieee802_11_elems {int supp_rates_len; int ext_supp_rates_len; scalar_t__ parse_error; scalar_t__ wmm_info; scalar_t__ wmm_param; int /*<<< orphan*/  ext_supp_rates; int /*<<< orphan*/  supp_rates; int /*<<< orphan*/ * erp_info; } ;
struct ieee80211_supported_band {int /*<<< orphan*/ * bitrates; } ;
struct TYPE_6__ {int /*<<< orphan*/  bssid; scalar_t__ assoc; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; } ;
struct ieee80211_rx_status {int flag; int signal; scalar_t__ bw; size_t band; scalar_t__ encoding; size_t rate_idx; int /*<<< orphan*/  device_timestamp; int /*<<< orphan*/  boottime_ns; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  frame_control; } ;
struct TYPE_9__ {int max_signal; TYPE_5__* wiphy; } ;
struct ieee80211_local {TYPE_4__ hw; int /*<<< orphan*/  scan_sdata; } ;
struct ieee80211_channel {scalar_t__ center_freq; } ;
struct ieee80211_bss {int valid_data; int has_erp_value; int supp_rates_len; int wmm_used; int /*<<< orphan*/ * beacon_rate; int /*<<< orphan*/  uapsd_supported; scalar_t__ supp_rates; int /*<<< orphan*/  erp_value; int /*<<< orphan*/  corrupt_data; int /*<<< orphan*/  device_ts_presp; int /*<<< orphan*/  device_ts_beacon; } ;
struct cfg80211_inform_bss {int signal; int /*<<< orphan*/  parent_bssid; int /*<<< orphan*/  parent_tsf; struct ieee80211_channel* chan; int /*<<< orphan*/  scan_width; int /*<<< orphan*/  boottime_ns; } ;
struct cfg80211_bss {scalar_t__ priv; TYPE_3__* channel; } ;
struct TYPE_10__ {scalar_t__ max_adj_channel_rssi_comp; struct ieee80211_supported_band** bands; } ;
struct TYPE_8__ {scalar_t__ center_freq; } ;

/* Variables and functions */
 scalar_t__ FCS_LEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IEEE80211_BSS_CORRUPT_BEACON ; 
 int /*<<< orphan*/  IEEE80211_BSS_CORRUPT_PROBE_RESP ; 
 int IEEE80211_BSS_VALID_ERP ; 
 int IEEE80211_BSS_VALID_RATES ; 
 int IEEE80211_BSS_VALID_WMM ; 
 int IEEE80211_MAX_SUPP_RATES ; 
 int /*<<< orphan*/  NL80211_BSS_CHAN_WIDTH_10 ; 
 int /*<<< orphan*/  NL80211_BSS_CHAN_WIDTH_20 ; 
 int /*<<< orphan*/  NL80211_BSS_CHAN_WIDTH_5 ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ RATE_INFO_BW_10 ; 
 scalar_t__ RATE_INFO_BW_5 ; 
 scalar_t__ RX_ENC_HT ; 
 scalar_t__ RX_ENC_VHT ; 
 int RX_FLAG_NO_SIGNAL_VAL ; 
 int /*<<< orphan*/  SIGNAL_DBM ; 
 int /*<<< orphan*/  SIGNAL_UNSPEC ; 
 scalar_t__ abs (scalar_t__) ; 
 struct cfg80211_bss* cfg80211_inform_bss_frame_data (TYPE_5__*,struct cfg80211_inform_bss*,struct ieee80211_mgmt*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_calculate_rx_timestamp (struct ieee80211_local*,struct ieee80211_rx_status*,scalar_t__,int) ; 
 scalar_t__ ieee80211_have_rx_timestamp (struct ieee80211_rx_status*) ; 
 scalar_t__ ieee80211_hw_check (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_uapsd_supported (struct ieee802_11_elems*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct ieee80211_sub_if_data* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct ieee80211_bss *
ieee80211_bss_info_update(struct ieee80211_local *local,
			  struct ieee80211_rx_status *rx_status,
			  struct ieee80211_mgmt *mgmt, size_t len,
			  struct ieee802_11_elems *elems,
			  struct ieee80211_channel *channel)
{
	bool beacon = ieee80211_is_beacon(mgmt->frame_control);
	struct cfg80211_bss *cbss;
	struct ieee80211_bss *bss;
	int clen, srlen;
	struct cfg80211_inform_bss bss_meta = {
		.boottime_ns = rx_status->boottime_ns,
	};
	bool signal_valid;
	struct ieee80211_sub_if_data *scan_sdata;

	if (rx_status->flag & RX_FLAG_NO_SIGNAL_VAL)
		bss_meta.signal = 0; /* invalid signal indication */
	else if (ieee80211_hw_check(&local->hw, SIGNAL_DBM))
		bss_meta.signal = rx_status->signal * 100;
	else if (ieee80211_hw_check(&local->hw, SIGNAL_UNSPEC))
		bss_meta.signal = (rx_status->signal * 100) / local->hw.max_signal;

	bss_meta.scan_width = NL80211_BSS_CHAN_WIDTH_20;
	if (rx_status->bw == RATE_INFO_BW_5)
		bss_meta.scan_width = NL80211_BSS_CHAN_WIDTH_5;
	else if (rx_status->bw == RATE_INFO_BW_10)
		bss_meta.scan_width = NL80211_BSS_CHAN_WIDTH_10;

	bss_meta.chan = channel;

	rcu_read_lock();
	scan_sdata = rcu_dereference(local->scan_sdata);
	if (scan_sdata && scan_sdata->vif.type == NL80211_IFTYPE_STATION &&
	    scan_sdata->vif.bss_conf.assoc &&
	    ieee80211_have_rx_timestamp(rx_status)) {
		bss_meta.parent_tsf =
			ieee80211_calculate_rx_timestamp(local, rx_status,
							 len + FCS_LEN, 24);
		ether_addr_copy(bss_meta.parent_bssid,
				scan_sdata->vif.bss_conf.bssid);
	}
	rcu_read_unlock();

	cbss = cfg80211_inform_bss_frame_data(local->hw.wiphy, &bss_meta,
					      mgmt, len, GFP_ATOMIC);
	if (!cbss)
		return NULL;
	/* In case the signal is invalid update the status */
	signal_valid = abs(channel->center_freq - cbss->channel->center_freq)
		<= local->hw.wiphy->max_adj_channel_rssi_comp;
	if (!signal_valid)
		rx_status->flag |= RX_FLAG_NO_SIGNAL_VAL;

	bss = (void *)cbss->priv;

	if (beacon)
		bss->device_ts_beacon = rx_status->device_timestamp;
	else
		bss->device_ts_presp = rx_status->device_timestamp;

	if (elems->parse_error) {
		if (beacon)
			bss->corrupt_data |= IEEE80211_BSS_CORRUPT_BEACON;
		else
			bss->corrupt_data |= IEEE80211_BSS_CORRUPT_PROBE_RESP;
	} else {
		if (beacon)
			bss->corrupt_data &= ~IEEE80211_BSS_CORRUPT_BEACON;
		else
			bss->corrupt_data &= ~IEEE80211_BSS_CORRUPT_PROBE_RESP;
	}

	/* save the ERP value so that it is available at association time */
	if (elems->erp_info && (!elems->parse_error ||
				!(bss->valid_data & IEEE80211_BSS_VALID_ERP))) {
		bss->erp_value = elems->erp_info[0];
		bss->has_erp_value = true;
		if (!elems->parse_error)
			bss->valid_data |= IEEE80211_BSS_VALID_ERP;
	}

	/* replace old supported rates if we get new values */
	if (!elems->parse_error ||
	    !(bss->valid_data & IEEE80211_BSS_VALID_RATES)) {
		srlen = 0;
		if (elems->supp_rates) {
			clen = IEEE80211_MAX_SUPP_RATES;
			if (clen > elems->supp_rates_len)
				clen = elems->supp_rates_len;
			memcpy(bss->supp_rates, elems->supp_rates, clen);
			srlen += clen;
		}
		if (elems->ext_supp_rates) {
			clen = IEEE80211_MAX_SUPP_RATES - srlen;
			if (clen > elems->ext_supp_rates_len)
				clen = elems->ext_supp_rates_len;
			memcpy(bss->supp_rates + srlen, elems->ext_supp_rates,
			       clen);
			srlen += clen;
		}
		if (srlen) {
			bss->supp_rates_len = srlen;
			if (!elems->parse_error)
				bss->valid_data |= IEEE80211_BSS_VALID_RATES;
		}
	}

	if (!elems->parse_error ||
	    !(bss->valid_data & IEEE80211_BSS_VALID_WMM)) {
		bss->wmm_used = elems->wmm_param || elems->wmm_info;
		bss->uapsd_supported = is_uapsd_supported(elems);
		if (!elems->parse_error)
			bss->valid_data |= IEEE80211_BSS_VALID_WMM;
	}

	if (beacon) {
		struct ieee80211_supported_band *sband =
			local->hw.wiphy->bands[rx_status->band];
		if (!(rx_status->encoding == RX_ENC_HT) &&
		    !(rx_status->encoding == RX_ENC_VHT))
			bss->beacon_rate =
				&sband->bitrates[rx_status->rate_idx];
	}

	return bss;
}