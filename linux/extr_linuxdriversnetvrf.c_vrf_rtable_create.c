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
struct TYPE_2__ {int /*<<< orphan*/  output; } ;
struct rtable {TYPE_1__ dst; } ;
struct net_vrf {int /*<<< orphan*/  rth; int /*<<< orphan*/  tb_id; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RTN_UNICAST ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  fib_new_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_vrf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct rtable*) ; 
 struct rtable* rt_dst_alloc (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrf_output ; 

__attribute__((used)) static int vrf_rtable_create(struct net_device *dev)
{
	struct net_vrf *vrf = netdev_priv(dev);
	struct rtable *rth;

	if (!fib_new_table(dev_net(dev), vrf->tb_id))
		return -ENOMEM;

	/* create a dst for routing packets out through a VRF device */
	rth = rt_dst_alloc(dev, 0, RTN_UNICAST, 1, 1, 0);
	if (!rth)
		return -ENOMEM;

	rth->dst.output	= vrf_output;

	rcu_assign_pointer(vrf->rth, rth);

	return 0;
}