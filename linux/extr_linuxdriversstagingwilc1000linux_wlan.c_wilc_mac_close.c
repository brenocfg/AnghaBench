#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wilc_vif {scalar_t__ mac_opened; TYPE_2__* ndev; struct wilc* wilc; } ;
struct wilc_priv {scalar_t__ hif_drv; } ;
struct wilc {scalar_t__ open_ifcs; int close; } ;
struct net_device {int dummy; } ;
struct host_if_drv {int dummy; } ;
struct TYPE_5__ {TYPE_1__* ieee80211_ptr; } ;
struct TYPE_4__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  wilc_deinit_host_int (TYPE_2__*) ; 
 int /*<<< orphan*/  wilc_wfi_deinit_mon_interface () ; 
 int /*<<< orphan*/  wilc_wlan_deinitialize (struct net_device*) ; 
 struct wilc_priv* wiphy_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wilc_mac_close(struct net_device *ndev)
{
	struct wilc_priv *priv;
	struct wilc_vif *vif = netdev_priv(ndev);
	struct host_if_drv *hif_drv;
	struct wilc *wl;

	if (!vif || !vif->ndev || !vif->ndev->ieee80211_ptr ||
	    !vif->ndev->ieee80211_ptr->wiphy)
		return 0;

	priv = wiphy_priv(vif->ndev->ieee80211_ptr->wiphy);
	wl = vif->wilc;

	if (!priv)
		return 0;

	hif_drv = (struct host_if_drv *)priv->hif_drv;

	netdev_dbg(ndev, "Mac close\n");

	if (!wl)
		return 0;

	if (!hif_drv)
		return 0;

	if (wl->open_ifcs > 0)
		wl->open_ifcs--;
	else
		return 0;

	if (vif->ndev) {
		netif_stop_queue(vif->ndev);

		wilc_deinit_host_int(vif->ndev);
	}

	if (wl->open_ifcs == 0) {
		netdev_dbg(ndev, "Deinitializing wilc1000\n");
		wl->close = 1;
		wilc_wlan_deinitialize(ndev);
		wilc_wfi_deinit_mon_interface();
	}

	vif->mac_opened = 0;

	return 0;
}