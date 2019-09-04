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
struct rmnet_port {int dummy; } ;
struct net_device {int /*<<< orphan*/  rx_handler_data; } ;

/* Variables and functions */
 struct rmnet_port* rcu_dereference_rtnl (int /*<<< orphan*/ ) ; 
 scalar_t__ rmnet_is_real_dev_registered (struct net_device*) ; 

struct rmnet_port *rmnet_get_port(struct net_device *real_dev)
{
	if (rmnet_is_real_dev_registered(real_dev))
		return rcu_dereference_rtnl(real_dev->rx_handler_data);
	else
		return NULL;
}