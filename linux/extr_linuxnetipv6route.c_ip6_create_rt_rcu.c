#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rt6_info {int /*<<< orphan*/  dst; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {struct net_device* nh_dev; } ;
struct fib6_info {TYPE_1__ fib6_nh; } ;
struct TYPE_6__ {struct rt6_info* ip6_null_entry; } ;
struct TYPE_7__ {TYPE_2__ ipv6; } ;

/* Variables and functions */
 TYPE_3__* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dst_hold (int /*<<< orphan*/ *) ; 
 unsigned short fib6_info_dst_flags (struct fib6_info*) ; 
 int /*<<< orphan*/  fib6_info_hold_safe (struct fib6_info*) ; 
 int /*<<< orphan*/  fib6_info_release (struct fib6_info*) ; 
 struct rt6_info* ip6_dst_alloc (TYPE_3__*,struct net_device*,unsigned short) ; 
 int /*<<< orphan*/  ip6_rt_copy_init (struct rt6_info*,struct fib6_info*) ; 

__attribute__((used)) static struct rt6_info *ip6_create_rt_rcu(struct fib6_info *rt)
{
	unsigned short flags = fib6_info_dst_flags(rt);
	struct net_device *dev = rt->fib6_nh.nh_dev;
	struct rt6_info *nrt;

	if (!fib6_info_hold_safe(rt))
		goto fallback;

	nrt = ip6_dst_alloc(dev_net(dev), dev, flags);
	if (!nrt) {
		fib6_info_release(rt);
		goto fallback;
	}

	ip6_rt_copy_init(nrt, rt);
	return nrt;

fallback:
	nrt = dev_net(dev)->ipv6.ip6_null_entry;
	dst_hold(&nrt->dst);
	return nrt;
}