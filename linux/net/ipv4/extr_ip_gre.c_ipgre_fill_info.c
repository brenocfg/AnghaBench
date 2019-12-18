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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int ttl; int tos; int frag_off; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct ip_tunnel_parm {TYPE_1__ iph; int /*<<< orphan*/  o_key; int /*<<< orphan*/  i_key; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  link; int /*<<< orphan*/  o_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; int /*<<< orphan*/  type; } ;
struct ip_tunnel {int erspan_ver; int dir; int ignore_df; scalar_t__ collect_md; TYPE_2__ encap; int /*<<< orphan*/  fwmark; int /*<<< orphan*/  hwid; int /*<<< orphan*/  index; struct ip_tunnel_parm parms; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_GRE_COLLECT_METADATA ; 
 int /*<<< orphan*/  IFLA_GRE_ENCAP_DPORT ; 
 int /*<<< orphan*/  IFLA_GRE_ENCAP_FLAGS ; 
 int /*<<< orphan*/  IFLA_GRE_ENCAP_SPORT ; 
 int /*<<< orphan*/  IFLA_GRE_ENCAP_TYPE ; 
 int /*<<< orphan*/  IFLA_GRE_ERSPAN_DIR ; 
 int /*<<< orphan*/  IFLA_GRE_ERSPAN_HWID ; 
 int /*<<< orphan*/  IFLA_GRE_ERSPAN_INDEX ; 
 int /*<<< orphan*/  IFLA_GRE_ERSPAN_VER ; 
 int /*<<< orphan*/  IFLA_GRE_FWMARK ; 
 int /*<<< orphan*/  IFLA_GRE_IFLAGS ; 
 int /*<<< orphan*/  IFLA_GRE_IGNORE_DF ; 
 int /*<<< orphan*/  IFLA_GRE_IKEY ; 
 int /*<<< orphan*/  IFLA_GRE_LINK ; 
 int /*<<< orphan*/  IFLA_GRE_LOCAL ; 
 int /*<<< orphan*/  IFLA_GRE_OFLAGS ; 
 int /*<<< orphan*/  IFLA_GRE_OKEY ; 
 int /*<<< orphan*/  IFLA_GRE_PMTUDISC ; 
 int /*<<< orphan*/  IFLA_GRE_REMOTE ; 
 int /*<<< orphan*/  IFLA_GRE_TOS ; 
 int /*<<< orphan*/  IFLA_GRE_TTL ; 
 int /*<<< orphan*/  IP_DF ; 
 int /*<<< orphan*/  TUNNEL_KEY ; 
 int /*<<< orphan*/  gre_tnl_flags_to_gre_flags (int /*<<< orphan*/ ) ; 
 int htons (int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device const*) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_in_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipgre_fill_info(struct sk_buff *skb, const struct net_device *dev)
{
	struct ip_tunnel *t = netdev_priv(dev);
	struct ip_tunnel_parm *p = &t->parms;
	__be16 o_flags = p->o_flags;

	if (t->erspan_ver == 1 || t->erspan_ver == 2) {
		if (!t->collect_md)
			o_flags |= TUNNEL_KEY;

		if (nla_put_u8(skb, IFLA_GRE_ERSPAN_VER, t->erspan_ver))
			goto nla_put_failure;

		if (t->erspan_ver == 1) {
			if (nla_put_u32(skb, IFLA_GRE_ERSPAN_INDEX, t->index))
				goto nla_put_failure;
		} else {
			if (nla_put_u8(skb, IFLA_GRE_ERSPAN_DIR, t->dir))
				goto nla_put_failure;
			if (nla_put_u16(skb, IFLA_GRE_ERSPAN_HWID, t->hwid))
				goto nla_put_failure;
		}
	}

	if (nla_put_u32(skb, IFLA_GRE_LINK, p->link) ||
	    nla_put_be16(skb, IFLA_GRE_IFLAGS,
			 gre_tnl_flags_to_gre_flags(p->i_flags)) ||
	    nla_put_be16(skb, IFLA_GRE_OFLAGS,
			 gre_tnl_flags_to_gre_flags(o_flags)) ||
	    nla_put_be32(skb, IFLA_GRE_IKEY, p->i_key) ||
	    nla_put_be32(skb, IFLA_GRE_OKEY, p->o_key) ||
	    nla_put_in_addr(skb, IFLA_GRE_LOCAL, p->iph.saddr) ||
	    nla_put_in_addr(skb, IFLA_GRE_REMOTE, p->iph.daddr) ||
	    nla_put_u8(skb, IFLA_GRE_TTL, p->iph.ttl) ||
	    nla_put_u8(skb, IFLA_GRE_TOS, p->iph.tos) ||
	    nla_put_u8(skb, IFLA_GRE_PMTUDISC,
		       !!(p->iph.frag_off & htons(IP_DF))) ||
	    nla_put_u32(skb, IFLA_GRE_FWMARK, t->fwmark))
		goto nla_put_failure;

	if (nla_put_u16(skb, IFLA_GRE_ENCAP_TYPE,
			t->encap.type) ||
	    nla_put_be16(skb, IFLA_GRE_ENCAP_SPORT,
			 t->encap.sport) ||
	    nla_put_be16(skb, IFLA_GRE_ENCAP_DPORT,
			 t->encap.dport) ||
	    nla_put_u16(skb, IFLA_GRE_ENCAP_FLAGS,
			t->encap.flags))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_GRE_IGNORE_DF, t->ignore_df))
		goto nla_put_failure;

	if (t->collect_md) {
		if (nla_put_flag(skb, IFLA_GRE_COLLECT_METADATA))
			goto nla_put_failure;
	}

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}