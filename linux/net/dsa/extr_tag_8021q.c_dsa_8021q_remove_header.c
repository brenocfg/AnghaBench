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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_pull_rcsum (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 

struct sk_buff *dsa_8021q_remove_header(struct sk_buff *skb)
{
	u8 *from = skb_mac_header(skb);
	u8 *dest = from + VLAN_HLEN;

	memmove(dest, from, ETH_HLEN - VLAN_HLEN);
	skb_pull(skb, VLAN_HLEN);
	skb_push(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	skb_reset_mac_len(skb);
	skb_pull_rcsum(skb, ETH_HLEN);

	return skb;
}