#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct twl4030_usb {int linkstat; int musb_mailbox_pending; TYPE_1__* dev; int /*<<< orphan*/  id_workaround_work; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum musb_vbus_id_status { ____Placeholder_musb_vbus_id_status } musb_vbus_id_status ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MUSB_ID_GROUND ; 
 scalar_t__ cable_present (int) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int musb_mailbox (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_runtime_active (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (TYPE_1__*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int twl4030_usb_linkstat (struct twl4030_usb*) ; 

__attribute__((used)) static irqreturn_t twl4030_usb_irq(int irq, void *_twl)
{
	struct twl4030_usb *twl = _twl;
	enum musb_vbus_id_status status;
	bool status_changed = false;
	int err;

	status = twl4030_usb_linkstat(twl);

	mutex_lock(&twl->lock);
	if (status >= 0 && status != twl->linkstat) {
		status_changed =
			cable_present(twl->linkstat) !=
			cable_present(status);
		twl->linkstat = status;
	}
	mutex_unlock(&twl->lock);

	if (status_changed) {
		/* FIXME add a set_power() method so that B-devices can
		 * configure the charger appropriately.  It's not always
		 * correct to consume VBUS power, and how much current to
		 * consume is a function of the USB configuration chosen
		 * by the host.
		 *
		 * REVISIT usb_gadget_vbus_connect(...) as needed, ditto
		 * its disconnect() sibling, when changing to/from the
		 * USB_LINK_VBUS state.  musb_hdrc won't care until it
		 * starts to handle softconnect right.
		 */
		if (cable_present(status)) {
			pm_runtime_get_sync(twl->dev);
		} else {
			pm_runtime_mark_last_busy(twl->dev);
			pm_runtime_put_autosuspend(twl->dev);
		}
		twl->musb_mailbox_pending = true;
	}
	if (twl->musb_mailbox_pending) {
		err = musb_mailbox(status);
		if (!err)
			twl->musb_mailbox_pending = false;
	}

	/* don't schedule during sleep - irq works right then */
	if (status == MUSB_ID_GROUND && pm_runtime_active(twl->dev)) {
		cancel_delayed_work(&twl->id_workaround_work);
		schedule_delayed_work(&twl->id_workaround_work, HZ);
	}

	if (irq)
		sysfs_notify(&twl->dev->kobj, NULL, "vbus");

	return IRQ_HANDLED;
}