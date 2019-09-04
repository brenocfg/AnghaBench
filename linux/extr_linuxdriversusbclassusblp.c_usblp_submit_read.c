#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usblp {size_t current_protocol; int rcomplete; int rstatus; int /*<<< orphan*/  lock; TYPE_3__* intf; scalar_t__ readcount; int /*<<< orphan*/  urbs; int /*<<< orphan*/  readbuf; TYPE_2__* protocol; int /*<<< orphan*/  dev; } ;
struct urb {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* epread; } ;
struct TYPE_4__ {int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USBLP_BUF_SIZE_IN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usblp*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 
 int /*<<< orphan*/  usblp_bulk_read ; 

__attribute__((used)) static int usblp_submit_read(struct usblp *usblp)
{
	struct urb *urb;
	unsigned long flags;
	int rc;

	rc = -ENOMEM;
	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (urb == NULL)
		goto raise_urb;

	usb_fill_bulk_urb(urb, usblp->dev,
		usb_rcvbulkpipe(usblp->dev,
		  usblp->protocol[usblp->current_protocol].epread->bEndpointAddress),
		usblp->readbuf, USBLP_BUF_SIZE_IN,
		usblp_bulk_read, usblp);
	usb_anchor_urb(urb, &usblp->urbs);

	spin_lock_irqsave(&usblp->lock, flags);
	usblp->readcount = 0; /* XXX Why here? */
	usblp->rcomplete = 0;
	spin_unlock_irqrestore(&usblp->lock, flags);
	if ((rc = usb_submit_urb(urb, GFP_KERNEL)) < 0) {
		dev_dbg(&usblp->intf->dev, "error submitting urb (%d)\n", rc);
		spin_lock_irqsave(&usblp->lock, flags);
		usblp->rstatus = rc;
		usblp->rcomplete = 1;
		spin_unlock_irqrestore(&usblp->lock, flags);
		goto raise_submit;
	}

	return 0;

raise_submit:
	usb_unanchor_urb(urb);
	usb_free_urb(urb);
raise_urb:
	return rc;
}