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
struct rt6key {int dummy; } ;
struct dst_entry {int __use; int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
struct rt6_info {int rt6i_flags; int /*<<< orphan*/  rt6i_src; int /*<<< orphan*/  rt6i_dst; int /*<<< orphan*/  rt6i_gateway; int /*<<< orphan*/  rt6i_idev; struct dst_entry dst; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* rt6_stats; } ;
struct net {TYPE_2__ ipv6; struct net_device* loopback_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  fib_rt_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_OBSOLETE_DEAD ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dst_entry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int RTF_PCPU ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct rt6_info* dst_alloc (int /*<<< orphan*/ *,struct net_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_copy_metrics (struct dst_entry*,struct dst_entry*) ; 
 int /*<<< orphan*/  dst_discard ; 
 int /*<<< orphan*/  dst_discard_out ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  ip6_dst_blackhole_ops ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rt6_info_init (struct rt6_info*) ; 

struct dst_entry *ip6_blackhole_route(struct net *net, struct dst_entry *dst_orig)
{
	struct rt6_info *rt, *ort = (struct rt6_info *) dst_orig;
	struct net_device *loopback_dev = net->loopback_dev;
	struct dst_entry *new = NULL;

	rt = dst_alloc(&ip6_dst_blackhole_ops, loopback_dev, 1,
		       DST_OBSOLETE_DEAD, 0);
	if (rt) {
		rt6_info_init(rt);
		atomic_inc(&net->ipv6.rt6_stats->fib_rt_alloc);

		new = &rt->dst;
		new->__use = 1;
		new->input = dst_discard;
		new->output = dst_discard_out;

		dst_copy_metrics(new, &ort->dst);

		rt->rt6i_idev = in6_dev_get(loopback_dev);
		rt->rt6i_gateway = ort->rt6i_gateway;
		rt->rt6i_flags = ort->rt6i_flags & ~RTF_PCPU;

		memcpy(&rt->rt6i_dst, &ort->rt6i_dst, sizeof(struct rt6key));
#ifdef CONFIG_IPV6_SUBTREES
		memcpy(&rt->rt6i_src, &ort->rt6i_src, sizeof(struct rt6key));
#endif
	}

	dst_release(dst_orig);
	return new ? new : ERR_PTR(-ENOMEM);
}