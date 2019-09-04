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
struct urb {int /*<<< orphan*/ * setup_packet; int /*<<< orphan*/ * transfer_buffer; } ;
struct stub_priv {int /*<<< orphan*/  seqnum; struct urb* urb; } ;
struct stub_device {TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct stub_priv*) ; 
 int /*<<< orphan*/  stub_priv_cache ; 
 struct stub_priv* stub_priv_pop (struct stub_device*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 

void stub_device_cleanup_urbs(struct stub_device *sdev)
{
	struct stub_priv *priv;
	struct urb *urb;

	dev_dbg(&sdev->udev->dev, "Stub device cleaning up urbs\n");

	while ((priv = stub_priv_pop(sdev))) {
		urb = priv->urb;
		dev_dbg(&sdev->udev->dev, "free urb seqnum %lu\n",
			priv->seqnum);
		usb_kill_urb(urb);

		kmem_cache_free(stub_priv_cache, priv);

		kfree(urb->transfer_buffer);
		urb->transfer_buffer = NULL;

		kfree(urb->setup_packet);
		urb->setup_packet = NULL;

		usb_free_urb(urb);
	}
}