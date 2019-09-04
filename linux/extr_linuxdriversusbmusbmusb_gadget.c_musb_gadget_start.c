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
struct usb_otg {int /*<<< orphan*/  state; } ;
struct usb_gadget_driver {scalar_t__ max_speed; } ;
struct usb_gadget {int dummy; } ;
struct musb {int is_active; int /*<<< orphan*/  controller; TYPE_1__* xceiv; int /*<<< orphan*/  lock; int /*<<< orphan*/  g; struct usb_gadget_driver* gadget_driver; scalar_t__ softconnect; } ;
struct TYPE_2__ {scalar_t__ last_event; struct usb_otg* otg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OTG_STATE_B_IDLE ; 
 scalar_t__ USB_EVENT_ID ; 
 scalar_t__ USB_SPEED_HIGH ; 
 struct musb* gadget_to_musb (struct usb_gadget*) ; 
 int /*<<< orphan*/  musb_platform_set_vbus (struct musb*,int) ; 
 int /*<<< orphan*/  musb_start (struct musb*) ; 
 int /*<<< orphan*/  otg_set_peripheral (struct usb_otg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int musb_gadget_start(struct usb_gadget *g,
		struct usb_gadget_driver *driver)
{
	struct musb		*musb = gadget_to_musb(g);
	struct usb_otg		*otg = musb->xceiv->otg;
	unsigned long		flags;
	int			retval = 0;

	if (driver->max_speed < USB_SPEED_HIGH) {
		retval = -EINVAL;
		goto err;
	}

	pm_runtime_get_sync(musb->controller);

	musb->softconnect = 0;
	musb->gadget_driver = driver;

	spin_lock_irqsave(&musb->lock, flags);
	musb->is_active = 1;

	otg_set_peripheral(otg, &musb->g);
	musb->xceiv->otg->state = OTG_STATE_B_IDLE;
	spin_unlock_irqrestore(&musb->lock, flags);

	musb_start(musb);

	/* REVISIT:  funcall to other code, which also
	 * handles power budgeting ... this way also
	 * ensures HdrcStart is indirectly called.
	 */
	if (musb->xceiv->last_event == USB_EVENT_ID)
		musb_platform_set_vbus(musb, 1);

	pm_runtime_mark_last_busy(musb->controller);
	pm_runtime_put_autosuspend(musb->controller);

	return 0;

err:
	return retval;
}