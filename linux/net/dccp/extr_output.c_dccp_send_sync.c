#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct sock {TYPE_1__* sk_prot; } ;
struct sk_buff {int dummy; } ;
typedef  enum dccp_pkt_type { ____Placeholder_dccp_pkt_type } dccp_pkt_type ;
struct TYPE_6__ {int dccpd_type; int /*<<< orphan*/  dccpd_ack_seq; } ;
struct TYPE_5__ {scalar_t__ dccps_sync_scheduled; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_CRIT (char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_packet_name (int const) ; 
 TYPE_2__* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_transmit_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

void dccp_send_sync(struct sock *sk, const u64 ackno,
		    const enum dccp_pkt_type pkt_type)
{
	/*
	 * We are not putting this on the write queue, so
	 * dccp_transmit_skb() will set the ownership to this
	 * sock.
	 */
	struct sk_buff *skb = alloc_skb(sk->sk_prot->max_header, GFP_ATOMIC);

	if (skb == NULL) {
		/* FIXME: how to make sure the sync is sent? */
		DCCP_CRIT("could not send %s", dccp_packet_name(pkt_type));
		return;
	}

	/* Reserve space for headers and prepare control bits. */
	skb_reserve(skb, sk->sk_prot->max_header);
	DCCP_SKB_CB(skb)->dccpd_type = pkt_type;
	DCCP_SKB_CB(skb)->dccpd_ack_seq = ackno;

	/*
	 * Clear the flag in case the Sync was scheduled for out-of-band data,
	 * such as carrying a long Ack Vector.
	 */
	dccp_sk(sk)->dccps_sync_scheduled = 0;

	dccp_transmit_skb(sk, skb);
}