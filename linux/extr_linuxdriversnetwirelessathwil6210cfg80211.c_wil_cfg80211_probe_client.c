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
typedef  int u64 ;
struct wiphy {int dummy; } ;
struct wil_probe_client_req {int cid; int cookie; int /*<<< orphan*/  list; } ;
struct wil6210_vif {int /*<<< orphan*/  probe_client_worker; int /*<<< orphan*/  probe_client_mutex; int /*<<< orphan*/  probe_client_pending; int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int /*<<< orphan*/  wq_service; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOLINK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct wil_probe_client_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int wil_find_cid (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 

__attribute__((used)) static int wil_cfg80211_probe_client(struct wiphy *wiphy,
				     struct net_device *dev,
				     const u8 *peer, u64 *cookie)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	struct wil6210_vif *vif = ndev_to_vif(dev);
	struct wil_probe_client_req *req;
	int cid = wil_find_cid(wil, vif->mid, peer);

	wil_dbg_misc(wil, "probe_client: %pM => CID %d MID %d\n",
		     peer, cid, vif->mid);

	if (cid < 0)
		return -ENOLINK;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	req->cid = cid;
	req->cookie = cid;

	mutex_lock(&vif->probe_client_mutex);
	list_add_tail(&req->list, &vif->probe_client_pending);
	mutex_unlock(&vif->probe_client_mutex);

	*cookie = req->cookie;
	queue_work(wil->wq_service, &vif->probe_client_worker);
	return 0;
}