#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {scalar_t__ type; int mtu; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  frag_off; int /*<<< orphan*/  tos; int /*<<< orphan*/  ttl; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct ip_tunnel_parm {scalar_t__ link; TYPE_2__ iph; int /*<<< orphan*/  o_key; int /*<<< orphan*/  i_key; } ;
struct ip_tunnel_net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  frag_off; int /*<<< orphan*/  tos; int /*<<< orphan*/  ttl; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_6__ {scalar_t__ link; TYPE_1__ iph; int /*<<< orphan*/  o_key; int /*<<< orphan*/  i_key; } ;
struct ip_tunnel {scalar_t__ fwmark; int /*<<< orphan*/  dst_cache; TYPE_3__ parms; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  dst_cache_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_tunnel_add (struct ip_tunnel_net*,struct ip_tunnel*) ; 
 int ip_tunnel_bind_dev (struct net_device*) ; 
 int /*<<< orphan*/  ip_tunnel_del (struct ip_tunnel_net*,struct ip_tunnel*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_state_change (struct net_device*) ; 

__attribute__((used)) static void ip_tunnel_update(struct ip_tunnel_net *itn,
			     struct ip_tunnel *t,
			     struct net_device *dev,
			     struct ip_tunnel_parm *p,
			     bool set_mtu,
			     __u32 fwmark)
{
	ip_tunnel_del(itn, t);
	t->parms.iph.saddr = p->iph.saddr;
	t->parms.iph.daddr = p->iph.daddr;
	t->parms.i_key = p->i_key;
	t->parms.o_key = p->o_key;
	if (dev->type != ARPHRD_ETHER) {
		memcpy(dev->dev_addr, &p->iph.saddr, 4);
		memcpy(dev->broadcast, &p->iph.daddr, 4);
	}
	ip_tunnel_add(itn, t);

	t->parms.iph.ttl = p->iph.ttl;
	t->parms.iph.tos = p->iph.tos;
	t->parms.iph.frag_off = p->iph.frag_off;

	if (t->parms.link != p->link || t->fwmark != fwmark) {
		int mtu;

		t->parms.link = p->link;
		t->fwmark = fwmark;
		mtu = ip_tunnel_bind_dev(dev);
		if (set_mtu)
			dev->mtu = mtu;
	}
	dst_cache_reset(&t->dst_cache);
	netdev_state_change(dev);
}