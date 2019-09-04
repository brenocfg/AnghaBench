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
struct tun_struct {int dummy; } ;
struct notifier_block {int dummy; } ;
struct net_device {int /*<<< orphan*/ * rtnl_link_ops; } ;

/* Variables and functions */
#define  NETDEV_CHANGE_TX_QUEUE_LEN 128 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 struct tun_struct* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tun_link_ops ; 
 int /*<<< orphan*/  tun_queue_resize (struct tun_struct*) ; 

__attribute__((used)) static int tun_device_event(struct notifier_block *unused,
			    unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct tun_struct *tun = netdev_priv(dev);

	if (dev->rtnl_link_ops != &tun_link_ops)
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_CHANGE_TX_QUEUE_LEN:
		if (tun_queue_resize(tun))
			return NOTIFY_BAD;
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}