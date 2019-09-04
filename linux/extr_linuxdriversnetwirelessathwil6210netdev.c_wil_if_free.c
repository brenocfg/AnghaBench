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
struct wil6210_priv {struct net_device* main_ndev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  wil_cfg80211_deinit (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_ndev_destructor (struct net_device*) ; 
 int /*<<< orphan*/  wil_priv_deinit (struct wil6210_priv*) ; 

void wil_if_free(struct wil6210_priv *wil)
{
	struct net_device *ndev = wil->main_ndev;

	wil_dbg_misc(wil, "if_free\n");

	if (!ndev)
		return;

	wil_priv_deinit(wil);

	wil->main_ndev = NULL;
	wil_ndev_destructor(ndev);
	free_netdev(ndev);

	wil_cfg80211_deinit(wil);
}