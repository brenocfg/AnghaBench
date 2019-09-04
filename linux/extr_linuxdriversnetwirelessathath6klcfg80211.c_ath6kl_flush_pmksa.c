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
struct ath6kl_vif {int /*<<< orphan*/  bssid; int /*<<< orphan*/  fw_vif_idx; int /*<<< orphan*/  flags; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTED ; 
 struct ath6kl* ath6kl_priv (struct net_device*) ; 
 int ath6kl_wmi_setpmkid_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct ath6kl_vif* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_flush_pmksa(struct wiphy *wiphy, struct net_device *netdev)
{
	struct ath6kl *ar = ath6kl_priv(netdev);
	struct ath6kl_vif *vif = netdev_priv(netdev);

	if (test_bit(CONNECTED, &vif->flags))
		return ath6kl_wmi_setpmkid_cmd(ar->wmi, vif->fw_vif_idx,
					       vif->bssid, NULL, false);
	return 0;
}