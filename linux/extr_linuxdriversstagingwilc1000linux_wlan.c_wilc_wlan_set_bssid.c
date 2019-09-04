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
struct wilc_vif {int /*<<< orphan*/  mode; int /*<<< orphan*/  bssid; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 

int wilc_wlan_set_bssid(struct net_device *wilc_netdev, u8 *bssid, u8 mode)
{
	struct wilc_vif *vif = netdev_priv(wilc_netdev);

	memcpy(vif->bssid, bssid, 6);
	vif->mode = mode;

	return 0;
}