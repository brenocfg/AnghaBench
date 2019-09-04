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
typedef  scalar_t__ u64 ;
struct wireless_dev {int dummy; } ;
struct wil_p2p_info {int discovery_started; unsigned int listen_duration; struct wireless_dev* pending_listen_wdev; scalar_t__ cookie; int /*<<< orphan*/  listen_chan; } ;
struct wil6210_vif {scalar_t__ mid; scalar_t__ scan_request; struct wil_p2p_info p2p; } ;
struct wil6210_priv {int /*<<< orphan*/  mutex; struct wireless_dev* radio_wdev; int /*<<< orphan*/  vif_mutex; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cfg80211_ready_on_channel (struct wireless_dev*,scalar_t__,struct ieee80211_channel*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ieee80211_channel*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wil6210_vif* wdev_to_vif (struct wil6210_priv*,struct wireless_dev*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 int wil_p2p_start_listen (struct wil6210_vif*) ; 

int wil_p2p_listen(struct wil6210_priv *wil, struct wireless_dev *wdev,
		   unsigned int duration, struct ieee80211_channel *chan,
		   u64 *cookie)
{
	struct wil6210_vif *vif = wdev_to_vif(wil, wdev);
	struct wil_p2p_info *p2p = &vif->p2p;
	int rc;

	if (!chan)
		return -EINVAL;

	wil_dbg_misc(wil, "p2p_listen: duration %d\n", duration);

	mutex_lock(&wil->mutex);

	if (p2p->discovery_started) {
		wil_err(wil, "discovery already ongoing\n");
		rc = -EBUSY;
		goto out;
	}

	memcpy(&p2p->listen_chan, chan, sizeof(*chan));
	*cookie = ++p2p->cookie;
	p2p->listen_duration = duration;

	mutex_lock(&wil->vif_mutex);
	if (vif->scan_request) {
		wil_dbg_misc(wil, "Delaying p2p listen until scan done\n");
		p2p->pending_listen_wdev = wdev;
		p2p->discovery_started = 1;
		rc = 0;
		mutex_unlock(&wil->vif_mutex);
		goto out;
	}
	mutex_unlock(&wil->vif_mutex);

	rc = wil_p2p_start_listen(vif);
	if (rc)
		goto out;

	p2p->discovery_started = 1;
	if (vif->mid == 0)
		wil->radio_wdev = wdev;

	cfg80211_ready_on_channel(wdev, *cookie, chan, duration,
				  GFP_KERNEL);

out:
	mutex_unlock(&wil->mutex);
	return rc;
}