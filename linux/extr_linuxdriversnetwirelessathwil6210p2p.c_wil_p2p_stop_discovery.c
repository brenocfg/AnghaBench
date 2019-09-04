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
typedef  scalar_t__ u8 ;
struct wil_p2p_info {scalar_t__ discovery_started; int /*<<< orphan*/  discovery_timer; int /*<<< orphan*/ * pending_listen_wdev; } ;
struct wil6210_vif {struct wil_p2p_info p2p; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmi_stop_discovery (struct wil6210_vif*) ; 

u8 wil_p2p_stop_discovery(struct wil6210_vif *vif)
{
	struct wil_p2p_info *p2p = &vif->p2p;
	u8 started = p2p->discovery_started;

	if (p2p->discovery_started) {
		if (p2p->pending_listen_wdev) {
			/* discovery not really started, only pending */
			p2p->pending_listen_wdev = NULL;
		} else {
			del_timer_sync(&p2p->discovery_timer);
			wmi_stop_discovery(vif);
		}
		p2p->discovery_started = 0;
	}

	return started;
}