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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  MAC_PROTO_NONE ; 
 int /*<<< orphan*/  invalidate_flow_key (struct sw_flow_key*) ; 
 int /*<<< orphan*/  skb_pull_rcsum (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 

__attribute__((used)) static int pop_eth(struct sk_buff *skb, struct sw_flow_key *key)
{
	skb_pull_rcsum(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	skb_reset_mac_len(skb);

	/* safe right before invalidate_flow_key */
	key->mac_proto = MAC_PROTO_NONE;
	invalidate_flow_key(key);
	return 0;
}