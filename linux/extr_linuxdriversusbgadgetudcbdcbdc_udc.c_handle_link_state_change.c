#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  speed; } ;
struct bdc {int devstatus; int /*<<< orphan*/  dev; TYPE_2__ gadget; TYPE_1__* gadget_driver; int /*<<< orphan*/  func_wake_notify; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* resume ) (TYPE_2__*) ;int /*<<< orphan*/  (* suspend ) (TYPE_2__*) ;} ;

/* Variables and functions */
#define  BDC_LINK_STATE_RESUME 130 
#define  BDC_LINK_STATE_U0 129 
#define  BDC_LINK_STATE_U3 128 
 int BDC_PST (int) ; 
 int /*<<< orphan*/  BDC_TNOTIFY ; 
 int DEVICE_SUSPENDED ; 
 int FUNC_WAKE_ISSUED ; 
 int REMOTE_WAKEUP_ISSUED ; 
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  bdc_function_wake_fh (struct bdc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static void handle_link_state_change(struct bdc *bdc, u32 uspc)
{
	u32 link_state;

	dev_dbg(bdc->dev, "Link state change");
	link_state = BDC_PST(uspc);
	switch (link_state) {
	case BDC_LINK_STATE_U3:
		if ((bdc->gadget.speed != USB_SPEED_UNKNOWN) &&
						bdc->gadget_driver->suspend) {
			dev_dbg(bdc->dev, "Entered Suspend mode\n");
			spin_unlock(&bdc->lock);
			bdc->devstatus |= DEVICE_SUSPENDED;
			bdc->gadget_driver->suspend(&bdc->gadget);
			spin_lock(&bdc->lock);
		}
		break;
	case BDC_LINK_STATE_U0:
		if (bdc->devstatus & REMOTE_WAKEUP_ISSUED) {
					bdc->devstatus &= ~REMOTE_WAKEUP_ISSUED;
			if (bdc->gadget.speed == USB_SPEED_SUPER) {
				bdc_function_wake_fh(bdc, 0);
				bdc->devstatus |= FUNC_WAKE_ISSUED;
				/*
				 * Start a Notification timer and check if the
				 * Host transferred anything on any of the EPs,
				 * if not then send function wake again every
				 * TNotification secs until host initiates
				 * transfer to BDC, USB3 spec Table 8.13
				*/
				schedule_delayed_work(
						&bdc->func_wake_notify,
						msecs_to_jiffies(BDC_TNOTIFY));
				dev_dbg(bdc->dev, "sched func_wake_notify\n");
			}
		}
		break;

	case BDC_LINK_STATE_RESUME:
		dev_dbg(bdc->dev, "Resumed from Suspend\n");
		if (bdc->devstatus & DEVICE_SUSPENDED) {
			bdc->gadget_driver->resume(&bdc->gadget);
			bdc->devstatus &= ~DEVICE_SUSPENDED;
		}
		break;
	default:
		dev_dbg(bdc->dev, "link state:%d\n", link_state);
	}
}