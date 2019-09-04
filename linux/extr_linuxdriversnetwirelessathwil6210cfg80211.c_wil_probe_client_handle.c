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
struct wil_sta_info {scalar_t__ status; int /*<<< orphan*/  addr; } ;
struct wil_probe_client_req {size_t cid; int /*<<< orphan*/  cookie; } ;
struct wil6210_vif {int dummy; } ;
struct wil6210_priv {struct wil_sta_info* sta; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cfg80211_probe_status (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct net_device* vif_to_ndev (struct wil6210_vif*) ; 
 scalar_t__ wil_sta_connected ; 

__attribute__((used)) static void wil_probe_client_handle(struct wil6210_priv *wil,
				    struct wil6210_vif *vif,
				    struct wil_probe_client_req *req)
{
	struct net_device *ndev = vif_to_ndev(vif);
	struct wil_sta_info *sta = &wil->sta[req->cid];
	/* assume STA is alive if it is still connected,
	 * else FW will disconnect it
	 */
	bool alive = (sta->status == wil_sta_connected);

	cfg80211_probe_status(ndev, sta->addr, req->cookie, alive,
			      0, false, GFP_KERNEL);
}