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
struct ath6kl_vif {scalar_t__ nw_type; int /*<<< orphan*/  ndev; int /*<<< orphan*/  flags; int /*<<< orphan*/  fw_vif_idx; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 scalar_t__ AP_NETWORK ; 
 int /*<<< orphan*/  CONNECTED ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 struct ath6kl* ath6kl_priv (struct net_device*) ; 
 int ath6kl_restore_htcap (struct ath6kl_vif*) ; 
 int /*<<< orphan*/  ath6kl_wmi_disconnect_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ath6kl_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_stop_ap(struct wiphy *wiphy, struct net_device *dev)
{
	struct ath6kl *ar = ath6kl_priv(dev);
	struct ath6kl_vif *vif = netdev_priv(dev);

	if (vif->nw_type != AP_NETWORK)
		return -EOPNOTSUPP;
	if (!test_bit(CONNECTED, &vif->flags))
		return -ENOTCONN;

	ath6kl_wmi_disconnect_cmd(ar->wmi, vif->fw_vif_idx);
	clear_bit(CONNECTED, &vif->flags);
	netif_carrier_off(vif->ndev);

	/* Restore ht setting in firmware */
	return ath6kl_restore_htcap(vif);
}