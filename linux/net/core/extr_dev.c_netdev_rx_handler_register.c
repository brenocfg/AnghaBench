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
struct net_device {int priv_flags; int /*<<< orphan*/  rx_handler; int /*<<< orphan*/  rx_handler_data; } ;
typedef  void rx_handler_func_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int IFF_NO_RX_HANDLER ; 
 scalar_t__ netdev_is_rx_handler_busy (struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,void*) ; 

int netdev_rx_handler_register(struct net_device *dev,
			       rx_handler_func_t *rx_handler,
			       void *rx_handler_data)
{
	if (netdev_is_rx_handler_busy(dev))
		return -EBUSY;

	if (dev->priv_flags & IFF_NO_RX_HANDLER)
		return -EINVAL;

	/* Note: rx_handler_data must be set before rx_handler */
	rcu_assign_pointer(dev->rx_handler_data, rx_handler_data);
	rcu_assign_pointer(dev->rx_handler, rx_handler);

	return 0;
}