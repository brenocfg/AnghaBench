#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {TYPE_2__* chan; } ;
struct wireless_dev {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/ * connect_keys; TYPE_4__ chandef; int /*<<< orphan*/  ibss_dfs_possible; int /*<<< orphan*/  ibss_fixed; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct ieee80211_supported_band {int n_bitrates; TYPE_3__* bitrates; } ;
struct TYPE_5__ {struct ieee80211_supported_band** bands; } ;
struct cfg80211_registered_device {TYPE_1__ wiphy; } ;
struct cfg80211_ibss_params {scalar_t__ wep_tx_key; scalar_t__ ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  wep_keys; TYPE_4__ chandef; int /*<<< orphan*/  userspace_handles_dfs; int /*<<< orphan*/  channel_fixed; int /*<<< orphan*/  basic_rates; } ;
struct cfg80211_cached_keys {scalar_t__ def; int /*<<< orphan*/  params; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {size_t band; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int /*<<< orphan*/  BIT (int) ; 
 int EALREADY ; 
 int EINVAL ; 
 int IEEE80211_RATE_MANDATORY_A ; 
 int IEEE80211_RATE_MANDATORY_B ; 
 size_t NL80211_BAND_5GHZ ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int rdev_join_ibss (struct cfg80211_registered_device*,struct net_device*,struct cfg80211_ibss_params*) ; 

int __cfg80211_join_ibss(struct cfg80211_registered_device *rdev,
			 struct net_device *dev,
			 struct cfg80211_ibss_params *params,
			 struct cfg80211_cached_keys *connkeys)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	int err;

	ASSERT_RTNL();
	ASSERT_WDEV_LOCK(wdev);

	if (wdev->ssid_len)
		return -EALREADY;

	if (!params->basic_rates) {
		/*
		* If no rates were explicitly configured,
		* use the mandatory rate set for 11b or
		* 11a for maximum compatibility.
		*/
		struct ieee80211_supported_band *sband =
			rdev->wiphy.bands[params->chandef.chan->band];
		int j;
		u32 flag = params->chandef.chan->band == NL80211_BAND_5GHZ ?
			IEEE80211_RATE_MANDATORY_A :
			IEEE80211_RATE_MANDATORY_B;

		for (j = 0; j < sband->n_bitrates; j++) {
			if (sband->bitrates[j].flags & flag)
				params->basic_rates |= BIT(j);
		}
	}

	if (WARN_ON(connkeys && connkeys->def < 0))
		return -EINVAL;

	if (WARN_ON(wdev->connect_keys))
		kzfree(wdev->connect_keys);
	wdev->connect_keys = connkeys;

	wdev->ibss_fixed = params->channel_fixed;
	wdev->ibss_dfs_possible = params->userspace_handles_dfs;
	wdev->chandef = params->chandef;
	if (connkeys) {
		params->wep_keys = connkeys->params;
		params->wep_tx_key = connkeys->def;
	}

#ifdef CONFIG_CFG80211_WEXT
	wdev->wext.ibss.chandef = params->chandef;
#endif
	err = rdev_join_ibss(rdev, dev, params);
	if (err) {
		wdev->connect_keys = NULL;
		return err;
	}

	memcpy(wdev->ssid, params->ssid, params->ssid_len);
	wdev->ssid_len = params->ssid_len;

	return 0;
}