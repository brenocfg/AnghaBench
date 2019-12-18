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
struct nl_info {int dummy; } ;
struct nexthop {int /*<<< orphan*/  rb_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  rb_root; } ;
struct net {TYPE_1__ nexthop; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTM_DELNEXTHOP ; 
 int /*<<< orphan*/  __remove_nexthop (struct net*,struct nexthop*,struct nl_info*) ; 
 int /*<<< orphan*/  nexthop_notify (int /*<<< orphan*/ ,struct nexthop*,struct nl_info*) ; 
 int /*<<< orphan*/  nexthop_put (struct nexthop*) ; 
 int /*<<< orphan*/  nh_base_seq_inc (struct net*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_nexthop(struct net *net, struct nexthop *nh,
			   struct nl_info *nlinfo)
{
	/* remove from the tree */
	rb_erase(&nh->rb_node, &net->nexthop.rb_root);

	if (nlinfo)
		nexthop_notify(RTM_DELNEXTHOP, nh, nlinfo);

	__remove_nexthop(net, nh, nlinfo);
	nh_base_seq_inc(net);

	nexthop_put(nh);
}