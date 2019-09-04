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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct net_device {int name; } ;
struct mwifiex_user_scan_cfg {int /*<<< orphan*/  scan_chan_gap; TYPE_3__* chan_list; int /*<<< orphan*/  ssid_list; int /*<<< orphan*/  num_ssids; int /*<<< orphan*/  random_mac; } ;
struct TYPE_7__ {int /*<<< orphan*/  wiphy; int /*<<< orphan*/  current_bss; } ;
struct mwifiex_private {int scan_aborting; int scan_block; TYPE_4__* vs_ie; struct cfg80211_scan_request* scan_request; TYPE_5__* adapter; TYPE_2__ wdev; } ;
struct ieee_types_header {scalar_t__ len; } ;
struct ieee80211_channel {int flags; int /*<<< orphan*/  band; int /*<<< orphan*/  hw_value; } ;
struct cfg80211_scan_request {int flags; int ie_len; scalar_t__ ie; int /*<<< orphan*/  n_ssids; struct ieee80211_channel** channels; int /*<<< orphan*/  n_channels; int /*<<< orphan*/  ssids; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  mac_addr_mask; TYPE_1__* wdev; } ;
struct TYPE_10__ {int /*<<< orphan*/  scan_chan_gap_time; scalar_t__ scan_chan_gap_enabled; } ;
struct TYPE_9__ {scalar_t__ mask; int /*<<< orphan*/  ie; } ;
struct TYPE_8__ {scalar_t__ scan_time; int /*<<< orphan*/  scan_type; int /*<<< orphan*/  radio_type; int /*<<< orphan*/  chan_number; } ;
struct TYPE_6__ {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_CHAN_NO_IR ; 
 int /*<<< orphan*/  MWIFIEX_MAX_VSIE_LEN ; 
 int MWIFIEX_MAX_VSIE_NUM ; 
 int /*<<< orphan*/  MWIFIEX_SCAN_TYPE_ACTIVE ; 
 int /*<<< orphan*/  MWIFIEX_SCAN_TYPE_PASSIVE ; 
 int /*<<< orphan*/  MWIFIEX_USER_SCAN_CHAN_MAX ; 
 scalar_t__ MWIFIEX_VSIE_MASK_CLEAR ; 
 scalar_t__ MWIFIEX_VSIE_MASK_SCAN ; 
 int NL80211_SCAN_FLAG_RANDOM_ADDR ; 
 int /*<<< orphan*/  WARN ; 
 int /*<<< orphan*/  cfg80211_sched_scan_stopped_rtnl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_random_mask_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mwifiex_user_scan_cfg*) ; 
 struct mwifiex_user_scan_cfg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ieee_types_header*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mwifiex_is_any_intf_active (struct mwifiex_private*) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 
 int mwifiex_scan_networks (struct mwifiex_private*,struct mwifiex_user_scan_cfg*) ; 
 int /*<<< orphan*/  mwifiex_stop_bg_scan (struct mwifiex_private*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int
mwifiex_cfg80211_scan(struct wiphy *wiphy,
		      struct cfg80211_scan_request *request)
{
	struct net_device *dev = request->wdev->netdev;
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);
	int i, offset, ret;
	struct ieee80211_channel *chan;
	struct ieee_types_header *ie;
	struct mwifiex_user_scan_cfg *user_scan_cfg;
	u8 mac_addr[ETH_ALEN];

	mwifiex_dbg(priv->adapter, CMD,
		    "info: received scan request on %s\n", dev->name);

	/* Block scan request if scan operation or scan cleanup when interface
	 * is disabled is in process
	 */
	if (priv->scan_request || priv->scan_aborting) {
		mwifiex_dbg(priv->adapter, WARN,
			    "cmd: Scan already in process..\n");
		return -EBUSY;
	}

	if (!priv->wdev.current_bss && priv->scan_block)
		priv->scan_block = false;

	if (!mwifiex_stop_bg_scan(priv))
		cfg80211_sched_scan_stopped_rtnl(priv->wdev.wiphy, 0);

	user_scan_cfg = kzalloc(sizeof(*user_scan_cfg), GFP_KERNEL);
	if (!user_scan_cfg)
		return -ENOMEM;

	priv->scan_request = request;

	if (request->flags & NL80211_SCAN_FLAG_RANDOM_ADDR) {
		get_random_mask_addr(mac_addr, request->mac_addr,
				     request->mac_addr_mask);
		ether_addr_copy(request->mac_addr, mac_addr);
		ether_addr_copy(user_scan_cfg->random_mac, mac_addr);
	}

	user_scan_cfg->num_ssids = request->n_ssids;
	user_scan_cfg->ssid_list = request->ssids;

	if (request->ie && request->ie_len) {
		offset = 0;
		for (i = 0; i < MWIFIEX_MAX_VSIE_NUM; i++) {
			if (priv->vs_ie[i].mask != MWIFIEX_VSIE_MASK_CLEAR)
				continue;
			priv->vs_ie[i].mask = MWIFIEX_VSIE_MASK_SCAN;
			ie = (struct ieee_types_header *)(request->ie + offset);
			memcpy(&priv->vs_ie[i].ie, ie, sizeof(*ie) + ie->len);
			offset += sizeof(*ie) + ie->len;

			if (offset >= request->ie_len)
				break;
		}
	}

	for (i = 0; i < min_t(u32, request->n_channels,
			      MWIFIEX_USER_SCAN_CHAN_MAX); i++) {
		chan = request->channels[i];
		user_scan_cfg->chan_list[i].chan_number = chan->hw_value;
		user_scan_cfg->chan_list[i].radio_type = chan->band;

		if ((chan->flags & IEEE80211_CHAN_NO_IR) || !request->n_ssids)
			user_scan_cfg->chan_list[i].scan_type =
						MWIFIEX_SCAN_TYPE_PASSIVE;
		else
			user_scan_cfg->chan_list[i].scan_type =
						MWIFIEX_SCAN_TYPE_ACTIVE;

		user_scan_cfg->chan_list[i].scan_time = 0;
	}

	if (priv->adapter->scan_chan_gap_enabled &&
	    mwifiex_is_any_intf_active(priv))
		user_scan_cfg->scan_chan_gap =
					      priv->adapter->scan_chan_gap_time;

	ret = mwifiex_scan_networks(priv, user_scan_cfg);
	kfree(user_scan_cfg);
	if (ret) {
		mwifiex_dbg(priv->adapter, ERROR,
			    "scan failed: %d\n", ret);
		priv->scan_aborting = false;
		priv->scan_request = NULL;
		return ret;
	}

	if (request->ie && request->ie_len) {
		for (i = 0; i < MWIFIEX_MAX_VSIE_NUM; i++) {
			if (priv->vs_ie[i].mask == MWIFIEX_VSIE_MASK_SCAN) {
				priv->vs_ie[i].mask = MWIFIEX_VSIE_MASK_CLEAR;
				memset(&priv->vs_ie[i].ie, 0,
				       MWIFIEX_MAX_VSIE_LEN);
			}
		}
	}
	return 0;
}