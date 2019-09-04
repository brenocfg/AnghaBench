#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wl12xx_vif {int /*<<< orphan*/  flags; } ;
struct wl1271 {TYPE_1__* ops; struct wl12xx_vif* sched_vif; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sched_scan_stop ) (struct wl1271*,struct wl12xx_vif*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WLVIF_FLAG_ACTIVE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct wl1271*,struct wl12xx_vif*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wl1271_sta_handle_idle(struct wl1271 *wl, struct wl12xx_vif *wlvif,
				   bool idle)
{
	bool cur_idle = !test_bit(WLVIF_FLAG_ACTIVE, &wlvif->flags);

	if (idle == cur_idle)
		return;

	if (idle) {
		clear_bit(WLVIF_FLAG_ACTIVE, &wlvif->flags);
	} else {
		/* The current firmware only supports sched_scan in idle */
		if (wl->sched_vif == wlvif)
			wl->ops->sched_scan_stop(wl, wlvif);

		set_bit(WLVIF_FLAG_ACTIVE, &wlvif->flags);
	}
}