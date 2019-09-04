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
struct net_device {scalar_t__ type; } ;
struct TYPE_2__ {int frag_off; void* tos; void* ttl; void* daddr; void* saddr; int /*<<< orphan*/  protocol; } ;
struct ip_tunnel_parm {TYPE_1__ iph; void* o_key; void* i_key; void* o_flags; void* i_flags; void* link; } ;
struct ip_tunnel {int ignore_df; int collect_md; int erspan_ver; int index; int dir; int hwid; } ;
typedef  void* __u32 ;

/* Variables and functions */
 scalar_t__ ARPHRD_IPGRE ; 
 scalar_t__ ARPHRD_NONE ; 
 int DIR_MASK ; 
 int DIR_OFFSET ; 
 int EINVAL ; 
 int HWID_MASK ; 
 int HWID_OFFSET ; 
 size_t IFLA_GRE_COLLECT_METADATA ; 
 size_t IFLA_GRE_ERSPAN_DIR ; 
 size_t IFLA_GRE_ERSPAN_HWID ; 
 size_t IFLA_GRE_ERSPAN_INDEX ; 
 size_t IFLA_GRE_ERSPAN_VER ; 
 size_t IFLA_GRE_FWMARK ; 
 size_t IFLA_GRE_IFLAGS ; 
 size_t IFLA_GRE_IGNORE_DF ; 
 size_t IFLA_GRE_IKEY ; 
 size_t IFLA_GRE_LINK ; 
 size_t IFLA_GRE_LOCAL ; 
 size_t IFLA_GRE_OFLAGS ; 
 size_t IFLA_GRE_OKEY ; 
 size_t IFLA_GRE_PMTUDISC ; 
 size_t IFLA_GRE_REMOTE ; 
 size_t IFLA_GRE_TOS ; 
 size_t IFLA_GRE_TTL ; 
 int INDEX_MASK ; 
 int /*<<< orphan*/  IPPROTO_GRE ; 
 int /*<<< orphan*/  IP_DF ; 
 void* gre_flags_to_tnl_flags (int /*<<< orphan*/ ) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ip_tunnel_parm*,int /*<<< orphan*/ ,int) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr*) ; 
 void* nla_get_be32 (struct nlattr*) ; 
 void* nla_get_in_addr (struct nlattr*) ; 
 int nla_get_u16 (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 void* nla_get_u8 (struct nlattr*) ; 

__attribute__((used)) static int ipgre_netlink_parms(struct net_device *dev,
				struct nlattr *data[],
				struct nlattr *tb[],
				struct ip_tunnel_parm *parms,
				__u32 *fwmark)
{
	struct ip_tunnel *t = netdev_priv(dev);

	memset(parms, 0, sizeof(*parms));

	parms->iph.protocol = IPPROTO_GRE;

	if (!data)
		return 0;

	if (data[IFLA_GRE_LINK])
		parms->link = nla_get_u32(data[IFLA_GRE_LINK]);

	if (data[IFLA_GRE_IFLAGS])
		parms->i_flags = gre_flags_to_tnl_flags(nla_get_be16(data[IFLA_GRE_IFLAGS]));

	if (data[IFLA_GRE_OFLAGS])
		parms->o_flags = gre_flags_to_tnl_flags(nla_get_be16(data[IFLA_GRE_OFLAGS]));

	if (data[IFLA_GRE_IKEY])
		parms->i_key = nla_get_be32(data[IFLA_GRE_IKEY]);

	if (data[IFLA_GRE_OKEY])
		parms->o_key = nla_get_be32(data[IFLA_GRE_OKEY]);

	if (data[IFLA_GRE_LOCAL])
		parms->iph.saddr = nla_get_in_addr(data[IFLA_GRE_LOCAL]);

	if (data[IFLA_GRE_REMOTE])
		parms->iph.daddr = nla_get_in_addr(data[IFLA_GRE_REMOTE]);

	if (data[IFLA_GRE_TTL])
		parms->iph.ttl = nla_get_u8(data[IFLA_GRE_TTL]);

	if (data[IFLA_GRE_TOS])
		parms->iph.tos = nla_get_u8(data[IFLA_GRE_TOS]);

	if (!data[IFLA_GRE_PMTUDISC] || nla_get_u8(data[IFLA_GRE_PMTUDISC])) {
		if (t->ignore_df)
			return -EINVAL;
		parms->iph.frag_off = htons(IP_DF);
	}

	if (data[IFLA_GRE_COLLECT_METADATA]) {
		t->collect_md = true;
		if (dev->type == ARPHRD_IPGRE)
			dev->type = ARPHRD_NONE;
	}

	if (data[IFLA_GRE_IGNORE_DF]) {
		if (nla_get_u8(data[IFLA_GRE_IGNORE_DF])
		  && (parms->iph.frag_off & htons(IP_DF)))
			return -EINVAL;
		t->ignore_df = !!nla_get_u8(data[IFLA_GRE_IGNORE_DF]);
	}

	if (data[IFLA_GRE_FWMARK])
		*fwmark = nla_get_u32(data[IFLA_GRE_FWMARK]);

	if (data[IFLA_GRE_ERSPAN_VER]) {
		t->erspan_ver = nla_get_u8(data[IFLA_GRE_ERSPAN_VER]);

		if (t->erspan_ver != 1 && t->erspan_ver != 2)
			return -EINVAL;
	}

	if (t->erspan_ver == 1) {
		if (data[IFLA_GRE_ERSPAN_INDEX]) {
			t->index = nla_get_u32(data[IFLA_GRE_ERSPAN_INDEX]);
			if (t->index & ~INDEX_MASK)
				return -EINVAL;
		}
	} else if (t->erspan_ver == 2) {
		if (data[IFLA_GRE_ERSPAN_DIR]) {
			t->dir = nla_get_u8(data[IFLA_GRE_ERSPAN_DIR]);
			if (t->dir & ~(DIR_MASK >> DIR_OFFSET))
				return -EINVAL;
		}
		if (data[IFLA_GRE_ERSPAN_HWID]) {
			t->hwid = nla_get_u16(data[IFLA_GRE_ERSPAN_HWID]);
			if (t->hwid & ~(HWID_MASK >> HWID_OFFSET))
				return -EINVAL;
		}
	}

	return 0;
}