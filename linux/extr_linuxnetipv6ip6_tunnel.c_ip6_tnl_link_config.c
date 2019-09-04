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
struct TYPE_8__ {TYPE_3__* dev; } ;
struct rt6_info {TYPE_4__ dst; } ;
struct net_device {scalar_t__ mtu; scalar_t__ hard_header_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  dev_addr; } ;
struct ipv6hdr {int dummy; } ;
struct __ip6_tnl_parm {int flags; int flowinfo; int /*<<< orphan*/  link; int /*<<< orphan*/  laddr; int /*<<< orphan*/  raddr; } ;
struct flowi6 {int flowlabel; int /*<<< orphan*/  flowi6_oif; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_5__ {struct flowi6 ip6; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
struct ip6_tnl {int tun_hlen; int hlen; int encap_hlen; struct __ip6_tnl_parm parms; int /*<<< orphan*/  net; TYPE_2__ fl; struct net_device* dev; } ;
struct in6_addr {int dummy; } ;
struct TYPE_7__ {scalar_t__ mtu; scalar_t__ hard_header_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_POINTOPOINT ; 
 int IP6_TNL_F_CAP_PER_PACKET ; 
 int IP6_TNL_F_CAP_RCV ; 
 int IP6_TNL_F_CAP_XMIT ; 
 int IP6_TNL_F_IGN_ENCAP_LIMIT ; 
 int IP6_TNL_F_USE_ORIG_FLOWLABEL ; 
 int IP6_TNL_F_USE_ORIG_TCLASS ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_MULTICAST ; 
 int IPV6_FLOWLABEL_MASK ; 
 scalar_t__ IPV6_MIN_MTU ; 
 int IPV6_TCLASS_MASK ; 
 int /*<<< orphan*/  ip6_rt_put (struct rt6_info*) ; 
 int ip6_tnl_get_cap (struct ip6_tnl*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct rt6_info* rt6_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ip6_tnl_link_config(struct ip6_tnl *t)
{
	struct net_device *dev = t->dev;
	struct __ip6_tnl_parm *p = &t->parms;
	struct flowi6 *fl6 = &t->fl.u.ip6;
	int t_hlen;

	memcpy(dev->dev_addr, &p->laddr, sizeof(struct in6_addr));
	memcpy(dev->broadcast, &p->raddr, sizeof(struct in6_addr));

	/* Set up flowi template */
	fl6->saddr = p->laddr;
	fl6->daddr = p->raddr;
	fl6->flowi6_oif = p->link;
	fl6->flowlabel = 0;

	if (!(p->flags&IP6_TNL_F_USE_ORIG_TCLASS))
		fl6->flowlabel |= IPV6_TCLASS_MASK & p->flowinfo;
	if (!(p->flags&IP6_TNL_F_USE_ORIG_FLOWLABEL))
		fl6->flowlabel |= IPV6_FLOWLABEL_MASK & p->flowinfo;

	p->flags &= ~(IP6_TNL_F_CAP_XMIT|IP6_TNL_F_CAP_RCV|IP6_TNL_F_CAP_PER_PACKET);
	p->flags |= ip6_tnl_get_cap(t, &p->laddr, &p->raddr);

	if (p->flags&IP6_TNL_F_CAP_XMIT && p->flags&IP6_TNL_F_CAP_RCV)
		dev->flags |= IFF_POINTOPOINT;
	else
		dev->flags &= ~IFF_POINTOPOINT;

	t->tun_hlen = 0;
	t->hlen = t->encap_hlen + t->tun_hlen;
	t_hlen = t->hlen + sizeof(struct ipv6hdr);

	if (p->flags & IP6_TNL_F_CAP_XMIT) {
		int strict = (ipv6_addr_type(&p->raddr) &
			      (IPV6_ADDR_MULTICAST|IPV6_ADDR_LINKLOCAL));

		struct rt6_info *rt = rt6_lookup(t->net,
						 &p->raddr, &p->laddr,
						 p->link, NULL, strict);

		if (!rt)
			return;

		if (rt->dst.dev) {
			dev->hard_header_len = rt->dst.dev->hard_header_len +
				t_hlen;

			dev->mtu = rt->dst.dev->mtu - t_hlen;
			if (!(t->parms.flags & IP6_TNL_F_IGN_ENCAP_LIMIT))
				dev->mtu -= 8;

			if (dev->mtu < IPV6_MIN_MTU)
				dev->mtu = IPV6_MIN_MTU;
		}
		ip6_rt_put(rt);
	}
}