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
struct TYPE_3__ {int /*<<< orphan*/  nhc_scope; } ;
struct nh_info {int family; int reject_nh; int /*<<< orphan*/  nh_info; TYPE_1__ fib_nhc; struct nh_info* nh_parent; struct net* net; int /*<<< orphan*/  nh_flags; } ;
struct nh_config {int nh_family; int /*<<< orphan*/  nh_ifindex; scalar_t__ nh_blackhole; int /*<<< orphan*/  nh_flags; } ;
struct nexthop {int family; int reject_nh; int /*<<< orphan*/  nh_info; TYPE_1__ fib_nhc; struct nexthop* nh_parent; struct net* net; int /*<<< orphan*/  nh_flags; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {TYPE_2__* loopback_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int ENOMEM ; 
 struct nh_info* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RT_SCOPE_LINK ; 
 int /*<<< orphan*/  kfree (struct nh_info*) ; 
 struct nh_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nh_info* nexthop_alloc () ; 
 int /*<<< orphan*/  nexthop_devhash_add (struct net*,struct nh_info*) ; 
 int nh_create_ipv4 (struct net*,struct nh_info*,struct nh_info*,struct nh_config*,struct netlink_ext_ack*) ; 
 int nh_create_ipv6 (struct net*,struct nh_info*,struct nh_info*,struct nh_config*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct nh_info*) ; 

__attribute__((used)) static struct nexthop *nexthop_create(struct net *net, struct nh_config *cfg,
				      struct netlink_ext_ack *extack)
{
	struct nh_info *nhi;
	struct nexthop *nh;
	int err = 0;

	nh = nexthop_alloc();
	if (!nh)
		return ERR_PTR(-ENOMEM);

	nhi = kzalloc(sizeof(*nhi), GFP_KERNEL);
	if (!nhi) {
		kfree(nh);
		return ERR_PTR(-ENOMEM);
	}

	nh->nh_flags = cfg->nh_flags;
	nh->net = net;

	nhi->nh_parent = nh;
	nhi->family = cfg->nh_family;
	nhi->fib_nhc.nhc_scope = RT_SCOPE_LINK;

	if (cfg->nh_blackhole) {
		nhi->reject_nh = 1;
		cfg->nh_ifindex = net->loopback_dev->ifindex;
	}

	switch (cfg->nh_family) {
	case AF_INET:
		err = nh_create_ipv4(net, nh, nhi, cfg, extack);
		break;
	case AF_INET6:
		err = nh_create_ipv6(net, nh, nhi, cfg, extack);
		break;
	}

	if (err) {
		kfree(nhi);
		kfree(nh);
		return ERR_PTR(err);
	}

	/* add the entry to the device based hash */
	nexthop_devhash_add(net, nhi);

	rcu_assign_pointer(nh->nh_info, nhi);

	return nh;
}