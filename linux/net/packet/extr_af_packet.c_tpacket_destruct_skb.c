#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  pg_vec; } ;
struct packet_sock {int /*<<< orphan*/  skb_completion; TYPE_1__ tx_ring; } ;
typedef  int __u32 ;

/* Variables and functions */
 int TP_STATUS_AVAILABLE ; 
 int /*<<< orphan*/  __packet_set_status (struct packet_sock*,void*,int) ; 
 int __packet_set_timestamp (struct packet_sock*,void*,struct sk_buff*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_dec_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  packet_read_pending (TYPE_1__*) ; 
 struct packet_sock* pkt_sk (int /*<<< orphan*/ ) ; 
 void* skb_zcopy_get_nouarg (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_wfree (struct sk_buff*) ; 

__attribute__((used)) static void tpacket_destruct_skb(struct sk_buff *skb)
{
	struct packet_sock *po = pkt_sk(skb->sk);

	if (likely(po->tx_ring.pg_vec)) {
		void *ph;
		__u32 ts;

		ph = skb_zcopy_get_nouarg(skb);
		packet_dec_pending(&po->tx_ring);

		ts = __packet_set_timestamp(po, ph, skb);
		__packet_set_status(po, ph, TP_STATUS_AVAILABLE | ts);

		if (!packet_read_pending(&po->tx_ring))
			complete(&po->skb_completion);
	}

	sock_wfree(skb);
}