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
struct net_device {int dummy; } ;

/* Variables and functions */
#define  NETDEV_DOWN 130 
#define  NETDEV_FEAT_CHANGE 129 
#define  NETDEV_REGISTER 128 
 int NOTIFY_DONE ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int xfrm_dev_down (struct net_device*) ; 
 int xfrm_dev_feat_change (struct net_device*) ; 
 int xfrm_dev_register (struct net_device*) ; 

__attribute__((used)) static int xfrm_dev_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);

	switch (event) {
	case NETDEV_REGISTER:
		return xfrm_dev_register(dev);

	case NETDEV_FEAT_CHANGE:
		return xfrm_dev_feat_change(dev);

	case NETDEV_DOWN:
		return xfrm_dev_down(dev);
	}
	return NOTIFY_DONE;
}