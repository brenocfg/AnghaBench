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
struct vlan_head {int /*<<< orphan*/  tci; int /*<<< orphan*/  tpid; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_ETHERTYPE ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_VLAN ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovs_nla_put_vlan(struct sk_buff *skb, const struct vlan_head *vh,
			    bool is_mask)
{
	__be16 eth_type = !is_mask ? vh->tpid : htons(0xffff);

	if (nla_put_be16(skb, OVS_KEY_ATTR_ETHERTYPE, eth_type) ||
	    nla_put_be16(skb, OVS_KEY_ATTR_VLAN, vh->tci))
		return -EMSGSIZE;
	return 0;
}