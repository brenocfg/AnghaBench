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
struct usb_gadget {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  speed; } ;
struct ast_vhub_dev {TYPE_1__* vhub; scalar_t__ enabled; TYPE_2__ gadget; int /*<<< orphan*/ * driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDBG (struct ast_vhub_dev*,char*) ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  ast_vhub_dev_disable (struct ast_vhub_dev*) ; 
 int /*<<< orphan*/  ast_vhub_dev_nuke (struct ast_vhub_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ast_vhub_dev* to_ast_dev (struct usb_gadget*) ; 

__attribute__((used)) static int ast_vhub_udc_stop(struct usb_gadget *gadget)
{
	struct ast_vhub_dev *d = to_ast_dev(gadget);
	unsigned long flags;

	spin_lock_irqsave(&d->vhub->lock, flags);

	DDBG(d, "stop\n");

	d->driver = NULL;
	d->gadget.speed = USB_SPEED_UNKNOWN;

	ast_vhub_dev_nuke(d);

	if (d->enabled)
		ast_vhub_dev_disable(d);

	spin_unlock_irqrestore(&d->vhub->lock, flags);

	return 0;
}