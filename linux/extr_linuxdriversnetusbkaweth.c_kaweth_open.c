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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct kaweth_device {int opened; TYPE_3__* intf; int /*<<< orphan*/  rx_urb; TYPE_1__* irq_urb; int /*<<< orphan*/  intbufferhandle; int /*<<< orphan*/  intbuffer; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTBUFFERSIZE ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  int_callback ; 
 int /*<<< orphan*/  kaweth_async_set_rx_mode (struct kaweth_device*) ; 
 int kaweth_resubmit_rx_urb (struct kaweth_device*,int /*<<< orphan*/ ) ; 
 struct kaweth_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int usb_autopm_get_interface (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kaweth_device*,int) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kaweth_open(struct net_device *net)
{
	struct kaweth_device *kaweth = netdev_priv(net);
	int res;

	res = usb_autopm_get_interface(kaweth->intf);
	if (res) {
		dev_err(&kaweth->intf->dev, "Interface cannot be resumed.\n");
		return -EIO;
	}
	res = kaweth_resubmit_rx_urb(kaweth, GFP_KERNEL);
	if (res)
		goto err_out;

	usb_fill_int_urb(
		kaweth->irq_urb,
		kaweth->dev,
		usb_rcvintpipe(kaweth->dev, 3),
		kaweth->intbuffer,
		INTBUFFERSIZE,
		int_callback,
		kaweth,
		250); /* overriding the descriptor */
	kaweth->irq_urb->transfer_dma = kaweth->intbufferhandle;
	kaweth->irq_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	res = usb_submit_urb(kaweth->irq_urb, GFP_KERNEL);
	if (res) {
		usb_kill_urb(kaweth->rx_urb);
		goto err_out;
	}
	kaweth->opened = 1;

	netif_start_queue(net);

	kaweth_async_set_rx_mode(kaweth);
	return 0;

err_out:
	usb_autopm_put_interface(kaweth->intf);
	return -EIO;
}