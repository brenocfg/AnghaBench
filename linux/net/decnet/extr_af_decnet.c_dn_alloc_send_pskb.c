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

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_DNA_RT ; 
 int /*<<< orphan*/  PACKET_OUTGOING ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct sk_buff* sock_alloc_send_skb (struct sock*,unsigned long,int,int*) ; 

__attribute__((used)) static inline struct sk_buff *dn_alloc_send_pskb(struct sock *sk,
			      unsigned long datalen, int noblock,
			      int *errcode)
{
	struct sk_buff *skb = sock_alloc_send_skb(sk, datalen,
						   noblock, errcode);
	if (skb) {
		skb->protocol = htons(ETH_P_DNA_RT);
		skb->pkt_type = PACKET_OUTGOING;
	}
	return skb;
}