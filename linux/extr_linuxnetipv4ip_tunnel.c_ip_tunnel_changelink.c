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
struct nlattr {int dummy; } ;
struct net_device {unsigned int flags; int /*<<< orphan*/  type; } ;
struct net {int dummy; } ;
struct TYPE_2__ {scalar_t__ daddr; } ;
struct ip_tunnel_parm {TYPE_1__ iph; } ;
struct ip_tunnel_net {struct net_device* fb_tunnel_dev; } ;
struct ip_tunnel {struct net_device* dev; int /*<<< orphan*/  ip_tnl_net_id; struct net* net; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int EEXIST ; 
 int EINVAL ; 
 unsigned int IFF_BROADCAST ; 
 unsigned int IFF_POINTOPOINT ; 
 size_t IFLA_MTU ; 
 struct ip_tunnel* ip_tunnel_find (struct ip_tunnel_net*,struct ip_tunnel_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_tunnel_update (struct ip_tunnel_net*,struct ip_tunnel*,struct net_device*,struct ip_tunnel_parm*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_multicast (scalar_t__) ; 
 struct ip_tunnel_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 

int ip_tunnel_changelink(struct net_device *dev, struct nlattr *tb[],
			 struct ip_tunnel_parm *p, __u32 fwmark)
{
	struct ip_tunnel *t;
	struct ip_tunnel *tunnel = netdev_priv(dev);
	struct net *net = tunnel->net;
	struct ip_tunnel_net *itn = net_generic(net, tunnel->ip_tnl_net_id);

	if (dev == itn->fb_tunnel_dev)
		return -EINVAL;

	t = ip_tunnel_find(itn, p, dev->type);

	if (t) {
		if (t->dev != dev)
			return -EEXIST;
	} else {
		t = tunnel;

		if (dev->type != ARPHRD_ETHER) {
			unsigned int nflags = 0;

			if (ipv4_is_multicast(p->iph.daddr))
				nflags = IFF_BROADCAST;
			else if (p->iph.daddr)
				nflags = IFF_POINTOPOINT;

			if ((dev->flags ^ nflags) &
			    (IFF_POINTOPOINT | IFF_BROADCAST))
				return -EINVAL;
		}
	}

	ip_tunnel_update(itn, t, dev, p, !tb[IFLA_MTU], fwmark);
	return 0;
}