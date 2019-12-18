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
struct sock {int sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct sk_buff {int dummy; } ;
struct dccp_sock {scalar_t__ dccps_role; } ;
struct dccp_skb_cb {int /*<<< orphan*/  dccpd_seq; void* dccpd_reset_code; } ;
struct dccp_hdr {scalar_t__ dccph_type; } ;
struct TYPE_4__ {TYPE_1__* icsk_af_ops; } ;
struct TYPE_3__ {scalar_t__ (* conn_request ) (struct sock*,struct sk_buff*) ;} ;

/* Variables and functions */
 int DCCP_CLOSED ; 
 int DCCP_LISTEN ; 
#define  DCCP_PARTOPEN 130 
 scalar_t__ DCCP_PKT_ACK ; 
 scalar_t__ DCCP_PKT_CLOSE ; 
 scalar_t__ DCCP_PKT_CLOSEREQ ; 
 scalar_t__ DCCP_PKT_DATA ; 
 scalar_t__ DCCP_PKT_DATAACK ; 
 scalar_t__ DCCP_PKT_REQUEST ; 
 scalar_t__ DCCP_PKT_RESET ; 
 scalar_t__ DCCP_PKT_RESPONSE ; 
 scalar_t__ DCCP_PKT_SYNC ; 
 scalar_t__ DCCP_PKT_SYNCACK ; 
#define  DCCP_REQUESTING 129 
 void* DCCP_RESET_CODE_NO_CONNECTION ; 
#define  DCCP_RESPOND 128 
 scalar_t__ DCCP_ROLE_CLIENT ; 
 struct dccp_skb_cb* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  POLL_OUT ; 
 int /*<<< orphan*/  SOCK_WAKE_IO ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 scalar_t__ dccp_check_seqno (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_deliver_input_to_ccids (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_handle_ackvec_processing (struct sock*,struct sk_buff*) ; 
 scalar_t__ dccp_parse_options (struct sock*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ dccp_rcv_close (struct sock*,struct sk_buff*) ; 
 scalar_t__ dccp_rcv_closereq (struct sock*,struct sk_buff*) ; 
 int dccp_rcv_request_sent_state_process (struct sock*,struct sk_buff*,struct dccp_hdr*,unsigned int) ; 
 int /*<<< orphan*/  dccp_rcv_reset (struct sock*,struct sk_buff*) ; 
 int dccp_rcv_respond_partopen_state_process (struct sock*,struct sk_buff*,struct dccp_hdr*,unsigned int) ; 
 int /*<<< orphan*/  dccp_send_sync (struct sock*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_wake_async (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

int dccp_rcv_state_process(struct sock *sk, struct sk_buff *skb,
			   struct dccp_hdr *dh, unsigned int len)
{
	struct dccp_sock *dp = dccp_sk(sk);
	struct dccp_skb_cb *dcb = DCCP_SKB_CB(skb);
	const int old_state = sk->sk_state;
	bool acceptable;
	int queued = 0;

	/*
	 *  Step 3: Process LISTEN state
	 *
	 *     If S.state == LISTEN,
	 *	 If P.type == Request or P contains a valid Init Cookie option,
	 *	      (* Must scan the packet's options to check for Init
	 *		 Cookies.  Only Init Cookies are processed here,
	 *		 however; other options are processed in Step 8.  This
	 *		 scan need only be performed if the endpoint uses Init
	 *		 Cookies *)
	 *	      (* Generate a new socket and switch to that socket *)
	 *	      Set S := new socket for this port pair
	 *	      S.state = RESPOND
	 *	      Choose S.ISS (initial seqno) or set from Init Cookies
	 *	      Initialize S.GAR := S.ISS
	 *	      Set S.ISR, S.GSR, S.SWL, S.SWH from packet or Init
	 *	      Cookies Continue with S.state == RESPOND
	 *	      (* A Response packet will be generated in Step 11 *)
	 *	 Otherwise,
	 *	      Generate Reset(No Connection) unless P.type == Reset
	 *	      Drop packet and return
	 */
	if (sk->sk_state == DCCP_LISTEN) {
		if (dh->dccph_type == DCCP_PKT_REQUEST) {
			/* It is possible that we process SYN packets from backlog,
			 * so we need to make sure to disable BH and RCU right there.
			 */
			rcu_read_lock();
			local_bh_disable();
			acceptable = inet_csk(sk)->icsk_af_ops->conn_request(sk, skb) >= 0;
			local_bh_enable();
			rcu_read_unlock();
			if (!acceptable)
				return 1;
			consume_skb(skb);
			return 0;
		}
		if (dh->dccph_type == DCCP_PKT_RESET)
			goto discard;

		/* Caller (dccp_v4_do_rcv) will send Reset */
		dcb->dccpd_reset_code = DCCP_RESET_CODE_NO_CONNECTION;
		return 1;
	} else if (sk->sk_state == DCCP_CLOSED) {
		dcb->dccpd_reset_code = DCCP_RESET_CODE_NO_CONNECTION;
		return 1;
	}

	/* Step 6: Check sequence numbers (omitted in LISTEN/REQUEST state) */
	if (sk->sk_state != DCCP_REQUESTING && dccp_check_seqno(sk, skb))
		goto discard;

	/*
	 *   Step 7: Check for unexpected packet types
	 *      If (S.is_server and P.type == Response)
	 *	    or (S.is_client and P.type == Request)
	 *	    or (S.state == RESPOND and P.type == Data),
	 *	  Send Sync packet acknowledging P.seqno
	 *	  Drop packet and return
	 */
	if ((dp->dccps_role != DCCP_ROLE_CLIENT &&
	     dh->dccph_type == DCCP_PKT_RESPONSE) ||
	    (dp->dccps_role == DCCP_ROLE_CLIENT &&
	     dh->dccph_type == DCCP_PKT_REQUEST) ||
	    (sk->sk_state == DCCP_RESPOND && dh->dccph_type == DCCP_PKT_DATA)) {
		dccp_send_sync(sk, dcb->dccpd_seq, DCCP_PKT_SYNC);
		goto discard;
	}

	/*  Step 8: Process options */
	if (dccp_parse_options(sk, NULL, skb))
		return 1;

	/*
	 *  Step 9: Process Reset
	 *	If P.type == Reset,
	 *		Tear down connection
	 *		S.state := TIMEWAIT
	 *		Set TIMEWAIT timer
	 *		Drop packet and return
	 */
	if (dh->dccph_type == DCCP_PKT_RESET) {
		dccp_rcv_reset(sk, skb);
		return 0;
	} else if (dh->dccph_type == DCCP_PKT_CLOSEREQ) {	/* Step 13 */
		if (dccp_rcv_closereq(sk, skb))
			return 0;
		goto discard;
	} else if (dh->dccph_type == DCCP_PKT_CLOSE) {		/* Step 14 */
		if (dccp_rcv_close(sk, skb))
			return 0;
		goto discard;
	}

	switch (sk->sk_state) {
	case DCCP_REQUESTING:
		queued = dccp_rcv_request_sent_state_process(sk, skb, dh, len);
		if (queued >= 0)
			return queued;

		__kfree_skb(skb);
		return 0;

	case DCCP_PARTOPEN:
		/* Step 8: if using Ack Vectors, mark packet acknowledgeable */
		dccp_handle_ackvec_processing(sk, skb);
		dccp_deliver_input_to_ccids(sk, skb);
		/* fall through */
	case DCCP_RESPOND:
		queued = dccp_rcv_respond_partopen_state_process(sk, skb,
								 dh, len);
		break;
	}

	if (dh->dccph_type == DCCP_PKT_ACK ||
	    dh->dccph_type == DCCP_PKT_DATAACK) {
		switch (old_state) {
		case DCCP_PARTOPEN:
			sk->sk_state_change(sk);
			sk_wake_async(sk, SOCK_WAKE_IO, POLL_OUT);
			break;
		}
	} else if (unlikely(dh->dccph_type == DCCP_PKT_SYNC)) {
		dccp_send_sync(sk, dcb->dccpd_seq, DCCP_PKT_SYNCACK);
		goto discard;
	}

	if (!queued) {
discard:
		__kfree_skb(skb);
	}
	return 0;
}