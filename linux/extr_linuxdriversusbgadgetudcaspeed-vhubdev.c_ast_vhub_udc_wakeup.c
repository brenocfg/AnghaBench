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
struct usb_gadget {int dummy; } ;
struct ast_vhub_dev {TYPE_1__* vhub; int /*<<< orphan*/  wakeup_en; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDBG (struct ast_vhub_dev*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ast_vhub_hub_wake_all (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ast_vhub_dev* to_ast_dev (struct usb_gadget*) ; 

__attribute__((used)) static int ast_vhub_udc_wakeup(struct usb_gadget* gadget)
{
	struct ast_vhub_dev *d = to_ast_dev(gadget);
	unsigned long flags;
	int rc = -EINVAL;

	spin_lock_irqsave(&d->vhub->lock, flags);
	if (!d->wakeup_en)
		goto err;

	DDBG(d, "Device initiated wakeup\n");

	/* Wakeup the host */
	ast_vhub_hub_wake_all(d->vhub);
	rc = 0;
 err:
	spin_unlock_irqrestore(&d->vhub->lock, flags);
	return rc;
}