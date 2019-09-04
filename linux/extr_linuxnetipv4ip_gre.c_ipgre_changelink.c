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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {TYPE_2__* rtnl_link_ops; } ;
struct ip_tunnel_parm {int /*<<< orphan*/  o_flags; int /*<<< orphan*/  i_flags; } ;
struct ip_tunnel_encap {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  o_flags; int /*<<< orphan*/  i_flags; } ;
struct ip_tunnel {TYPE_1__ parms; int /*<<< orphan*/  fwmark; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 size_t IFLA_MTU ; 
 int ip_tunnel_changelink (struct net_device*,struct nlattr**,struct ip_tunnel_parm*,int /*<<< orphan*/ ) ; 
 int ip_tunnel_encap_setup (struct ip_tunnel*,struct ip_tunnel_encap*) ; 
 int /*<<< orphan*/  ipgre_link_update (struct net_device*,int) ; 
 scalar_t__ ipgre_netlink_encap_parms (struct nlattr**,struct ip_tunnel_encap*) ; 
 int ipgre_netlink_parms (struct net_device*,struct nlattr**,struct nlattr**,struct ip_tunnel_parm*,int /*<<< orphan*/ *) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ipgre_changelink(struct net_device *dev, struct nlattr *tb[],
			    struct nlattr *data[],
			    struct netlink_ext_ack *extack)
{
	struct ip_tunnel *t = netdev_priv(dev);
	struct ip_tunnel_encap ipencap;
	__u32 fwmark = t->fwmark;
	struct ip_tunnel_parm p;
	int err;

	if (ipgre_netlink_encap_parms(data, &ipencap)) {
		err = ip_tunnel_encap_setup(t, &ipencap);

		if (err < 0)
			return err;
	}

	err = ipgre_netlink_parms(dev, data, tb, &p, &fwmark);
	if (err < 0)
		return err;

	err = ip_tunnel_changelink(dev, tb, &p, fwmark);
	if (err < 0)
		return err;

	t->parms.i_flags = p.i_flags;
	t->parms.o_flags = p.o_flags;

	if (strcmp(dev->rtnl_link_ops->kind, "erspan"))
		ipgre_link_update(dev, !tb[IFLA_MTU]);

	return 0;
}