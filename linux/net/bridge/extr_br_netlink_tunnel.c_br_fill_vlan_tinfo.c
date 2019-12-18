#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_BRIDGE_VLAN_TUNNEL_FLAGS ; 
 int /*<<< orphan*/  IFLA_BRIDGE_VLAN_TUNNEL_ID ; 
 int /*<<< orphan*/  IFLA_BRIDGE_VLAN_TUNNEL_INFO ; 
 int /*<<< orphan*/  IFLA_BRIDGE_VLAN_TUNNEL_VID ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tunnel_id_to_key32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int br_fill_vlan_tinfo(struct sk_buff *skb, u16 vid,
			      __be64 tunnel_id, u16 flags)
{
	__be32 tid = tunnel_id_to_key32(tunnel_id);
	struct nlattr *tmap;

	tmap = nla_nest_start_noflag(skb, IFLA_BRIDGE_VLAN_TUNNEL_INFO);
	if (!tmap)
		return -EMSGSIZE;
	if (nla_put_u32(skb, IFLA_BRIDGE_VLAN_TUNNEL_ID,
			be32_to_cpu(tid)))
		goto nla_put_failure;
	if (nla_put_u16(skb, IFLA_BRIDGE_VLAN_TUNNEL_VID,
			vid))
		goto nla_put_failure;
	if (nla_put_u16(skb, IFLA_BRIDGE_VLAN_TUNNEL_FLAGS,
			flags))
		goto nla_put_failure;
	nla_nest_end(skb, tmap);

	return 0;

nla_put_failure:
	nla_nest_cancel(skb, tmap);

	return -EMSGSIZE;
}