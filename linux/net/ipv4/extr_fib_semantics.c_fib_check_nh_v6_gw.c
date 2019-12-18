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
typedef  int /*<<< orphan*/  u32 ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct fib_nh {int fib_nh_flags; int /*<<< orphan*/  fib_nh_scope; TYPE_2__* fib_nh_dev; int /*<<< orphan*/  fib_nh_oif; int /*<<< orphan*/  fib_nh_gw6; } ;
struct fib6_nh {TYPE_2__* fib_nh_dev; } ;
struct fib6_config {int fc_flags; int /*<<< orphan*/  fc_gateway; int /*<<< orphan*/  fc_ifindex; int /*<<< orphan*/  fc_table; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;
struct TYPE_3__ {int (* fib6_nh_init ) (struct net*,struct fib6_nh*,struct fib6_config*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ;int /*<<< orphan*/  (* fib6_nh_release ) (struct fib6_nh*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RTF_GATEWAY ; 
 int /*<<< orphan*/  RT_SCOPE_LINK ; 
 int /*<<< orphan*/  dev_hold (TYPE_2__*) ; 
 TYPE_1__* ipv6_stub ; 
 int stub1 (struct net*,struct fib6_nh*,struct fib6_config*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  stub2 (struct fib6_nh*) ; 

__attribute__((used)) static int fib_check_nh_v6_gw(struct net *net, struct fib_nh *nh,
			      u32 table, struct netlink_ext_ack *extack)
{
	struct fib6_config cfg = {
		.fc_table = table,
		.fc_flags = nh->fib_nh_flags | RTF_GATEWAY,
		.fc_ifindex = nh->fib_nh_oif,
		.fc_gateway = nh->fib_nh_gw6,
	};
	struct fib6_nh fib6_nh = {};
	int err;

	err = ipv6_stub->fib6_nh_init(net, &fib6_nh, &cfg, GFP_KERNEL, extack);
	if (!err) {
		nh->fib_nh_dev = fib6_nh.fib_nh_dev;
		dev_hold(nh->fib_nh_dev);
		nh->fib_nh_oif = nh->fib_nh_dev->ifindex;
		nh->fib_nh_scope = RT_SCOPE_LINK;

		ipv6_stub->fib6_nh_release(&fib6_nh);
	}

	return err;
}