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
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct cfg80211_bitrate_mask {int dummy; } ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 struct ath6kl* ath6kl_priv (struct net_device*) ; 
 int ath6kl_wmi_set_bitrate_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_bitrate_mask const*) ; 
 struct ath6kl_vif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ath6kl_cfg80211_set_bitrate(struct wiphy *wiphy,
				       struct net_device *dev,
				       const u8 *addr,
				       const struct cfg80211_bitrate_mask *mask)
{
	struct ath6kl *ar = ath6kl_priv(dev);
	struct ath6kl_vif *vif = netdev_priv(dev);

	return ath6kl_wmi_set_bitrate_mask(ar->wmi, vif->fw_vif_idx,
					   mask);
}