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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  input; int /*<<< orphan*/  output; int /*<<< orphan*/  tclassid; } ;
struct rtable {int rt_is_input; TYPE_1__ dst; } ;
struct net_device {int dummy; } ;
struct in_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  loopback_dev; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  IN_DEV_CONF_GET (struct in_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ IN_DEV_MFORWARD (struct in_device*) ; 
 int /*<<< orphan*/  NOPOLICY ; 
 unsigned int RTCF_LOCAL ; 
 unsigned int RTCF_MULTICAST ; 
 int /*<<< orphan*/  RTN_MULTICAST ; 
 int /*<<< orphan*/  RT_CACHE_STAT_INC (int /*<<< orphan*/ ) ; 
 struct in_device* __in_dev_get_rcu (struct net_device*) ; 
 TYPE_2__* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  in_slow_mc ; 
 int ip_mc_validate_source (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,struct in_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_mr_input ; 
 int /*<<< orphan*/  ip_rt_bug ; 
 int /*<<< orphan*/  ipv4_is_local_multicast (int /*<<< orphan*/ ) ; 
 struct rtable* rt_dst_alloc (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,TYPE_1__*) ; 

__attribute__((used)) static int ip_route_input_mc(struct sk_buff *skb, __be32 daddr, __be32 saddr,
			     u8 tos, struct net_device *dev, int our)
{
	struct in_device *in_dev = __in_dev_get_rcu(dev);
	unsigned int flags = RTCF_MULTICAST;
	struct rtable *rth;
	u32 itag = 0;
	int err;

	err = ip_mc_validate_source(skb, daddr, saddr, tos, dev, in_dev, &itag);
	if (err)
		return err;

	if (our)
		flags |= RTCF_LOCAL;

	rth = rt_dst_alloc(dev_net(dev)->loopback_dev, flags, RTN_MULTICAST,
			   IN_DEV_CONF_GET(in_dev, NOPOLICY), false, false);
	if (!rth)
		return -ENOBUFS;

#ifdef CONFIG_IP_ROUTE_CLASSID
	rth->dst.tclassid = itag;
#endif
	rth->dst.output = ip_rt_bug;
	rth->rt_is_input= 1;

#ifdef CONFIG_IP_MROUTE
	if (!ipv4_is_local_multicast(daddr) && IN_DEV_MFORWARD(in_dev))
		rth->dst.input = ip_mr_input;
#endif
	RT_CACHE_STAT_INC(in_slow_mc);

	skb_dst_set(skb, &rth->dst);
	return 0;
}