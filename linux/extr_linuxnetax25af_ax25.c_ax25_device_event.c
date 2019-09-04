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
struct notifier_block {int dummy; } ;
struct net_device {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_AX25 ; 
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  ax25_dev_device_down (struct net_device*) ; 
 int /*<<< orphan*/  ax25_dev_device_up (struct net_device*) ; 
 int /*<<< orphan*/  ax25_kill_by_device (struct net_device*) ; 
 int /*<<< orphan*/  ax25_rt_device_down (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 

__attribute__((used)) static int ax25_device_event(struct notifier_block *this, unsigned long event,
			     void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);

	if (!net_eq(dev_net(dev), &init_net))
		return NOTIFY_DONE;

	/* Reject non AX.25 devices */
	if (dev->type != ARPHRD_AX25)
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		ax25_dev_device_up(dev);
		break;
	case NETDEV_DOWN:
		ax25_kill_by_device(dev);
		ax25_rt_device_down(dev);
		ax25_dev_device_down(dev);
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}