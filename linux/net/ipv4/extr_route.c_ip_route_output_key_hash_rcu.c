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
struct sk_buff {int dummy; } ;
struct rtable {int dummy; } ;
struct net_device {int ifindex; int flags; } ;
struct net {struct net_device* loopback_dev; } ;
struct flowi4 {int flowi4_oif; int flowi4_flags; scalar_t__ flowi4_proto; void* daddr; void* saddr; int /*<<< orphan*/  flowi4_scope; } ;
struct fib_result {scalar_t__ type; TYPE_1__* fi; int /*<<< orphan*/ * table; } ;
struct TYPE_2__ {void* fib_prefsrc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENETUNREACH ; 
 int ENODEV ; 
 struct rtable* ERR_PTR (int) ; 
 struct net_device* FIB_RES_DEV (struct fib_result) ; 
 int FIB_RES_OIF (struct fib_result) ; 
 int FLOWI_FLAG_ANYSRC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 scalar_t__ IPPROTO_IGMP ; 
 int LOOPBACK_IFINDEX ; 
 unsigned int RTCF_LOCAL ; 
 scalar_t__ RTN_LOCAL ; 
 scalar_t__ RTN_UNICAST ; 
 int /*<<< orphan*/  RT_SCOPE_HOST ; 
 int /*<<< orphan*/  RT_SCOPE_LINK ; 
 int /*<<< orphan*/  __in_dev_get_rcu (struct net_device*) ; 
 struct net_device* __ip_dev_find (struct net*,void*,int) ; 
 struct rtable* __mkroute_output (struct fib_result*,struct flowi4*,int,struct net_device*,unsigned int) ; 
 struct net_device* dev_get_by_index_rcu (struct net*,int) ; 
 int fib_lookup (struct net*,struct flowi4*,struct fib_result*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib_select_path (struct net*,struct fib_result*,struct flowi4*,struct sk_buff const*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 void* inet_select_addr (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_lbcast (void*) ; 
 scalar_t__ ipv4_is_local_multicast (void*) ; 
 scalar_t__ ipv4_is_multicast (void*) ; 
 scalar_t__ ipv4_is_zeronet (void*) ; 
 scalar_t__ l3mdev_master_dev_rcu (struct net_device*) ; 
 int /*<<< orphan*/  netif_index_is_l3_master (struct net*,int) ; 

struct rtable *ip_route_output_key_hash_rcu(struct net *net, struct flowi4 *fl4,
					    struct fib_result *res,
					    const struct sk_buff *skb)
{
	struct net_device *dev_out = NULL;
	int orig_oif = fl4->flowi4_oif;
	unsigned int flags = 0;
	struct rtable *rth;
	int err;

	if (fl4->saddr) {
		if (ipv4_is_multicast(fl4->saddr) ||
		    ipv4_is_lbcast(fl4->saddr) ||
		    ipv4_is_zeronet(fl4->saddr)) {
			rth = ERR_PTR(-EINVAL);
			goto out;
		}

		rth = ERR_PTR(-ENETUNREACH);

		/* I removed check for oif == dev_out->oif here.
		   It was wrong for two reasons:
		   1. ip_dev_find(net, saddr) can return wrong iface, if saddr
		      is assigned to multiple interfaces.
		   2. Moreover, we are allowed to send packets with saddr
		      of another iface. --ANK
		 */

		if (fl4->flowi4_oif == 0 &&
		    (ipv4_is_multicast(fl4->daddr) ||
		     ipv4_is_lbcast(fl4->daddr))) {
			/* It is equivalent to inet_addr_type(saddr) == RTN_LOCAL */
			dev_out = __ip_dev_find(net, fl4->saddr, false);
			if (!dev_out)
				goto out;

			/* Special hack: user can direct multicasts
			   and limited broadcast via necessary interface
			   without fiddling with IP_MULTICAST_IF or IP_PKTINFO.
			   This hack is not just for fun, it allows
			   vic,vat and friends to work.
			   They bind socket to loopback, set ttl to zero
			   and expect that it will work.
			   From the viewpoint of routing cache they are broken,
			   because we are not allowed to build multicast path
			   with loopback source addr (look, routing cache
			   cannot know, that ttl is zero, so that packet
			   will not leave this host and route is valid).
			   Luckily, this hack is good workaround.
			 */

			fl4->flowi4_oif = dev_out->ifindex;
			goto make_route;
		}

		if (!(fl4->flowi4_flags & FLOWI_FLAG_ANYSRC)) {
			/* It is equivalent to inet_addr_type(saddr) == RTN_LOCAL */
			if (!__ip_dev_find(net, fl4->saddr, false))
				goto out;
		}
	}


	if (fl4->flowi4_oif) {
		dev_out = dev_get_by_index_rcu(net, fl4->flowi4_oif);
		rth = ERR_PTR(-ENODEV);
		if (!dev_out)
			goto out;

		/* RACE: Check return value of inet_select_addr instead. */
		if (!(dev_out->flags & IFF_UP) || !__in_dev_get_rcu(dev_out)) {
			rth = ERR_PTR(-ENETUNREACH);
			goto out;
		}
		if (ipv4_is_local_multicast(fl4->daddr) ||
		    ipv4_is_lbcast(fl4->daddr) ||
		    fl4->flowi4_proto == IPPROTO_IGMP) {
			if (!fl4->saddr)
				fl4->saddr = inet_select_addr(dev_out, 0,
							      RT_SCOPE_LINK);
			goto make_route;
		}
		if (!fl4->saddr) {
			if (ipv4_is_multicast(fl4->daddr))
				fl4->saddr = inet_select_addr(dev_out, 0,
							      fl4->flowi4_scope);
			else if (!fl4->daddr)
				fl4->saddr = inet_select_addr(dev_out, 0,
							      RT_SCOPE_HOST);
		}
	}

	if (!fl4->daddr) {
		fl4->daddr = fl4->saddr;
		if (!fl4->daddr)
			fl4->daddr = fl4->saddr = htonl(INADDR_LOOPBACK);
		dev_out = net->loopback_dev;
		fl4->flowi4_oif = LOOPBACK_IFINDEX;
		res->type = RTN_LOCAL;
		flags |= RTCF_LOCAL;
		goto make_route;
	}

	err = fib_lookup(net, fl4, res, 0);
	if (err) {
		res->fi = NULL;
		res->table = NULL;
		if (fl4->flowi4_oif &&
		    (ipv4_is_multicast(fl4->daddr) ||
		    !netif_index_is_l3_master(net, fl4->flowi4_oif))) {
			/* Apparently, routing tables are wrong. Assume,
			   that the destination is on link.

			   WHY? DW.
			   Because we are allowed to send to iface
			   even if it has NO routes and NO assigned
			   addresses. When oif is specified, routing
			   tables are looked up with only one purpose:
			   to catch if destination is gatewayed, rather than
			   direct. Moreover, if MSG_DONTROUTE is set,
			   we send packet, ignoring both routing tables
			   and ifaddr state. --ANK


			   We could make it even if oif is unknown,
			   likely IPv6, but we do not.
			 */

			if (fl4->saddr == 0)
				fl4->saddr = inet_select_addr(dev_out, 0,
							      RT_SCOPE_LINK);
			res->type = RTN_UNICAST;
			goto make_route;
		}
		rth = ERR_PTR(err);
		goto out;
	}

	if (res->type == RTN_LOCAL) {
		if (!fl4->saddr) {
			if (res->fi->fib_prefsrc)
				fl4->saddr = res->fi->fib_prefsrc;
			else
				fl4->saddr = fl4->daddr;
		}

		/* L3 master device is the loopback for that domain */
		dev_out = l3mdev_master_dev_rcu(FIB_RES_DEV(*res)) ? :
			net->loopback_dev;

		/* make sure orig_oif points to fib result device even
		 * though packet rx/tx happens over loopback or l3mdev
		 */
		orig_oif = FIB_RES_OIF(*res);

		fl4->flowi4_oif = dev_out->ifindex;
		flags |= RTCF_LOCAL;
		goto make_route;
	}

	fib_select_path(net, res, fl4, skb);

	dev_out = FIB_RES_DEV(*res);
	fl4->flowi4_oif = dev_out->ifindex;


make_route:
	rth = __mkroute_output(res, fl4, orig_oif, dev_out, flags);

out:
	return rth;
}