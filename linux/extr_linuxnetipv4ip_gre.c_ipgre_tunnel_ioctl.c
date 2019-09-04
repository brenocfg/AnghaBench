#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {TYPE_3__* rtnl_link_ops; } ;
struct TYPE_5__ {int version; scalar_t__ protocol; int ihl; int frag_off; } ;
struct ip_tunnel_parm {int i_flags; int o_flags; TYPE_1__ iph; } ;
struct TYPE_6__ {int i_flags; int o_flags; } ;
struct ip_tunnel {TYPE_2__ parms; } ;
struct TYPE_8__ {int /*<<< orphan*/  ifru_data; } ;
struct ifreq {TYPE_4__ ifr_ifru; } ;
typedef  int /*<<< orphan*/  p ;
struct TYPE_7__ {int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int GRE_ROUTING ; 
 int GRE_VERSION ; 
 scalar_t__ IPPROTO_GRE ; 
 int /*<<< orphan*/  IP_DF ; 
 int SIOCADDTUNNEL ; 
 int SIOCCHGTUNNEL ; 
 scalar_t__ copy_from_user (struct ip_tunnel_parm*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct ip_tunnel_parm*,int) ; 
 void* gre_flags_to_tnl_flags (int) ; 
 void* gre_tnl_flags_to_gre_flags (int) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int ip_tunnel_ioctl (struct net_device*,struct ip_tunnel_parm*,int) ; 
 int /*<<< orphan*/  ipgre_link_update (struct net_device*,int) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ipgre_tunnel_ioctl(struct net_device *dev,
			      struct ifreq *ifr, int cmd)
{
	struct ip_tunnel_parm p;
	int err;

	if (copy_from_user(&p, ifr->ifr_ifru.ifru_data, sizeof(p)))
		return -EFAULT;

	if (cmd == SIOCADDTUNNEL || cmd == SIOCCHGTUNNEL) {
		if (p.iph.version != 4 || p.iph.protocol != IPPROTO_GRE ||
		    p.iph.ihl != 5 || (p.iph.frag_off & htons(~IP_DF)) ||
		    ((p.i_flags | p.o_flags) & (GRE_VERSION | GRE_ROUTING)))
			return -EINVAL;
	}

	p.i_flags = gre_flags_to_tnl_flags(p.i_flags);
	p.o_flags = gre_flags_to_tnl_flags(p.o_flags);

	err = ip_tunnel_ioctl(dev, &p, cmd);
	if (err)
		return err;

	if (cmd == SIOCCHGTUNNEL) {
		struct ip_tunnel *t = netdev_priv(dev);

		t->parms.i_flags = p.i_flags;
		t->parms.o_flags = p.o_flags;

		if (strcmp(dev->rtnl_link_ops->kind, "erspan"))
			ipgre_link_update(dev, true);
	}

	p.i_flags = gre_tnl_flags_to_gre_flags(p.i_flags);
	p.o_flags = gre_tnl_flags_to_gre_flags(p.o_flags);

	if (copy_to_user(ifr->ifr_ifru.ifru_data, &p, sizeof(p)))
		return -EFAULT;

	return 0;
}