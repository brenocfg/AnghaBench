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
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct ath6kl_vif {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ath6kl_cfg80211_ready (struct ath6kl_vif*) ; 
 int /*<<< orphan*/  ath6kl_disconnect (struct ath6kl_vif*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ath6kl_vif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ath6kl_cfg80211_leave_ibss(struct wiphy *wiphy,
				      struct net_device *dev)
{
	struct ath6kl_vif *vif = netdev_priv(dev);

	if (!ath6kl_cfg80211_ready(vif))
		return -EIO;

	ath6kl_disconnect(vif);
	memset(vif->ssid, 0, sizeof(vif->ssid));
	vif->ssid_len = 0;

	return 0;
}