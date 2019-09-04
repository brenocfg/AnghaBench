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
struct wl1271 {int /*<<< orphan*/  event_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT ; 
 int wl1271_acx_event_mbox_mask (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int wl1271_event_unmask(struct wl1271 *wl)
{
	int ret;

	wl1271_debug(DEBUG_EVENT, "unmasking event_mask 0x%x", wl->event_mask);
	ret = wl1271_acx_event_mbox_mask(wl, ~(wl->event_mask));
	if (ret < 0)
		return ret;

	return 0;
}