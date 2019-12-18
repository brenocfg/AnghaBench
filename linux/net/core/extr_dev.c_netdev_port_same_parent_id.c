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
struct netdev_phys_item_id {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ dev_get_port_parent_id (struct net_device*,struct netdev_phys_item_id*,int) ; 
 int netdev_phys_item_id_same (struct netdev_phys_item_id*,struct netdev_phys_item_id*) ; 

bool netdev_port_same_parent_id(struct net_device *a, struct net_device *b)
{
	struct netdev_phys_item_id a_id = { };
	struct netdev_phys_item_id b_id = { };

	if (dev_get_port_parent_id(a, &a_id, true) ||
	    dev_get_port_parent_id(b, &b_id, true))
		return false;

	return netdev_phys_item_id_same(&a_id, &b_id);
}