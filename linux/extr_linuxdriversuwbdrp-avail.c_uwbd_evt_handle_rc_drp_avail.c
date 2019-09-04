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
struct TYPE_2__ {int ie_valid; int /*<<< orphan*/  global; } ;
struct uwb_rc {int /*<<< orphan*/  rsvs_mutex; TYPE_1__ drp_avail; } ;
struct uwb_event {struct uwb_rc* rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UWB_NUM_MAS ; 
 int /*<<< orphan*/  bitmap_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bmp ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_rsv_handle_drp_avail_change (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rsv_sched_update (struct uwb_rc*) ; 
 int uwbd_evt_get_drp_avail (struct uwb_event*,int /*<<< orphan*/ ) ; 

int uwbd_evt_handle_rc_drp_avail(struct uwb_event *evt)
{
	int result;
	struct uwb_rc *rc = evt->rc;
	DECLARE_BITMAP(bmp, UWB_NUM_MAS);

	result = uwbd_evt_get_drp_avail(evt, bmp);
	if (result < 0)
		return result;

	mutex_lock(&rc->rsvs_mutex);
	bitmap_copy(rc->drp_avail.global, bmp, UWB_NUM_MAS);
	rc->drp_avail.ie_valid = false;
	uwb_rsv_handle_drp_avail_change(rc);
	mutex_unlock(&rc->rsvs_mutex);

	uwb_rsv_sched_update(rc);

	return 0;
}