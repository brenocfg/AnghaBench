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
struct station_del_parameters {int /*<<< orphan*/ * mac; } ;
struct net_device {int dummy; } ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_REASON_PREV_AUTH_NOT_VALID ; 
 int /*<<< orphan*/  WMI_AP_DEAUTH ; 
 struct ath6kl* ath6kl_priv (struct net_device*) ; 
 int ath6kl_wmi_ap_set_mlme (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bcast_addr ; 
 struct ath6kl_vif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ath6kl_del_station(struct wiphy *wiphy, struct net_device *dev,
			      struct station_del_parameters *params)
{
	struct ath6kl *ar = ath6kl_priv(dev);
	struct ath6kl_vif *vif = netdev_priv(dev);
	const u8 *addr = params->mac ? params->mac : bcast_addr;

	return ath6kl_wmi_ap_set_mlme(ar->wmi, vif->fw_vif_idx, WMI_AP_DEAUTH,
				      addr, WLAN_REASON_PREV_AUTH_NOT_VALID);
}