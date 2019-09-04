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
struct wl12xx_vif {int /*<<< orphan*/  rx_streaming_disable_work; struct wl1271* wl; } ;
struct wl1271 {int /*<<< orphan*/  hw; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 struct wl12xx_vif* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_streaming_timer ; 
 struct wl12xx_vif* wlvif ; 

__attribute__((used)) static void wl1271_rx_streaming_timer(struct timer_list *t)
{
	struct wl12xx_vif *wlvif = from_timer(wlvif, t, rx_streaming_timer);
	struct wl1271 *wl = wlvif->wl;
	ieee80211_queue_work(wl->hw, &wlvif->rx_streaming_disable_work);
}