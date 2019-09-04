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
typedef  int /*<<< orphan*/  u32 ;
struct wl1271 {int dummy; } ;
typedef  enum wlcore_wait_event { ____Placeholder_wlcore_wait_event } wlcore_wait_event ;

/* Variables and functions */
 int /*<<< orphan*/  DFS_CHANNELS_CONFIG_COMPLETE_EVENT ; 
 int /*<<< orphan*/  PEER_REMOVE_COMPLETE_EVENT_ID ; 
#define  WLCORE_EVENT_DFS_CONFIG_COMPLETE 129 
#define  WLCORE_EVENT_PEER_REMOVE_COMPLETE 128 
 int wlcore_cmd_wait_for_event_or_timeout (struct wl1271*,int /*<<< orphan*/ ,int*) ; 

int wl18xx_wait_for_event(struct wl1271 *wl, enum wlcore_wait_event event,
			  bool *timeout)
{
	u32 local_event;

	switch (event) {
	case WLCORE_EVENT_PEER_REMOVE_COMPLETE:
		local_event = PEER_REMOVE_COMPLETE_EVENT_ID;
		break;

	case WLCORE_EVENT_DFS_CONFIG_COMPLETE:
		local_event = DFS_CHANNELS_CONFIG_COMPLETE_EVENT;
		break;

	default:
		/* event not implemented */
		return 0;
	}
	return wlcore_cmd_wait_for_event_or_timeout(wl, local_event, timeout);
}