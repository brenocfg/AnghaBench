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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ last_id_allocated; } ;
struct net {TYPE_1__ nexthop; } ;

/* Variables and functions */
 int /*<<< orphan*/  nexthop_find_by_id (struct net*,scalar_t__) ; 

__attribute__((used)) static u32 nh_find_unused_id(struct net *net)
{
	u32 id_start = net->nexthop.last_id_allocated;

	while (1) {
		net->nexthop.last_id_allocated++;
		if (net->nexthop.last_id_allocated == id_start)
			break;

		if (!nexthop_find_by_id(net, net->nexthop.last_id_allocated))
			return net->nexthop.last_id_allocated;
	}
	return 0;
}