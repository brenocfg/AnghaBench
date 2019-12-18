#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ s_net; scalar_t__ s_node; } ;
struct sockaddr_at {scalar_t__ sat_family; TYPE_3__ sat_addr; } ;
struct rtentry {int rt_flags; int /*<<< orphan*/  rt_gateway; int /*<<< orphan*/  rt_dst; } ;
struct net_device {int dummy; } ;
struct atalk_route {int flags; TYPE_3__ gateway; struct net_device* dev; TYPE_3__ target; struct atalk_route* next; } ;
struct TYPE_5__ {scalar_t__ s_net; scalar_t__ s_node; } ;
struct TYPE_4__ {scalar_t__ nr_firstnet; scalar_t__ nr_lastnet; } ;
struct atalk_iface {struct net_device* dev; TYPE_2__ address; TYPE_1__ nets; struct atalk_iface* next; } ;

/* Variables and functions */
 scalar_t__ AF_APPLETALK ; 
 int EINVAL ; 
 int ENETUNREACH ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int RTF_HOST ; 
 struct atalk_iface* atalk_interfaces ; 
 int /*<<< orphan*/  atalk_interfaces_lock ; 
 struct atalk_route* atalk_routes ; 
 int /*<<< orphan*/  atalk_routes_lock ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct atalk_route* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (scalar_t__) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atrtr_create(struct rtentry *r, struct net_device *devhint)
{
	struct sockaddr_at *ta = (struct sockaddr_at *)&r->rt_dst;
	struct sockaddr_at *ga = (struct sockaddr_at *)&r->rt_gateway;
	struct atalk_route *rt;
	struct atalk_iface *iface, *riface;
	int retval = -EINVAL;

	/*
	 * Fixme: Raise/Lower a routing change semaphore for these
	 * operations.
	 */

	/* Validate the request */
	if (ta->sat_family != AF_APPLETALK ||
	    (!devhint && ga->sat_family != AF_APPLETALK))
		goto out;

	/* Now walk the routing table and make our decisions */
	write_lock_bh(&atalk_routes_lock);
	for (rt = atalk_routes; rt; rt = rt->next) {
		if (r->rt_flags != rt->flags)
			continue;

		if (ta->sat_addr.s_net == rt->target.s_net) {
			if (!(rt->flags & RTF_HOST))
				break;
			if (ta->sat_addr.s_node == rt->target.s_node)
				break;
		}
	}

	if (!devhint) {
		riface = NULL;

		read_lock_bh(&atalk_interfaces_lock);
		for (iface = atalk_interfaces; iface; iface = iface->next) {
			if (!riface &&
			    ntohs(ga->sat_addr.s_net) >=
					ntohs(iface->nets.nr_firstnet) &&
			    ntohs(ga->sat_addr.s_net) <=
					ntohs(iface->nets.nr_lastnet))
				riface = iface;

			if (ga->sat_addr.s_net == iface->address.s_net &&
			    ga->sat_addr.s_node == iface->address.s_node)
				riface = iface;
		}
		read_unlock_bh(&atalk_interfaces_lock);

		retval = -ENETUNREACH;
		if (!riface)
			goto out_unlock;

		devhint = riface->dev;
	}

	if (!rt) {
		rt = kzalloc(sizeof(*rt), GFP_ATOMIC);

		retval = -ENOBUFS;
		if (!rt)
			goto out_unlock;

		rt->next = atalk_routes;
		atalk_routes = rt;
	}

	/* Fill in the routing entry */
	rt->target  = ta->sat_addr;
	dev_hold(devhint);
	rt->dev     = devhint;
	rt->flags   = r->rt_flags;
	rt->gateway = ga->sat_addr;

	retval = 0;
out_unlock:
	write_unlock_bh(&atalk_routes_lock);
out:
	return retval;
}