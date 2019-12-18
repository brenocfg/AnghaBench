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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct ip_tunnel_parm {TYPE_1__ iph; int /*<<< orphan*/  o_key; int /*<<< orphan*/  i_key; int /*<<< orphan*/  link; } ;
struct ip_tunnel {int /*<<< orphan*/  fwmark; struct ip_tunnel_parm parms; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_VTI_FWMARK ; 
 int /*<<< orphan*/  IFLA_VTI_IKEY ; 
 int /*<<< orphan*/  IFLA_VTI_LINK ; 
 int /*<<< orphan*/  IFLA_VTI_LOCAL ; 
 int /*<<< orphan*/  IFLA_VTI_OKEY ; 
 int /*<<< orphan*/  IFLA_VTI_REMOTE ; 
 struct ip_tunnel* netdev_priv (struct net_device const*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_in_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vti_fill_info(struct sk_buff *skb, const struct net_device *dev)
{
	struct ip_tunnel *t = netdev_priv(dev);
	struct ip_tunnel_parm *p = &t->parms;

	if (nla_put_u32(skb, IFLA_VTI_LINK, p->link) ||
	    nla_put_be32(skb, IFLA_VTI_IKEY, p->i_key) ||
	    nla_put_be32(skb, IFLA_VTI_OKEY, p->o_key) ||
	    nla_put_in_addr(skb, IFLA_VTI_LOCAL, p->iph.saddr) ||
	    nla_put_in_addr(skb, IFLA_VTI_REMOTE, p->iph.daddr) ||
	    nla_put_u32(skb, IFLA_VTI_FWMARK, t->fwmark))
		return -EMSGSIZE;

	return 0;
}