#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rt6_info {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* rt6_stats; int /*<<< orphan*/  ip6_dst_ops; } ;
struct net {TYPE_2__ ipv6; } ;
struct TYPE_3__ {int /*<<< orphan*/  fib_rt_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_OBSOLETE_FORCE_CHK ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct rt6_info* dst_alloc (int /*<<< orphan*/ *,struct net_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt6_info_init (struct rt6_info*) ; 

struct rt6_info *ip6_dst_alloc(struct net *net, struct net_device *dev,
			       int flags)
{
	struct rt6_info *rt = dst_alloc(&net->ipv6.ip6_dst_ops, dev,
					1, DST_OBSOLETE_FORCE_CHK, flags);

	if (rt) {
		rt6_info_init(rt);
		atomic_inc(&net->ipv6.rt6_stats->fib_rt_alloc);
	}

	return rt;
}