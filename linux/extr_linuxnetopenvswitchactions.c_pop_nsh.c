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
struct sw_flow_key {int /*<<< orphan*/  mac_proto; } ;
struct sk_buff {scalar_t__ protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_TEB ; 
 int /*<<< orphan*/  MAC_PROTO_ETHERNET ; 
 int /*<<< orphan*/  MAC_PROTO_NONE ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_flow_key (struct sw_flow_key*) ; 
 int nsh_pop (struct sk_buff*) ; 

__attribute__((used)) static int pop_nsh(struct sk_buff *skb, struct sw_flow_key *key)
{
	int err;

	err = nsh_pop(skb);
	if (err)
		return err;

	/* safe right before invalidate_flow_key */
	if (skb->protocol == htons(ETH_P_TEB))
		key->mac_proto = MAC_PROTO_ETHERNET;
	else
		key->mac_proto = MAC_PROTO_NONE;
	invalidate_flow_key(key);
	return 0;
}