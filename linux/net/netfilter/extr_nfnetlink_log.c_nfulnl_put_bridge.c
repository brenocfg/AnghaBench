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
struct sk_buff {scalar_t__ mac_header; scalar_t__ network_header; int /*<<< orphan*/  vlan_proto; int /*<<< orphan*/  vlan_tci; } ;
struct nlattr {int dummy; } ;
struct nfulnl_instance {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFULA_L2HDR ; 
 int /*<<< orphan*/  NFULA_VLAN ; 
 int /*<<< orphan*/  NFULA_VLAN_PROTO ; 
 int /*<<< orphan*/  NFULA_VLAN_TCI ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (int /*<<< orphan*/ ,struct nlattr*) ; 
 struct nlattr* nla_nest_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_mac_header (struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_mac_header_was_set (struct sk_buff const*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff const*) ; 

__attribute__((used)) static int nfulnl_put_bridge(struct nfulnl_instance *inst, const struct sk_buff *skb)
{
	if (!skb_mac_header_was_set(skb))
		return 0;

	if (skb_vlan_tag_present(skb)) {
		struct nlattr *nest;

		nest = nla_nest_start(inst->skb, NFULA_VLAN);
		if (!nest)
			goto nla_put_failure;

		if (nla_put_be16(inst->skb, NFULA_VLAN_TCI, htons(skb->vlan_tci)) ||
		    nla_put_be16(inst->skb, NFULA_VLAN_PROTO, skb->vlan_proto))
			goto nla_put_failure;

		nla_nest_end(inst->skb, nest);
	}

	if (skb->mac_header < skb->network_header) {
		int len = (int)(skb->network_header - skb->mac_header);

		if (nla_put(inst->skb, NFULA_L2HDR, len, skb_mac_header(skb)))
			goto nla_put_failure;
	}

	return 0;

nla_put_failure:
	return -1;
}