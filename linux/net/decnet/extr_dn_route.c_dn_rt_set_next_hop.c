#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct net_device {scalar_t__ mtu; } ;
struct neighbour {int dummy; } ;
struct TYPE_7__ {struct net_device* dev; } ;
struct dn_route {TYPE_1__ dst; struct neighbour* n; scalar_t__ rt_gateway; int /*<<< orphan*/  rt_type; } ;
struct dn_fib_res {int /*<<< orphan*/  type; struct dn_fib_info* fi; } ;
struct dn_fib_info {int /*<<< orphan*/  fib_metrics; } ;
struct TYPE_8__ {scalar_t__ nh_scope; } ;

/* Variables and functions */
 scalar_t__ DN_FIB_RES_GW (struct dn_fib_res) ; 
 TYPE_6__ DN_FIB_RES_NH (struct dn_fib_res) ; 
 scalar_t__ IS_ERR (struct neighbour*) ; 
 int PTR_ERR (struct neighbour*) ; 
 int /*<<< orphan*/  RTAX_ADVMSS ; 
 int /*<<< orphan*/  RTAX_MTU ; 
 scalar_t__ RT_SCOPE_LINK ; 
 struct neighbour* __neigh_lookup_errno (int /*<<< orphan*/ *,scalar_t__*,struct net_device*) ; 
 unsigned int dn_mss_from_pmtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_neigh_table ; 
 int /*<<< orphan*/  dst_init_metrics (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dst_metric (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned int dst_metric_raw (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_metric_set (TYPE_1__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dst_mtu (TYPE_1__*) ; 

__attribute__((used)) static int dn_rt_set_next_hop(struct dn_route *rt, struct dn_fib_res *res)
{
	struct dn_fib_info *fi = res->fi;
	struct net_device *dev = rt->dst.dev;
	unsigned int mss_metric;
	struct neighbour *n;

	if (fi) {
		if (DN_FIB_RES_GW(*res) &&
		    DN_FIB_RES_NH(*res).nh_scope == RT_SCOPE_LINK)
			rt->rt_gateway = DN_FIB_RES_GW(*res);
		dst_init_metrics(&rt->dst, fi->fib_metrics, true);
	}
	rt->rt_type = res->type;

	if (dev != NULL && rt->n == NULL) {
		n = __neigh_lookup_errno(&dn_neigh_table, &rt->rt_gateway, dev);
		if (IS_ERR(n))
			return PTR_ERR(n);
		rt->n = n;
	}

	if (dst_metric(&rt->dst, RTAX_MTU) > rt->dst.dev->mtu)
		dst_metric_set(&rt->dst, RTAX_MTU, rt->dst.dev->mtu);
	mss_metric = dst_metric_raw(&rt->dst, RTAX_ADVMSS);
	if (mss_metric) {
		unsigned int mss = dn_mss_from_pmtu(dev, dst_mtu(&rt->dst));
		if (mss_metric > mss)
			dst_metric_set(&rt->dst, RTAX_ADVMSS, mss);
	}
	return 0;
}