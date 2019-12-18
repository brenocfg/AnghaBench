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
struct TYPE_2__ {int /*<<< orphan*/  lwtstate; int /*<<< orphan*/  lastuse; int /*<<< orphan*/  error; int /*<<< orphan*/  output; int /*<<< orphan*/  input; int /*<<< orphan*/  flags; } ;
struct rtable {scalar_t__ rt_gw_family; TYPE_1__ dst; int /*<<< orphan*/  rt_uncached; int /*<<< orphan*/  rt_gw6; int /*<<< orphan*/  rt_gw4; int /*<<< orphan*/  rt_mtu_locked; int /*<<< orphan*/  rt_pmtu; int /*<<< orphan*/  rt_iif; int /*<<< orphan*/  rt_is_input; int /*<<< orphan*/  rt_type; int /*<<< orphan*/  rt_flags; int /*<<< orphan*/  rt_genid; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  DST_HOST ; 
 int /*<<< orphan*/  DST_OBSOLETE_FORCE_CHK ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct rtable* dst_alloc (int /*<<< orphan*/ *,struct net_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_dst_ops ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  lwtstate_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_genid_ipv4 (int /*<<< orphan*/ ) ; 

struct rtable *rt_dst_clone(struct net_device *dev, struct rtable *rt)
{
	struct rtable *new_rt;

	new_rt = dst_alloc(&ipv4_dst_ops, dev, 1, DST_OBSOLETE_FORCE_CHK,
			   rt->dst.flags);

	if (new_rt) {
		new_rt->rt_genid = rt_genid_ipv4(dev_net(dev));
		new_rt->rt_flags = rt->rt_flags;
		new_rt->rt_type = rt->rt_type;
		new_rt->rt_is_input = rt->rt_is_input;
		new_rt->rt_iif = rt->rt_iif;
		new_rt->rt_pmtu = rt->rt_pmtu;
		new_rt->rt_mtu_locked = rt->rt_mtu_locked;
		new_rt->rt_gw_family = rt->rt_gw_family;
		if (rt->rt_gw_family == AF_INET)
			new_rt->rt_gw4 = rt->rt_gw4;
		else if (rt->rt_gw_family == AF_INET6)
			new_rt->rt_gw6 = rt->rt_gw6;
		INIT_LIST_HEAD(&new_rt->rt_uncached);

		new_rt->dst.flags |= DST_HOST;
		new_rt->dst.input = rt->dst.input;
		new_rt->dst.output = rt->dst.output;
		new_rt->dst.error = rt->dst.error;
		new_rt->dst.lastuse = jiffies;
		new_rt->dst.lwtstate = lwtstate_get(rt->dst.lwtstate);
	}
	return new_rt;
}