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
struct kaweth_device {int suspend_lowmem_rx; TYPE_1__* intf; int /*<<< orphan*/  lowmem_work; TYPE_2__* rx_urb; int /*<<< orphan*/  rxbufferhandle; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_5__ {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  KAWETH_BUF_SIZE ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kaweth_usb_receive ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kaweth_device*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kaweth_resubmit_rx_urb(struct kaweth_device *kaweth,
						gfp_t mem_flags)
{
	int result;

	usb_fill_bulk_urb(kaweth->rx_urb,
		      kaweth->dev,
		      usb_rcvbulkpipe(kaweth->dev, 1),
		      kaweth->rx_buf,
		      KAWETH_BUF_SIZE,
		      kaweth_usb_receive,
		      kaweth);
	kaweth->rx_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	kaweth->rx_urb->transfer_dma = kaweth->rxbufferhandle;

	if((result = usb_submit_urb(kaweth->rx_urb, mem_flags))) {
		if (result == -ENOMEM) {
			kaweth->suspend_lowmem_rx = 1;
			schedule_delayed_work(&kaweth->lowmem_work, HZ/4);
		}
		dev_err(&kaweth->intf->dev, "resubmitting rx_urb %d failed\n",
			result);
	} else {
		kaweth->suspend_lowmem_rx = 0;
	}

	return result;
}