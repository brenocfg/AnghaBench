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
struct fib6_nh {int /*<<< orphan*/  fib_nh_flags; } ;
struct nh_info {struct fib6_nh fib6_nh; } ;
struct TYPE_3__ {int /*<<< orphan*/  ipv6; } ;
struct nh_config {TYPE_1__ gw; int /*<<< orphan*/  nh_encap_type; int /*<<< orphan*/  nh_encap; int /*<<< orphan*/  nh_flags; int /*<<< orphan*/  nh_ifindex; int /*<<< orphan*/  dev; } ;
struct nexthop {int /*<<< orphan*/  nh_flags; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct fib6_config {int /*<<< orphan*/  fc_flags; int /*<<< orphan*/  fc_encap_type; int /*<<< orphan*/  fc_encap; int /*<<< orphan*/  fc_gateway; int /*<<< orphan*/  fc_ifindex; int /*<<< orphan*/  fc_table; } ;
struct TYPE_4__ {int (* fib6_nh_init ) (struct net*,struct fib6_nh*,struct fib6_config*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ;int /*<<< orphan*/  (* fib6_nh_release ) (struct fib6_nh*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RTF_GATEWAY ; 
 int /*<<< orphan*/  ipv6_addr_any (int /*<<< orphan*/ *) ; 
 TYPE_2__* ipv6_stub ; 
 int /*<<< orphan*/  l3mdev_fib_table (int /*<<< orphan*/ ) ; 
 int stub1 (struct net*,struct fib6_nh*,struct fib6_config*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  stub2 (struct fib6_nh*) ; 

__attribute__((used)) static int nh_create_ipv6(struct net *net,  struct nexthop *nh,
			  struct nh_info *nhi, struct nh_config *cfg,
			  struct netlink_ext_ack *extack)
{
	struct fib6_nh *fib6_nh = &nhi->fib6_nh;
	struct fib6_config fib6_cfg = {
		.fc_table = l3mdev_fib_table(cfg->dev),
		.fc_ifindex = cfg->nh_ifindex,
		.fc_gateway = cfg->gw.ipv6,
		.fc_flags = cfg->nh_flags,
		.fc_encap = cfg->nh_encap,
		.fc_encap_type = cfg->nh_encap_type,
	};
	int err;

	if (!ipv6_addr_any(&cfg->gw.ipv6))
		fib6_cfg.fc_flags |= RTF_GATEWAY;

	/* sets nh_dev if successful */
	err = ipv6_stub->fib6_nh_init(net, fib6_nh, &fib6_cfg, GFP_KERNEL,
				      extack);
	if (err)
		ipv6_stub->fib6_nh_release(fib6_nh);
	else
		nh->nh_flags = fib6_nh->fib_nh_flags;

	return err;
}