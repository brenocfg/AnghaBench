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
struct usb_lcd {int /*<<< orphan*/  limit_sem; TYPE_1__* interface; } ;
struct urb {int status; int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  dev; struct usb_lcd* context; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int ENOENT ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lcd_write_bulk_callback(struct urb *urb)
{
	struct usb_lcd *dev;
	int status = urb->status;

	dev = urb->context;

	/* sync/async unlink faults aren't errors */
	if (status &&
	    !(status == -ENOENT ||
	      status == -ECONNRESET ||
	      status == -ESHUTDOWN)) {
		dev_dbg(&dev->interface->dev,
			"nonzero write bulk status received: %d\n", status);
	}

	/* free up our allocated buffer */
	usb_free_coherent(urb->dev, urb->transfer_buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);
	up(&dev->limit_sem);
}