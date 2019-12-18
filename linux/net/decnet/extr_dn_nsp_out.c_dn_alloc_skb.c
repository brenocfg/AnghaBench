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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  protocol; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_DNA_RT ; 
 int /*<<< orphan*/  PACKET_OUTGOING ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 

struct sk_buff *dn_alloc_skb(struct sock *sk, int size, gfp_t pri)
{
	struct sk_buff *skb;
	int hdr = 64;

	if ((skb = alloc_skb(size + hdr, pri)) == NULL)
		return NULL;

	skb->protocol = htons(ETH_P_DNA_RT);
	skb->pkt_type = PACKET_OUTGOING;

	if (sk)
		skb_set_owner_w(skb, sk);

	skb_reserve(skb, hdr);

	return skb;
}