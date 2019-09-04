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
struct wiphy {int /*<<< orphan*/  fw_version; } ;
struct wil6210_vif {int dummy; } ;
struct wil6210_priv {int /*<<< orphan*/  napi_tx; int /*<<< orphan*/  napi_ndev; int /*<<< orphan*/  napi_rx; scalar_t__ use_enhanced_dma_hw; int /*<<< orphan*/  fw_version; struct net_device* main_ndev; struct wiphy* wiphy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIL6210_NAPI_BUDGET ; 
 int /*<<< orphan*/  init_dummy_netdev (int /*<<< orphan*/ *) ; 
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_napi_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wil6210_netdev_poll_rx ; 
 int /*<<< orphan*/  wil6210_netdev_poll_rx_edma ; 
 int /*<<< orphan*/  wil6210_netdev_poll_tx ; 
 int /*<<< orphan*/  wil6210_netdev_poll_tx_edma ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,int) ; 
 int /*<<< orphan*/  wil_update_net_queues_bh (struct wil6210_priv*,struct wil6210_vif*,int /*<<< orphan*/ *,int) ; 
 int wil_vif_add (struct wil6210_priv*,struct wil6210_vif*) ; 
 int wiphy_register (struct wiphy*) ; 
 int /*<<< orphan*/  wiphy_unregister (struct wiphy*) ; 

int wil_if_add(struct wil6210_priv *wil)
{
	struct wiphy *wiphy = wil->wiphy;
	struct net_device *ndev = wil->main_ndev;
	struct wil6210_vif *vif = ndev_to_vif(ndev);
	int rc;

	wil_dbg_misc(wil, "entered");

	strlcpy(wiphy->fw_version, wil->fw_version, sizeof(wiphy->fw_version));

	rc = wiphy_register(wiphy);
	if (rc < 0) {
		wil_err(wil, "failed to register wiphy, err %d\n", rc);
		return rc;
	}

	init_dummy_netdev(&wil->napi_ndev);
	if (wil->use_enhanced_dma_hw) {
		netif_napi_add(&wil->napi_ndev, &wil->napi_rx,
			       wil6210_netdev_poll_rx_edma,
			       WIL6210_NAPI_BUDGET);
		netif_tx_napi_add(&wil->napi_ndev,
				  &wil->napi_tx, wil6210_netdev_poll_tx_edma,
				  WIL6210_NAPI_BUDGET);
	} else {
		netif_napi_add(&wil->napi_ndev, &wil->napi_rx,
			       wil6210_netdev_poll_rx,
			       WIL6210_NAPI_BUDGET);
		netif_tx_napi_add(&wil->napi_ndev,
				  &wil->napi_tx, wil6210_netdev_poll_tx,
				  WIL6210_NAPI_BUDGET);
	}

	wil_update_net_queues_bh(wil, vif, NULL, true);

	rtnl_lock();
	rc = wil_vif_add(wil, vif);
	rtnl_unlock();
	if (rc < 0)
		goto out_wiphy;

	return 0;

out_wiphy:
	wiphy_unregister(wiphy);
	return rc;
}