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
struct TYPE_5__ {scalar_t__ speed; int /*<<< orphan*/  ep_list; } ;
struct udc {TYPE_3__* ep; TYPE_2__ gadget; } ;
struct TYPE_4__ {int /*<<< orphan*/  ep_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  fifo_depth; TYPE_1__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t UDC_EPIN_IX ; 
 int /*<<< orphan*/  UDC_EPIN_SMALLINT_BUFF_SIZE ; 
 size_t UDC_EPIN_STATUS_IX ; 
 size_t UDC_EPOUT_IX ; 
 int /*<<< orphan*/  UDC_FS_EPIN_BUFF_SIZE ; 
 int /*<<< orphan*/  UDC_RXFIFO_SIZE ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  hs_tx_buf ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void make_ep_lists(struct udc *dev)
{
	/* make gadget ep lists */
	INIT_LIST_HEAD(&dev->gadget.ep_list);
	list_add_tail(&dev->ep[UDC_EPIN_STATUS_IX].ep.ep_list,
						&dev->gadget.ep_list);
	list_add_tail(&dev->ep[UDC_EPIN_IX].ep.ep_list,
						&dev->gadget.ep_list);
	list_add_tail(&dev->ep[UDC_EPOUT_IX].ep.ep_list,
						&dev->gadget.ep_list);

	/* fifo config */
	dev->ep[UDC_EPIN_STATUS_IX].fifo_depth = UDC_EPIN_SMALLINT_BUFF_SIZE;
	if (dev->gadget.speed == USB_SPEED_FULL)
		dev->ep[UDC_EPIN_IX].fifo_depth = UDC_FS_EPIN_BUFF_SIZE;
	else if (dev->gadget.speed == USB_SPEED_HIGH)
		dev->ep[UDC_EPIN_IX].fifo_depth = hs_tx_buf;
	dev->ep[UDC_EPOUT_IX].fifo_depth = UDC_RXFIFO_SIZE;
}