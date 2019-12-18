#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_osr; int /*<<< orphan*/  dccps_role; } ;
struct dccp_hdr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dccpd_seq; } ;
struct TYPE_3__ {int dccph_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_INC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCP_MIB_INERRS ; 
#define  DCCP_PKT_ACK 136 
#define  DCCP_PKT_CLOSE 135 
#define  DCCP_PKT_CLOSEREQ 134 
#define  DCCP_PKT_DATA 133 
#define  DCCP_PKT_DATAACK 132 
#define  DCCP_PKT_REQUEST 131 
#define  DCCP_PKT_RESET 130 
#define  DCCP_PKT_RESPONSE 129 
#define  DCCP_PKT_SYNC 128 
 int DCCP_PKT_SYNCACK ; 
 int /*<<< orphan*/  DCCP_ROLE_CLIENT ; 
 int /*<<< orphan*/  DCCP_ROLE_LISTEN ; 
 TYPE_2__* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_delta_seqno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_enqueue_skb (struct sock*,struct sk_buff*) ; 
 TYPE_1__* dccp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_rcv_close (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_rcv_closereq (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_rcv_reset (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_send_sync (struct sock*,int /*<<< orphan*/ ,int) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 

__attribute__((used)) static int __dccp_rcv_established(struct sock *sk, struct sk_buff *skb,
				  const struct dccp_hdr *dh, const unsigned int len)
{
	struct dccp_sock *dp = dccp_sk(sk);

	switch (dccp_hdr(skb)->dccph_type) {
	case DCCP_PKT_DATAACK:
	case DCCP_PKT_DATA:
		/*
		 * FIXME: schedule DATA_DROPPED (RFC 4340, 11.7.2) if and when
		 * - sk_shutdown == RCV_SHUTDOWN, use Code 1, "Not Listening"
		 * - sk_receive_queue is full, use Code 2, "Receive Buffer"
		 */
		dccp_enqueue_skb(sk, skb);
		return 0;
	case DCCP_PKT_ACK:
		goto discard;
	case DCCP_PKT_RESET:
		/*
		 *  Step 9: Process Reset
		 *	If P.type == Reset,
		 *		Tear down connection
		 *		S.state := TIMEWAIT
		 *		Set TIMEWAIT timer
		 *		Drop packet and return
		 */
		dccp_rcv_reset(sk, skb);
		return 0;
	case DCCP_PKT_CLOSEREQ:
		if (dccp_rcv_closereq(sk, skb))
			return 0;
		goto discard;
	case DCCP_PKT_CLOSE:
		if (dccp_rcv_close(sk, skb))
			return 0;
		goto discard;
	case DCCP_PKT_REQUEST:
		/* Step 7
		 *   or (S.is_server and P.type == Response)
		 *   or (S.is_client and P.type == Request)
		 *   or (S.state >= OPEN and P.type == Request
		 *	and P.seqno >= S.OSR)
		 *    or (S.state >= OPEN and P.type == Response
		 *	and P.seqno >= S.OSR)
		 *    or (S.state == RESPOND and P.type == Data),
		 *  Send Sync packet acknowledging P.seqno
		 *  Drop packet and return
		 */
		if (dp->dccps_role != DCCP_ROLE_LISTEN)
			goto send_sync;
		goto check_seq;
	case DCCP_PKT_RESPONSE:
		if (dp->dccps_role != DCCP_ROLE_CLIENT)
			goto send_sync;
check_seq:
		if (dccp_delta_seqno(dp->dccps_osr,
				     DCCP_SKB_CB(skb)->dccpd_seq) >= 0) {
send_sync:
			dccp_send_sync(sk, DCCP_SKB_CB(skb)->dccpd_seq,
				       DCCP_PKT_SYNC);
		}
		break;
	case DCCP_PKT_SYNC:
		dccp_send_sync(sk, DCCP_SKB_CB(skb)->dccpd_seq,
			       DCCP_PKT_SYNCACK);
		/*
		 * From RFC 4340, sec. 5.7
		 *
		 * As with DCCP-Ack packets, DCCP-Sync and DCCP-SyncAck packets
		 * MAY have non-zero-length application data areas, whose
		 * contents receivers MUST ignore.
		 */
		goto discard;
	}

	DCCP_INC_STATS(DCCP_MIB_INERRS);
discard:
	__kfree_skb(skb);
	return 0;
}