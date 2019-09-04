#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int /*<<< orphan*/  phydev; } ;
struct lan78xx_net {int link_on; int /*<<< orphan*/  intf; int /*<<< orphan*/  flags; int /*<<< orphan*/  net; scalar_t__ urb_intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_DEV_OPEN ; 
 int /*<<< orphan*/  EVENT_LINK_RESET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  lan78xx_defer_kevent (struct lan78xx_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan78xx_init_stats (struct lan78xx_net*) ; 
 struct lan78xx_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct lan78xx_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_err (struct lan78xx_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int usb_submit_urb (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan78xx_open(struct net_device *net)
{
	struct lan78xx_net *dev = netdev_priv(net);
	int ret;

	ret = usb_autopm_get_interface(dev->intf);
	if (ret < 0)
		goto out;

	phy_start(net->phydev);

	netif_dbg(dev, ifup, dev->net, "phy initialised successfully");

	/* for Link Check */
	if (dev->urb_intr) {
		ret = usb_submit_urb(dev->urb_intr, GFP_KERNEL);
		if (ret < 0) {
			netif_err(dev, ifup, dev->net,
				  "intr submit %d\n", ret);
			goto done;
		}
	}

	lan78xx_init_stats(dev);

	set_bit(EVENT_DEV_OPEN, &dev->flags);

	netif_start_queue(net);

	dev->link_on = false;

	lan78xx_defer_kevent(dev, EVENT_LINK_RESET);
done:
	usb_autopm_put_interface(dev->intf);

out:
	return ret;
}