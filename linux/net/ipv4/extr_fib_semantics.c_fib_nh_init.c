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
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fib_num_tclassid_users; } ;
struct net {TYPE_1__ ipv4; } ;
struct fib_nh {scalar_t__ fib_nh_gw_family; int fib_nh_weight; scalar_t__ nh_tclassid; int /*<<< orphan*/  fib_nh_flags; int /*<<< orphan*/  fib_nh_gw6; int /*<<< orphan*/  fib_nh_gw4; int /*<<< orphan*/  fib_nh_oif; int /*<<< orphan*/  nh_common; scalar_t__ fib_nh_family; } ;
struct fib_config {scalar_t__ fc_gw_family; scalar_t__ fc_flow; int /*<<< orphan*/  fc_flags; int /*<<< orphan*/  fc_gw6; int /*<<< orphan*/  fc_gw4; int /*<<< orphan*/  fc_oif; int /*<<< orphan*/  fc_encap_type; int /*<<< orphan*/  fc_encap; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int fib_nh_common_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fib_config*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

int fib_nh_init(struct net *net, struct fib_nh *nh,
		struct fib_config *cfg, int nh_weight,
		struct netlink_ext_ack *extack)
{
	int err;

	nh->fib_nh_family = AF_INET;

	err = fib_nh_common_init(&nh->nh_common, cfg->fc_encap,
				 cfg->fc_encap_type, cfg, GFP_KERNEL, extack);
	if (err)
		return err;

	nh->fib_nh_oif = cfg->fc_oif;
	nh->fib_nh_gw_family = cfg->fc_gw_family;
	if (cfg->fc_gw_family == AF_INET)
		nh->fib_nh_gw4 = cfg->fc_gw4;
	else if (cfg->fc_gw_family == AF_INET6)
		nh->fib_nh_gw6 = cfg->fc_gw6;

	nh->fib_nh_flags = cfg->fc_flags;

#ifdef CONFIG_IP_ROUTE_CLASSID
	nh->nh_tclassid = cfg->fc_flow;
	if (nh->nh_tclassid)
		net->ipv4.fib_num_tclassid_users++;
#endif
#ifdef CONFIG_IP_ROUTE_MULTIPATH
	nh->fib_nh_weight = nh_weight;
#endif
	return 0;
}