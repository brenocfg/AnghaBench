#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ protocol; } ;
struct TYPE_7__ {int /*<<< orphan*/  input; } ;
struct rtable {int rt_is_input; TYPE_2__ dst; } ;
struct net_device {int dummy; } ;
struct in_device {int /*<<< orphan*/  dev; } ;
struct fib_result {int /*<<< orphan*/  type; int /*<<< orphan*/  fi; } ;
struct fib_nh_exception {int /*<<< orphan*/  fnhe_rth_input; } ;
struct TYPE_6__ {int /*<<< orphan*/  ipv4; } ;
struct fib_nh_common {scalar_t__ nhc_gw_family; int /*<<< orphan*/  nhc_rth_input; TYPE_1__ nhc_gw; struct net_device* nhc_dev; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 struct fib_nh_common* FIB_RES_NHC (struct fib_result const) ; 
 int /*<<< orphan*/  FIB_RES_OIF (struct fib_result const) ; 
 int /*<<< orphan*/  IN_DEV_CONF_GET (struct in_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ IN_DEV_PROXY_ARP_PVLAN (struct in_device*) ; 
 scalar_t__ IN_DEV_SHARED_MEDIA (struct in_device*) ; 
 scalar_t__ IN_DEV_TX_REDIRECTS (struct in_device*) ; 
 TYPE_5__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPSKB_DOREDIRECT ; 
 int /*<<< orphan*/  NOPOLICY ; 
 int /*<<< orphan*/  NOXFRM ; 
 int /*<<< orphan*/  RT_CACHE_STAT_INC (int /*<<< orphan*/ ) ; 
 struct in_device* __in_dev_get_rcu (struct net_device*) ; 
 int fib_validate_source (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in_device*,scalar_t__*) ; 
 struct fib_nh_exception* find_exception (struct fib_nh_common*,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_slow_tot ; 
 scalar_t__ inet_addr_onlink (struct in_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_forward ; 
 int /*<<< orphan*/  ip_handle_martian_source (int /*<<< orphan*/ ,struct in_device*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwtunnel_set_redirect (TYPE_2__*) ; 
 int /*<<< orphan*/  net_crit_ratelimited (char*) ; 
 struct rtable* rcu_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ rt_cache_valid (struct rtable*) ; 
 struct rtable* rt_dst_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt_set_nexthop (struct rtable*,int /*<<< orphan*/ ,struct fib_result const*,struct fib_nh_exception*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  skb_dst_set_noref (struct sk_buff*,TYPE_2__*) ; 

__attribute__((used)) static int __mkroute_input(struct sk_buff *skb,
			   const struct fib_result *res,
			   struct in_device *in_dev,
			   __be32 daddr, __be32 saddr, u32 tos)
{
	struct fib_nh_common *nhc = FIB_RES_NHC(*res);
	struct net_device *dev = nhc->nhc_dev;
	struct fib_nh_exception *fnhe;
	struct rtable *rth;
	int err;
	struct in_device *out_dev;
	bool do_cache;
	u32 itag = 0;

	/* get a working reference to the output device */
	out_dev = __in_dev_get_rcu(dev);
	if (!out_dev) {
		net_crit_ratelimited("Bug in ip_route_input_slow(). Please report.\n");
		return -EINVAL;
	}

	err = fib_validate_source(skb, saddr, daddr, tos, FIB_RES_OIF(*res),
				  in_dev->dev, in_dev, &itag);
	if (err < 0) {
		ip_handle_martian_source(in_dev->dev, in_dev, skb, daddr,
					 saddr);

		goto cleanup;
	}

	do_cache = res->fi && !itag;
	if (out_dev == in_dev && err && IN_DEV_TX_REDIRECTS(out_dev) &&
	    skb->protocol == htons(ETH_P_IP)) {
		__be32 gw;

		gw = nhc->nhc_gw_family == AF_INET ? nhc->nhc_gw.ipv4 : 0;
		if (IN_DEV_SHARED_MEDIA(out_dev) ||
		    inet_addr_onlink(out_dev, saddr, gw))
			IPCB(skb)->flags |= IPSKB_DOREDIRECT;
	}

	if (skb->protocol != htons(ETH_P_IP)) {
		/* Not IP (i.e. ARP). Do not create route, if it is
		 * invalid for proxy arp. DNAT routes are always valid.
		 *
		 * Proxy arp feature have been extended to allow, ARP
		 * replies back to the same interface, to support
		 * Private VLAN switch technologies. See arp.c.
		 */
		if (out_dev == in_dev &&
		    IN_DEV_PROXY_ARP_PVLAN(in_dev) == 0) {
			err = -EINVAL;
			goto cleanup;
		}
	}

	fnhe = find_exception(nhc, daddr);
	if (do_cache) {
		if (fnhe)
			rth = rcu_dereference(fnhe->fnhe_rth_input);
		else
			rth = rcu_dereference(nhc->nhc_rth_input);
		if (rt_cache_valid(rth)) {
			skb_dst_set_noref(skb, &rth->dst);
			goto out;
		}
	}

	rth = rt_dst_alloc(out_dev->dev, 0, res->type,
			   IN_DEV_CONF_GET(in_dev, NOPOLICY),
			   IN_DEV_CONF_GET(out_dev, NOXFRM), do_cache);
	if (!rth) {
		err = -ENOBUFS;
		goto cleanup;
	}

	rth->rt_is_input = 1;
	RT_CACHE_STAT_INC(in_slow_tot);

	rth->dst.input = ip_forward;

	rt_set_nexthop(rth, daddr, res, fnhe, res->fi, res->type, itag,
		       do_cache);
	lwtunnel_set_redirect(&rth->dst);
	skb_dst_set(skb, &rth->dst);
out:
	err = 0;
 cleanup:
	return err;
}