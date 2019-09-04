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
struct TYPE_4__ {int in_use; int /*<<< orphan*/  data_buf; } ;
struct vnt_private {TYPE_1__ int_buf; TYPE_2__* usb; int /*<<< orphan*/  interrupt_urb; int /*<<< orphan*/  int_interval; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MAX_INTERRUPT_SIZE ; 
 int STATUS_FAILURE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvintpipe (TYPE_2__*,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_start_interrupt_urb_complete ; 

int vnt_start_interrupt_urb(struct vnt_private *priv)
{
	int status = STATUS_FAILURE;

	if (priv->int_buf.in_use)
		return STATUS_FAILURE;

	priv->int_buf.in_use = true;

	usb_fill_int_urb(priv->interrupt_urb,
			 priv->usb,
			 usb_rcvintpipe(priv->usb, 1),
			 priv->int_buf.data_buf,
			 MAX_INTERRUPT_SIZE,
			 vnt_start_interrupt_urb_complete,
			 priv,
			 priv->int_interval);

	status = usb_submit_urb(priv->interrupt_urb, GFP_ATOMIC);
	if (status) {
		dev_dbg(&priv->usb->dev, "Submit int URB failed %d\n", status);
		priv->int_buf.in_use = false;
	}

	return status;
}