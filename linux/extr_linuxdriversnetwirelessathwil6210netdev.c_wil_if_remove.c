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
struct wireless_dev {int /*<<< orphan*/  wiphy; } ;
struct wil6210_priv {int /*<<< orphan*/  napi_rx; int /*<<< orphan*/  napi_tx; struct net_device* main_ndev; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_vif_remove (struct wil6210_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_unregister (int /*<<< orphan*/ ) ; 

void wil_if_remove(struct wil6210_priv *wil)
{
	struct net_device *ndev = wil->main_ndev;
	struct wireless_dev *wdev = ndev->ieee80211_ptr;

	wil_dbg_misc(wil, "if_remove\n");

	rtnl_lock();
	wil_vif_remove(wil, 0);
	rtnl_unlock();

	netif_napi_del(&wil->napi_tx);
	netif_napi_del(&wil->napi_rx);

	wiphy_unregister(wdev->wiphy);
}