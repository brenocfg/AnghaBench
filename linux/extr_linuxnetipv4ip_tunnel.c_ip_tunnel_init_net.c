#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rtnl_link_ops {int dummy; } ;
struct net {int dummy; } ;
struct ip_tunnel_parm {int /*<<< orphan*/  name; } ;
struct ip_tunnel_net {TYPE_1__* fb_tunnel_dev; int /*<<< orphan*/  type; int /*<<< orphan*/ * tunnels; struct rtnl_link_ops* rtnl_link_ops; } ;
typedef  int /*<<< orphan*/  parms ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/  mtu; int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int IP_TNL_HASH_SIZE ; 
 int /*<<< orphan*/  IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  NETIF_F_NETNS_LOCAL ; 
 int PTR_ERR_OR_ZERO (TYPE_1__*) ; 
 TYPE_1__* __ip_tunnel_create (struct net*,struct rtnl_link_ops*,struct ip_tunnel_parm*) ; 
 struct net init_net ; 
 int /*<<< orphan*/  ip_tunnel_add (struct ip_tunnel_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_tunnel_bind_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct ip_tunnel_parm*,int /*<<< orphan*/ ,int) ; 
 struct ip_tunnel_net* net_generic (struct net*,unsigned int) ; 
 int /*<<< orphan*/  net_has_fallback_tunnels (struct net*) ; 
 int /*<<< orphan*/  netdev_priv (TYPE_1__*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int ip_tunnel_init_net(struct net *net, unsigned int ip_tnl_net_id,
				  struct rtnl_link_ops *ops, char *devname)
{
	struct ip_tunnel_net *itn = net_generic(net, ip_tnl_net_id);
	struct ip_tunnel_parm parms;
	unsigned int i;

	itn->rtnl_link_ops = ops;
	for (i = 0; i < IP_TNL_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&itn->tunnels[i]);

	if (!ops || !net_has_fallback_tunnels(net)) {
		struct ip_tunnel_net *it_init_net;

		it_init_net = net_generic(&init_net, ip_tnl_net_id);
		itn->type = it_init_net->type;
		itn->fb_tunnel_dev = NULL;
		return 0;
	}

	memset(&parms, 0, sizeof(parms));
	if (devname)
		strlcpy(parms.name, devname, IFNAMSIZ);

	rtnl_lock();
	itn->fb_tunnel_dev = __ip_tunnel_create(net, ops, &parms);
	/* FB netdevice is special: we have one, and only one per netns.
	 * Allowing to move it to another netns is clearly unsafe.
	 */
	if (!IS_ERR(itn->fb_tunnel_dev)) {
		itn->fb_tunnel_dev->features |= NETIF_F_NETNS_LOCAL;
		itn->fb_tunnel_dev->mtu = ip_tunnel_bind_dev(itn->fb_tunnel_dev);
		ip_tunnel_add(itn, netdev_priv(itn->fb_tunnel_dev));
		itn->type = itn->fb_tunnel_dev->type;
	}
	rtnl_unlock();

	return PTR_ERR_OR_ZERO(itn->fb_tunnel_dev);
}