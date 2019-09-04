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
struct wl12xx_vif {int dummy; } ;
struct wl1271 {int /*<<< orphan*/ * queue_stop_reasons; int /*<<< orphan*/  wl_lock; } ;
typedef  enum wlcore_queue_stop_reason { ____Placeholder_wlcore_queue_stop_reason } wlcore_queue_stop_reason ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int test_bit (int,int /*<<< orphan*/ *) ; 
 int wlcore_tx_get_mac80211_queue (struct wl12xx_vif*,int /*<<< orphan*/ ) ; 

bool wlcore_is_queue_stopped_by_reason_locked(struct wl1271 *wl,
				       struct wl12xx_vif *wlvif, u8 queue,
				       enum wlcore_queue_stop_reason reason)
{
	int hwq = wlcore_tx_get_mac80211_queue(wlvif, queue);

	assert_spin_locked(&wl->wl_lock);
	return test_bit(reason, &wl->queue_stop_reasons[hwq]);
}