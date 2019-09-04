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
struct wl1271 {scalar_t__ state; scalar_t__ tx_frames_cnt; int /*<<< orphan*/  mutex; } ;
struct ieee80211_hw {struct wl1271* priv; } ;

/* Variables and functions */
 scalar_t__ WLCORE_STATE_ON ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ wl1271_tx_total_queue_count (struct wl1271*) ; 

__attribute__((used)) static bool wl1271_tx_frames_pending(struct ieee80211_hw *hw)
{
	struct wl1271 *wl = hw->priv;
	bool ret = false;

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON))
		goto out;

	/* packets are considered pending if in the TX queue or the FW */
	ret = (wl1271_tx_total_queue_count(wl) > 0) || (wl->tx_frames_cnt > 0);
out:
	mutex_unlock(&wl->mutex);

	return ret;
}