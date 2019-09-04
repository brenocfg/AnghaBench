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
struct urb {int status; int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  dev; struct iowarrior* context; } ;
struct iowarrior {int /*<<< orphan*/  write_wait; int /*<<< orphan*/  write_busy; TYPE_1__* interface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int ENOENT ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iowarrior_write_callback(struct urb *urb)
{
	struct iowarrior *dev;
	int status = urb->status;

	dev = urb->context;
	/* sync/async unlink faults aren't errors */
	if (status &&
	    !(status == -ENOENT ||
	      status == -ECONNRESET || status == -ESHUTDOWN)) {
		dev_dbg(&dev->interface->dev,
			"nonzero write bulk status received: %d\n", status);
	}
	/* free up our allocated buffer */
	usb_free_coherent(urb->dev, urb->transfer_buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);
	/* tell a waiting writer the interrupt-out-pipe is available again */
	atomic_dec(&dev->write_busy);
	wake_up_interruptible(&dev->write_wait);
}