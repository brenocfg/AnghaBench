#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  intr_urb; int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  usb; int /*<<< orphan*/  net; int /*<<< orphan*/  intr_interval; int /*<<< orphan*/  intr_buff; TYPE_7__* rx_skb; } ;
typedef  TYPE_1__ pegasus_t ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EthID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PEGASUS_MTU ; 
 TYPE_7__* __netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int enable_net_traffic (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  intr_callback ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (TYPE_1__*,int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  read_bulk_callback ; 
 int /*<<< orphan*/  set_carrier (struct net_device*) ; 
 int set_registers (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pegasus_open(struct net_device *net)
{
	pegasus_t *pegasus = netdev_priv(net);
	int res=-ENOMEM;

	if (pegasus->rx_skb == NULL)
		pegasus->rx_skb = __netdev_alloc_skb_ip_align(pegasus->net,
							      PEGASUS_MTU,
							      GFP_KERNEL);
	if (!pegasus->rx_skb)
		goto exit;

	res = set_registers(pegasus, EthID, 6, net->dev_addr);

	usb_fill_bulk_urb(pegasus->rx_urb, pegasus->usb,
			  usb_rcvbulkpipe(pegasus->usb, 1),
			  pegasus->rx_skb->data, PEGASUS_MTU,
			  read_bulk_callback, pegasus);
	if ((res = usb_submit_urb(pegasus->rx_urb, GFP_KERNEL))) {
		if (res == -ENODEV)
			netif_device_detach(pegasus->net);
		netif_dbg(pegasus, ifup, net, "failed rx_urb, %d\n", res);
		goto exit;
	}

	usb_fill_int_urb(pegasus->intr_urb, pegasus->usb,
			 usb_rcvintpipe(pegasus->usb, 3),
			 pegasus->intr_buff, sizeof(pegasus->intr_buff),
			 intr_callback, pegasus, pegasus->intr_interval);
	if ((res = usb_submit_urb(pegasus->intr_urb, GFP_KERNEL))) {
		if (res == -ENODEV)
			netif_device_detach(pegasus->net);
		netif_dbg(pegasus, ifup, net, "failed intr_urb, %d\n", res);
		usb_kill_urb(pegasus->rx_urb);
		goto exit;
	}
	res = enable_net_traffic(net, pegasus->usb);
	if (res < 0) {
		netif_dbg(pegasus, ifup, net,
			  "can't enable_net_traffic() - %d\n", res);
		res = -EIO;
		usb_kill_urb(pegasus->rx_urb);
		usb_kill_urb(pegasus->intr_urb);
		goto exit;
	}
	set_carrier(net);
	netif_start_queue(net);
	netif_dbg(pegasus, ifup, net, "open\n");
	res = 0;
exit:
	return res;
}