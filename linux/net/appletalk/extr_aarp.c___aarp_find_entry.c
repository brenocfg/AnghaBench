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
struct net_device {int dummy; } ;
struct atalk_addr {scalar_t__ s_net; scalar_t__ s_node; } ;
struct TYPE_2__ {scalar_t__ s_net; scalar_t__ s_node; } ;
struct aarp_entry {struct aarp_entry* next; struct net_device* dev; TYPE_1__ target_addr; } ;

/* Variables and functions */

__attribute__((used)) static struct aarp_entry *__aarp_find_entry(struct aarp_entry *list,
					    struct net_device *dev,
					    struct atalk_addr *sat)
{
	while (list) {
		if (list->target_addr.s_net == sat->s_net &&
		    list->target_addr.s_node == sat->s_node &&
		    list->dev == dev)
			break;
		list = list->next;
	}

	return list;
}