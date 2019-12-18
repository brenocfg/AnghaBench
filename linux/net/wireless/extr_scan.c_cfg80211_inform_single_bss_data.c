#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  void* u16 ;
struct wiphy {scalar_t__ signal_type; scalar_t__ max_adj_channel_rssi_comp; } ;
struct ieee80211_channel {scalar_t__ band; scalar_t__ center_freq; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  bss_generation; } ;
struct cfg80211_non_tx_bss {int /*<<< orphan*/  tx_bss; int /*<<< orphan*/  max_bssid_indicator; int /*<<< orphan*/  bssid_index; } ;
struct cfg80211_bss {int signal; int capability; int /*<<< orphan*/  ies; int /*<<< orphan*/  proberesp_ies; int /*<<< orphan*/  beacon_ies; int /*<<< orphan*/  max_bssid_indicator; int /*<<< orphan*/  bssid_index; int /*<<< orphan*/  transmitted_bss; void* beacon_interval; int /*<<< orphan*/  scan_width; struct ieee80211_channel* channel; int /*<<< orphan*/  bssid; } ;
struct cfg80211_internal_bss {struct cfg80211_bss pub; int /*<<< orphan*/  ts_boottime; } ;
struct cfg80211_inform_bss {int signal; TYPE_1__* chan; int /*<<< orphan*/  boottime_ns; int /*<<< orphan*/  scan_width; } ;
struct cfg80211_bss_ies {size_t len; int from_beacon; int /*<<< orphan*/  data; int /*<<< orphan*/  tsf; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum cfg80211_bss_frame_type { ____Placeholder_cfg80211_bss_frame_type } cfg80211_bss_frame_type ;
struct TYPE_4__ {unsigned long ts; } ;
struct TYPE_3__ {scalar_t__ center_freq; } ;

/* Variables and functions */
#define  CFG80211_BSS_FTYPE_BEACON 130 
#define  CFG80211_BSS_FTYPE_PRESP 129 
#define  CFG80211_BSS_FTYPE_UNKNOWN 128 
 scalar_t__ CFG80211_SIGNAL_TYPE_UNSPEC ; 
 size_t ETH_ALEN ; 
 scalar_t__ NL80211_BAND_60GHZ ; 
 scalar_t__ WARN_ON (int) ; 
 int WLAN_CAPABILITY_DMG_TYPE_AP ; 
 int WLAN_CAPABILITY_DMG_TYPE_MASK ; 
 int WLAN_CAPABILITY_DMG_TYPE_PBSS ; 
 int WLAN_CAPABILITY_ESS ; 
 scalar_t__ __cfg80211_unlink_bss (struct cfg80211_registered_device*,struct cfg80211_internal_bss*) ; 
 scalar_t__ abs (scalar_t__) ; 
 TYPE_2__* bss_from_pub (int /*<<< orphan*/ ) ; 
 scalar_t__ cfg80211_add_nontrans_list (int /*<<< orphan*/ ,struct cfg80211_bss*) ; 
 struct cfg80211_internal_bss* cfg80211_bss_update (struct cfg80211_registered_device*,struct cfg80211_internal_bss*,int,unsigned long) ; 
 struct ieee80211_channel* cfg80211_get_bss_channel (struct wiphy*,int /*<<< orphan*/  const*,size_t,TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 struct cfg80211_bss_ies* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct cfg80211_bss_ies*) ; 
 int /*<<< orphan*/  regulatory_hint_found_beacon (struct wiphy*,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_cfg80211_return_bss (struct cfg80211_bss*) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 

__attribute__((used)) static struct cfg80211_bss *
cfg80211_inform_single_bss_data(struct wiphy *wiphy,
				struct cfg80211_inform_bss *data,
				enum cfg80211_bss_frame_type ftype,
				const u8 *bssid, u64 tsf, u16 capability,
				u16 beacon_interval, const u8 *ie, size_t ielen,
				struct cfg80211_non_tx_bss *non_tx_data,
				gfp_t gfp)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wiphy);
	struct cfg80211_bss_ies *ies;
	struct ieee80211_channel *channel;
	struct cfg80211_internal_bss tmp = {}, *res;
	int bss_type;
	bool signal_valid;
	unsigned long ts;

