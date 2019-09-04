#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct net_device {int priv_flags; } ;
struct TYPE_3__ {int carrier; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  open; } ;
typedef  TYPE_1__ hdlc_device ;

/* Variables and functions */
 int IFF_WAN_HDLC ; 
 unsigned long NETDEV_CHANGE ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 TYPE_1__* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  hdlc_proto_start (struct net_device*) ; 
 int /*<<< orphan*/  hdlc_proto_stop (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hdlc_device_event(struct notifier_block *this, unsigned long event,
			     void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	hdlc_device *hdlc;
	unsigned long flags;
	int on;

	if (!net_eq(dev_net(dev), &init_net))
		return NOTIFY_DONE;

	if (!(dev->priv_flags & IFF_WAN_HDLC))
		return NOTIFY_DONE; /* not an HDLC device */

	if (event != NETDEV_CHANGE)
		return NOTIFY_DONE; /* Only interested in carrier changes */

	on = netif_carrier_ok(dev);

#ifdef DEBUG_LINK
	printk(KERN_DEBUG "%s: hdlc_device_event NETDEV_CHANGE, carrier %i\n",
	       dev->name, on);
#endif

	hdlc = dev_to_hdlc(dev);
	spin_lock_irqsave(&hdlc->state_lock, flags);

	if (hdlc->carrier == on)
		goto carrier_exit; /* no change in DCD line level */

	hdlc->carrier = on;

	if (!hdlc->open)
		goto carrier_exit;

	if (hdlc->carrier) {
		netdev_info(dev, "Carrier detected\n");
		hdlc_proto_start(dev);
	} else {
		netdev_info(dev, "Carrier lost\n");
		hdlc_proto_stop(dev);
	}

carrier_exit:
	spin_unlock_irqrestore(&hdlc->state_lock, flags);
	return NOTIFY_DONE;
}