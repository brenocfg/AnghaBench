#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct uwb_rc {TYPE_2__ uwb_dev; scalar_t__ ready; } ;
struct TYPE_3__ {int /*<<< orphan*/  rceb; } ;
struct uwb_event {int type; TYPE_1__ notif; struct uwb_rc* rc; } ;

/* Variables and functions */
#define  UWB_EVT_TYPE_MSG 129 
#define  UWB_EVT_TYPE_NOTIF 128 
 int /*<<< orphan*/  __uwb_rc_put (struct uwb_rc*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwbd_event_handle_message (struct uwb_event*) ; 
 int uwbd_event_handle_urc (struct uwb_event*) ; 

__attribute__((used)) static void uwbd_event_handle(struct uwb_event *evt)
{
	struct uwb_rc *rc;
	int should_keep;

	rc = evt->rc;

	if (rc->ready) {
		switch (evt->type) {
		case UWB_EVT_TYPE_NOTIF:
			should_keep = uwbd_event_handle_urc(evt);
			if (should_keep <= 0)
				kfree(evt->notif.rceb);
			break;
		case UWB_EVT_TYPE_MSG:
			uwbd_event_handle_message(evt);
			break;
		default:
			dev_err(&rc->uwb_dev.dev, "UWBD: invalid event type %d\n", evt->type);
			break;
		}
	}

	__uwb_rc_put(rc);	/* for the __uwb_rc_get() in uwb_rc_notif_cb() */
}