	if (WARN_ON(!wiphy))
		return NULL;

	if (WARN_ON(wiphy->signal_type == CFG80211_SIGNAL_TYPE_UNSPEC &&
		    (data->signal < 0 || data->signal > 100)))
		return NULL;

	channel = cfg80211_get_bss_channel(wiphy, ie, ielen, data->chan,
					   data->scan_width);
	if (!channel)
		return NULL;

	memcpy(tmp.pub.bssid, bssid, ETH_ALEN);
	tmp.pub.channel = channel;
	tmp.pub.scan_width = data->scan_width;
	tmp.pub.signal = data->signal;
	tmp.pub.beacon_interval = beacon_interval;
	tmp.pub.capability = capability;
	tmp.ts_boottime = data->boottime_ns;
	if (non_tx_data) {
		tmp.pub.transmitted_bss = non_tx_data->tx_bss;
		ts = bss_from_pub(non_tx_data->tx_bss)->ts;
		tmp.pub.bssid_index = non_tx_data->bssid_index;
		tmp.pub.max_bssid_indicator = non_tx_data->max_bssid_indicator;
	} else {
		ts = jiffies;
	}

	/*
	 * If we do not know here whether the IEs are from a Beacon or Probe
	 * Response frame, we need to pick one of the options and only use it
	 * with the driver that does not provide the full Beacon/Probe Response
	 * frame. Use Beacon frame pointer to avoid indicating that this should
	 * override the IEs pointer should we have received an earlier
	 * indication of Probe Response data.
	 */
	ies = kzalloc(sizeof(*ies) + ielen, gfp);
	if (!ies)
		return NULL;
	ies->len = ielen;
	ies->tsf = tsf;
	ies->from_beacon = false;
	memcpy(ies->data, ie, ielen);

	switch (ftype) {
	case CFG80211_BSS_FTYPE_BEACON:
		ies->from_beacon = true;
		/* fall through */
	case CFG80211_BSS_FTYPE_UNKNOWN:
		rcu_assign_pointer(tmp.pub.beacon_ies, ies);
		break;
	case CFG80211_BSS_FTYPE_PRESP:
		rcu_assign_pointer(tmp.pub.proberesp_ies, ies);
		break;
	}
	rcu_assign_pointer(tmp.pub.ies, ies);

	signal_valid = abs(data->chan->center_freq - channel->center_freq) <=
		wiphy->max_adj_channel_rssi_comp;
	res = cfg80211_bss_update(wiphy_to_rdev(wiphy), &tmp, signal_valid, ts);
	if (!res)
		return NULL;

	if (channel->band == NL80211_BAND_60GHZ) {
		bss_type = res->pub.capability & WLAN_CAPABILITY_DMG_TYPE_MASK;
		if (bss_type == WLAN_CAPABILITY_DMG_TYPE_AP ||
		    bss_type == WLAN_CAPABILITY_DMG_TYPE_PBSS)
			regulatory_hint_found_beacon(wiphy, channel, gfp);
	} else {
		if (res->pub.capability & WLAN_CAPABILITY_ESS)
			regulatory_hint_found_beacon(wiphy, channel, gfp);
	}

	if (non_tx_data) {
		/* this is a nontransmitting bss, we need to add it to
		 * transmitting bss' list if it is not there
		 */
		if (cfg80211_add_nontrans_list(non_tx_data->tx_bss,
					       &res->pub)) {
			if (__cfg80211_unlink_bss(rdev, res))
				rdev->bss_generation++;
		}
	}

	trace_cfg80211_return_bss(&res->pub);
	/* cfg80211_bss_update gives us a referenced result */
	return &res->pub;
}