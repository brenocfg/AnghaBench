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
struct wlcore_hw_queue_iter_data {int /*<<< orphan*/  hw_queue_map; scalar_t__ cur_running; struct ieee80211_vif* vif; } ;
struct wl12xx_vif {int hw_queue_base; scalar_t__ bss_type; } ;
struct wl1271 {scalar_t__* queue_stop_reasons; int /*<<< orphan*/  hw; } ;
struct ieee80211_vif {scalar_t__ type; int cab_queue; int* hw_queue; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_AP_BSS ; 
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int EBUSY ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 void* IEEE80211_INVAL_HW_QUEUE ; 
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 int NUM_TX_QUEUES ; 
 int WLCORE_NUM_MAC_ADDRESSES ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wlcore_hw_queue_iter_data*) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int) ; 
 struct ieee80211_vif* wl12xx_wlvif_to_vif (struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wlcore_hw_queue_iter ; 

__attribute__((used)) static int wlcore_allocate_hw_queue_base(struct wl1271 *wl,
					 struct wl12xx_vif *wlvif)
{
	struct ieee80211_vif *vif = wl12xx_wlvif_to_vif(wlvif);
	struct wlcore_hw_queue_iter_data iter_data = {};
	int i, q_base;

	if (vif->type == NL80211_IFTYPE_P2P_DEVICE) {
		vif->cab_queue = IEEE80211_INVAL_HW_QUEUE;
		return 0;
	}

	iter_data.vif = vif;

	/* mark all bits taken by active interfaces */
	ieee80211_iterate_active_interfaces_atomic(wl->hw,
					IEEE80211_IFACE_ITER_RESUME_ALL,
					wlcore_hw_queue_iter, &iter_data);

	/* the current vif is already running in mac80211 (resume/recovery) */
	if (iter_data.cur_running) {
		wlvif->hw_queue_base = vif->hw_queue[0];
		wl1271_debug(DEBUG_MAC80211,
			     "using pre-allocated hw queue base %d",
			     wlvif->hw_queue_base);

		/* interface type might have changed type */
		goto adjust_cab_queue;
	}

	q_base = find_first_zero_bit(iter_data.hw_queue_map,
				     WLCORE_NUM_MAC_ADDRESSES);
	if (q_base >= WLCORE_NUM_MAC_ADDRESSES)
		return -EBUSY;

	wlvif->hw_queue_base = q_base * NUM_TX_QUEUES;
	wl1271_debug(DEBUG_MAC80211, "allocating hw queue base: %d",
		     wlvif->hw_queue_base);

	for (i = 0; i < NUM_TX_QUEUES; i++) {
		wl->queue_stop_reasons[wlvif->hw_queue_base + i] = 0;
		/* register hw queues in mac80211 */
		vif->hw_queue[i] = wlvif->hw_queue_base + i;
	}

adjust_cab_queue:
	/* the last places are reserved for cab queues per interface */
	if (wlvif->bss_type == BSS_TYPE_AP_BSS)
		vif->cab_queue = NUM_TX_QUEUES * WLCORE_NUM_MAC_ADDRESSES +
				 wlvif->hw_queue_base / NUM_TX_QUEUES;
	else
		vif->cab_queue = IEEE80211_INVAL_HW_QUEUE;

	return 0;
}