#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  output; int /*<<< orphan*/  input; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int plen; int /*<<< orphan*/  addr; } ;
struct rt6_info {TYPE_4__ dst; struct inet6_dev* rt6i_idev; TYPE_1__ rt6i_dst; int /*<<< orphan*/  rt6i_gateway; } ;
struct net_device {int dummy; } ;
struct TYPE_8__ {TYPE_2__* rt6_stats; } ;
struct net {TYPE_3__ ipv6; } ;
struct inet6_dev {int dummy; } ;
struct flowi6 {int /*<<< orphan*/  daddr; } ;
struct dst_entry {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  fib_rt_uncache; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_HOST ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dst_entry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTAX_HOPLIMIT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dst_metric_set (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flowi6_to_flowi (struct flowi6*) ; 
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 struct rt6_info* ip6_dst_alloc (struct net*,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_input ; 
 int /*<<< orphan*/  ip6_output ; 
 int /*<<< orphan*/  rt6_uncached_list_add (struct rt6_info*) ; 
 scalar_t__ unlikely (int) ; 
 struct dst_entry* xfrm_lookup (struct net*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct dst_entry *icmp6_dst_alloc(struct net_device *dev,
				  struct flowi6 *fl6)
{
	struct dst_entry *dst;
	struct rt6_info *rt;
	struct inet6_dev *idev = in6_dev_get(dev);
	struct net *net = dev_net(dev);

	if (unlikely(!idev))
		return ERR_PTR(-ENODEV);

	rt = ip6_dst_alloc(net, dev, 0);
	if (unlikely(!rt)) {
		in6_dev_put(idev);
		dst = ERR_PTR(-ENOMEM);
		goto out;
	}

	rt->dst.flags |= DST_HOST;
	rt->dst.input = ip6_input;
	rt->dst.output  = ip6_output;
	rt->rt6i_gateway  = fl6->daddr;
	rt->rt6i_dst.addr = fl6->daddr;
	rt->rt6i_dst.plen = 128;
	rt->rt6i_idev     = idev;
	dst_metric_set(&rt->dst, RTAX_HOPLIMIT, 0);

	/* Add this dst into uncached_list so that rt6_disable_ip() can
	 * do proper release of the net_device
	 */
	rt6_uncached_list_add(rt);
	atomic_inc(&net->ipv6.rt6_stats->fib_rt_uncache);

	dst = xfrm_lookup(net, &rt->dst, flowi6_to_flowi(fl6), NULL, 0);

out:
	return dst;
}