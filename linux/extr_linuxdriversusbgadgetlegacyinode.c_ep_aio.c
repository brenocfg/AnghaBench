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
struct usb_request {char* buf; size_t length; struct kiocb* context; int /*<<< orphan*/  complete; } ;
struct kiocb_priv {struct kiocb_priv* to_free; struct usb_request* req; int /*<<< orphan*/  mm; scalar_t__ actual; struct ep_data* epdata; struct kiocb* iocb; } ;
struct kiocb {struct kiocb_priv* private; } ;
struct ep_data {TYPE_1__* dev; int /*<<< orphan*/ * ep; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIOCBQUEUED ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  ep_aio_cancel ; 
 int /*<<< orphan*/  ep_aio_complete ; 
 int /*<<< orphan*/  get_ep (struct ep_data*) ; 
 int /*<<< orphan*/  kfree (struct kiocb_priv*) ; 
 int /*<<< orphan*/  kiocb_set_cancel_fn (struct kiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ep (struct ep_data*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct usb_request* usb_ep_alloc_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_free_request (int /*<<< orphan*/ *,struct usb_request*) ; 
 int /*<<< orphan*/  usb_ep_queue (int /*<<< orphan*/ *,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ep_aio(struct kiocb *iocb,
		      struct kiocb_priv *priv,
		      struct ep_data *epdata,
		      char *buf,
		      size_t len)
{
	struct usb_request *req;
	ssize_t value;

	iocb->private = priv;
	priv->iocb = iocb;

	kiocb_set_cancel_fn(iocb, ep_aio_cancel);
	get_ep(epdata);
	priv->epdata = epdata;
	priv->actual = 0;
	priv->mm = current->mm; /* mm teardown waits for iocbs in exit_aio() */

	/* each kiocb is coupled to one usb_request, but we can't
	 * allocate or submit those if the host disconnected.
	 */
	spin_lock_irq(&epdata->dev->lock);
	value = -ENODEV;
	if (unlikely(epdata->ep == NULL))
		goto fail;

	req = usb_ep_alloc_request(epdata->ep, GFP_ATOMIC);
	value = -ENOMEM;
	if (unlikely(!req))
		goto fail;

	priv->req = req;
	req->buf = buf;
	req->length = len;
	req->complete = ep_aio_complete;
	req->context = iocb;
	value = usb_ep_queue(epdata->ep, req, GFP_ATOMIC);
	if (unlikely(0 != value)) {
		usb_ep_free_request(epdata->ep, req);
		goto fail;
	}
	spin_unlock_irq(&epdata->dev->lock);
	return -EIOCBQUEUED;

fail:
	spin_unlock_irq(&epdata->dev->lock);
	kfree(priv->to_free);
	kfree(priv);
	put_ep(epdata);
	return value;
}