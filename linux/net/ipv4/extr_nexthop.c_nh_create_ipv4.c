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
typedef  int /*<<< orphan*/  u32 ;
struct fib_nh {int /*<<< orphan*/  fib_nh_scope; int /*<<< orphan*/  nh_common; int /*<<< orphan*/  fib_nh_flags; } ;
struct nh_info {struct fib_nh fib_nh; } ;
struct TYPE_2__ {int /*<<< orphan*/  ipv4; } ;
struct nh_config {int /*<<< orphan*/  dev; int /*<<< orphan*/  nh_encap_type; int /*<<< orphan*/  nh_encap; int /*<<< orphan*/  nh_flags; TYPE_1__ gw; int /*<<< orphan*/  nh_ifindex; } ;
struct nexthop {int /*<<< orphan*/  nh_flags; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct fib_config {int /*<<< orphan*/  fc_encap_type; int /*<<< orphan*/  fc_encap; int /*<<< orphan*/  fc_flags; int /*<<< orphan*/  fc_gw_family; int /*<<< orphan*/  fc_gw4; int /*<<< orphan*/  fc_oif; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int fib_check_nh (struct net*,struct fib_nh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  fib_info_update_nhc_saddr (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fib_nh_init (struct net*,struct fib_nh*,struct fib_config*,int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  fib_nh_release (struct net*,struct fib_nh*) ; 
 int /*<<< orphan*/  l3mdev_fib_table (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nh_create_ipv4(struct net *net, struct nexthop *nh,
			  struct nh_info *nhi, struct nh_config *cfg,
			  struct netlink_ext_ack *extack)
{
	struct fib_nh *fib_nh = &nhi->fib_nh;
	struct fib_config fib_cfg = {
		.fc_oif   = cfg->nh_ifindex,
		.fc_gw4   = cfg->gw.ipv4,
		.fc_gw_family = cfg->gw.ipv4 ? AF_INET : 0,
		.fc_flags = cfg->nh_flags,
		.fc_encap = cfg->nh_encap,
		.fc_encap_type = cfg->nh_encap_type,
	};
	u32 tb_id = l3mdev_fib_table(cfg->dev);
	int err;

	err = fib_nh_init(net, fib_nh, &fib_cfg, 1, extack);
	if (err) {
		fib_nh_release(net, fib_nh);
		goto out;
	}

	/* sets nh_dev if successful */
	err = fib_check_nh(net, fib_nh, tb_id, 0, extack);
	if (!err) {
		nh->nh_flags = fib_nh->fib_nh_flags;
		fib_info_update_nhc_saddr(net, &fib_nh->nh_common,
					  fib_nh->fib_nh_scope);
	} else {
		fib_nh_release(net, fib_nh);
	}
out:
	return err;
}