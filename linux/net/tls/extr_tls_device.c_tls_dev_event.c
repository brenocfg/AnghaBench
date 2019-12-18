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
struct notifier_block {int dummy; } ;
struct net_device {int features; TYPE_1__* tlsdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  tls_dev_del; int /*<<< orphan*/  tls_dev_add; int /*<<< orphan*/  tls_dev_resync; } ;

/* Variables and functions */
#define  NETDEV_DOWN 130 
#define  NETDEV_FEAT_CHANGE 129 
#define  NETDEV_REGISTER 128 
 int NETIF_F_HW_TLS_RX ; 
 int NETIF_F_HW_TLS_TX ; 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int tls_device_down (struct net_device*) ; 

__attribute__((used)) static int tls_dev_event(struct notifier_block *this, unsigned long event,
			 void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);

	if (!dev->tlsdev_ops &&
	    !(dev->features & (NETIF_F_HW_TLS_RX | NETIF_F_HW_TLS_TX)))
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_REGISTER:
	case NETDEV_FEAT_CHANGE:
		if ((dev->features & NETIF_F_HW_TLS_RX) &&
		    !dev->tlsdev_ops->tls_dev_resync)
			return NOTIFY_BAD;

		if  (dev->tlsdev_ops &&
		     dev->tlsdev_ops->tls_dev_add &&
		     dev->tlsdev_ops->tls_dev_del)
			return NOTIFY_DONE;
		else
			return NOTIFY_BAD;
	case NETDEV_DOWN:
		return tls_device_down(dev);
	}
	return NOTIFY_DONE;
}