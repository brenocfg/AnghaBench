#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct tcphdr {int doff; int /*<<< orphan*/  rst; } ;
struct tcp_options_received {int /*<<< orphan*/  rcv_tsval; scalar_t__ saw_tstamp; scalar_t__ ts_recent_stamp; scalar_t__ rcv_tsecr; int /*<<< orphan*/  ts_recent; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_24__ {unsigned long expires; } ;
struct request_sock {int num_timeout; TYPE_4__* rsk_ops; int /*<<< orphan*/  ts_recent; scalar_t__ rsk_rcv_wnd; TYPE_9__ rsk_timer; } ;
typedef  int __be32 ;
struct TYPE_20__ {int /*<<< orphan*/  sysctl_tcp_abort_on_overflow; } ;
struct TYPE_23__ {TYPE_3__ ipv4; } ;
struct TYPE_22__ {scalar_t__ rcv_isn; scalar_t__ snt_isn; scalar_t__ rcv_nxt; int /*<<< orphan*/  last_oow_ack_time; scalar_t__ ts_off; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* send_reset ) (struct sock*,struct sk_buff*) ;int /*<<< orphan*/  (* send_ack ) (struct sock*,struct sk_buff*,struct request_sock*) ;} ;
struct TYPE_19__ {struct sock* (* syn_recv_sock ) (struct sock*,struct sk_buff*,struct request_sock*,int /*<<< orphan*/ *,struct request_sock*,int*) ;} ;
struct TYPE_18__ {int rskq_defer_accept; } ;
struct TYPE_17__ {scalar_t__ seq; scalar_t__ ack_seq; scalar_t__ end_seq; } ;
struct TYPE_16__ {TYPE_2__* icsk_af_ops; TYPE_1__ icsk_accept_queue; } ;
struct TYPE_15__ {int acked; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  LINUX_MIB_EMBRYONICRSTS ; 
 int /*<<< orphan*/  LINUX_MIB_PAWSESTABREJECTED ; 
 int /*<<< orphan*/  LINUX_MIB_TCPACKSKIPPEDSYNRECV ; 
 int /*<<< orphan*/  LINUX_MIB_TCPDEFERACCEPTDROP ; 
 int TCP_FLAG_ACK ; 
 int TCP_FLAG_RST ; 
 int TCP_FLAG_SYN ; 
 int /*<<< orphan*/  TCP_MIB_ATTEMPTFAILS ; 
 int /*<<< orphan*/  TCP_RTO_MAX ; 
 TYPE_14__* TCP_SKB_CB (struct sk_buff*) ; 
 int TCP_TIMEOUT_INIT ; 
 int /*<<< orphan*/  __NET_INC_STATS (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __TCP_INC_STATS (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  after (scalar_t__,scalar_t__) ; 
 TYPE_11__* inet_csk (struct sock*) ; 
 struct sock* inet_csk_complete_hashdance (struct sock*,struct sock*,struct request_sock*,int) ; 
 int /*<<< orphan*/  inet_csk_reqsk_queue_drop (struct sock*,struct request_sock*) ; 
 TYPE_10__* inet_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  inet_rtx_syn_ack (struct sock*,struct request_sock*) ; 
 unsigned long jiffies ; 
 scalar_t__ ktime_get_seconds () ; 
 scalar_t__ min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer_pending (TYPE_9__*,unsigned long) ; 
 int /*<<< orphan*/  reqsk_fastopen_remove (struct sock*,struct request_sock*,int) ; 
 TYPE_6__* sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_rps_save_rxhash (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,struct sk_buff*,struct request_sock*) ; 
 struct sock* stub2 (struct sock*,struct sk_buff*,struct request_sock*,int /*<<< orphan*/ *,struct request_sock*,int*) ; 
 int /*<<< orphan*/  stub3 (struct sock*,struct sk_buff*) ; 
 int tcp_flag_word (struct tcphdr const*) ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_in_window (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tcp_oow_rate_limited (TYPE_6__*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_parse_options (TYPE_6__*,struct sk_buff*,struct tcp_options_received*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tcp_paws_reject (struct tcp_options_received*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_reset (struct sock*) ; 
 TYPE_5__* tcp_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  tcp_synack_rtt_meas (struct sock*,struct request_sock*) ; 

struct sock *tcp_check_req(struct sock *sk, struct sk_buff *skb,
			   struct request_sock *req,
			   bool fastopen, bool *req_stolen)
{
	struct tcp_options_received tmp_opt;
	struct sock *child;
	const struct tcphdr *th = tcp_hdr(skb);
	__be32 flg = tcp_flag_word(th) & (TCP_FLAG_RST|TCP_FLAG_SYN|TCP_FLAG_ACK);
	bool paws_reject = false;
	bool own_req;

	tmp_opt.saw_tstamp = 0;
	if (th->doff > (sizeof(struct tcphdr)>>2)) {
		tcp_parse_options(sock_net(sk), skb, &tmp_opt, 0, NULL);

		if (tmp_opt.saw_tstamp) {
			tmp_opt.ts_recent = req->ts_recent;
			if (tmp_opt.rcv_tsecr)
				tmp_opt.rcv_tsecr -= tcp_rsk(req)->ts_off;
			/* We do not store true stamp, but it is not required,
			 * it can be estimated (approximately)
			 * from another data.
			 */
			tmp_opt.ts_recent_stamp = ktime_get_seconds() - ((TCP_TIMEOUT_INIT/HZ)<<req->num_timeout);
			paws_reject = tcp_paws_reject(&tmp_opt, th->rst);
		}
	}

	/* Check for pure retransmitted SYN. */
	if (TCP_SKB_CB(skb)->seq == tcp_rsk(req)->rcv_isn &&
	    flg == TCP_FLAG_SYN &&
	    !paws_reject) {
		/*
		 * RFC793 draws (Incorrectly! It was fixed in RFC1122)
		 * this case on figure 6 and figure 8, but formal
		 * protocol description says NOTHING.
		 * To be more exact, it says that we should send ACK,
		 * because this segment (at least, if it has no data)
		 * is out of window.
		 *
		 *  CONCLUSION: RFC793 (even with RFC1122) DOES NOT
		 *  describe SYN-RECV state. All the description
		 *  is wrong, we cannot believe to it and should
		 *  rely only on common sense and implementation
		 *  experience.
		 *
		 * Enforce "SYN-ACK" according to figure 8, figure 6
		 * of RFC793, fixed by RFC1122.
		 *
		 * Note that even if there is new data in the SYN packet
		 * they will be thrown away too.
		 *
		 * Reset timer after retransmitting SYNACK, similar to
		 * the idea of fast retransmit in recovery.
		 */
		if (!tcp_oow_rate_limited(sock_net(sk), skb,
					  LINUX_MIB_TCPACKSKIPPEDSYNRECV,
					  &tcp_rsk(req)->last_oow_ack_time) &&

		    !inet_rtx_syn_ack(sk, req)) {
			unsigned long expires = jiffies;

			expires += min(TCP_TIMEOUT_INIT << req->num_timeout,
				       TCP_RTO_MAX);
			if (!fastopen)
				mod_timer_pending(&req->rsk_timer, expires);
			else
				req->rsk_timer.expires = expires;
		}
		return NULL;
	}

	/* Further reproduces section "SEGMENT ARRIVES"
	   for state SYN-RECEIVED of RFC793.
	   It is broken, however, it does not work only
	   when SYNs are crossed.

	   You would think that SYN crossing is impossible here, since
	   we should have a SYN_SENT socket (from connect()) on our end,
	   but this is not true if the crossed SYNs were sent to both
	   ends by a malicious third party.  We must defend against this,
	   and to do that we first verify the ACK (as per RFC793, page
	   36) and reset if it is invalid.  Is this a true full defense?
	   To convince ourselves, let us consider a way in which the ACK
	   test can still pass in this 'malicious crossed SYNs' case.
	   Malicious sender sends identical SYNs (and thus identical sequence
	   numbers) to both A and B:

		A: gets SYN, seq=7
		B: gets SYN, seq=7

	   By our good fortune, both A and B select the same initial
	   send sequence number of seven :-)

		A: sends SYN|ACK, seq=7, ack_seq=8
		B: sends SYN|ACK, seq=7, ack_seq=8

	   So we are now A eating this SYN|ACK, ACK test passes.  So
	   does sequence test, SYN is truncated, and thus we consider
	   it a bare ACK.

	   If icsk->icsk_accept_queue.rskq_defer_accept, we silently drop this
	   bare ACK.  Otherwise, we create an established connection.  Both
	   ends (listening sockets) accept the new incoming connection and try
	   to talk to each other. 8-)

	   Note: This case is both harmless, and rare.  Possibility is about the
	   same as us discovering intelligent life on another plant tomorrow.

	   But generally, we should (RFC lies!) to accept ACK
	   from SYNACK both here and in tcp_rcv_state_process().
	   tcp_rcv_state_process() does not, hence, we do not too.

	   Note that the case is absolutely generic:
	   we cannot optimize anything here without
	   violating protocol. All the checks must be made
	   before attempt to create socket.
	 */

	/* RFC793 page 36: "If the connection is in any non-synchronized state ...
	 *                  and the incoming segment acknowledges something not yet
	 *                  sent (the segment carries an unacceptable ACK) ...
	 *                  a reset is sent."
	 *
	 * Invalid ACK: reset will be sent by listening socket.
	 * Note that the ACK validity check for a Fast Open socket is done
	 * elsewhere and is checked directly against the child socket rather
	 * than req because user data may have been sent out.
	 */
	if ((flg & TCP_FLAG_ACK) && !fastopen &&
	    (TCP_SKB_CB(skb)->ack_seq !=
	     tcp_rsk(req)->snt_isn + 1))
		return sk;

	/* Also, it would be not so bad idea to check rcv_tsecr, which
	 * is essentially ACK extension and too early or too late values
	 * should cause reset in unsynchronized states.
	 */

	/* RFC793: "first check sequence number". */

	if (paws_reject || !tcp_in_window(TCP_SKB_CB(skb)->seq, TCP_SKB_CB(skb)->end_seq,
					  tcp_rsk(req)->rcv_nxt, tcp_rsk(req)->rcv_nxt + req->rsk_rcv_wnd)) {
		/* Out of window: send ACK and drop. */
		if (!(flg & TCP_FLAG_RST) &&
		    !tcp_oow_rate_limited(sock_net(sk), skb,
					  LINUX_MIB_TCPACKSKIPPEDSYNRECV,
					  &tcp_rsk(req)->last_oow_ack_time))
			req->rsk_ops->send_ack(sk, skb, req);
		if (paws_reject)
			__NET_INC_STATS(sock_net(sk), LINUX_MIB_PAWSESTABREJECTED);
		return NULL;
	}

	/* In sequence, PAWS is OK. */

	if (tmp_opt.saw_tstamp && !after(TCP_SKB_CB(skb)->seq, tcp_rsk(req)->rcv_nxt))
		req->ts_recent = tmp_opt.rcv_tsval;

	if (TCP_SKB_CB(skb)->seq == tcp_rsk(req)->rcv_isn) {
		/* Truncate SYN, it is out of window starting
		   at tcp_rsk(req)->rcv_isn + 1. */
		flg &= ~TCP_FLAG_SYN;
	}

	/* RFC793: "second check the RST bit" and
	 *	   "fourth, check the SYN bit"
	 */
	if (flg & (TCP_FLAG_RST|TCP_FLAG_SYN)) {
		__TCP_INC_STATS(sock_net(sk), TCP_MIB_ATTEMPTFAILS);
		goto embryonic_reset;
	}

	/* ACK sequence verified above, just make sure ACK is
	 * set.  If ACK not set, just silently drop the packet.
	 *
	 * XXX (TFO) - if we ever allow "data after SYN", the
	 * following check needs to be removed.
	 */
	if (!(flg & TCP_FLAG_ACK))
		return NULL;

	/* For Fast Open no more processing is needed (sk is the
	 * child socket).
	 */
	if (fastopen)
		return sk;

	/* While TCP_DEFER_ACCEPT is active, drop bare ACK. */
	if (req->num_timeout < inet_csk(sk)->icsk_accept_queue.rskq_defer_accept &&
	    TCP_SKB_CB(skb)->end_seq == tcp_rsk(req)->rcv_isn + 1) {
		inet_rsk(req)->acked = 1;
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPDEFERACCEPTDROP);
		return NULL;
	}

	/* OK, ACK is valid, create big socket and
	 * feed this segment to it. It will repeat all
	 * the tests. THIS SEGMENT MUST MOVE SOCKET TO
	 * ESTABLISHED STATE. If it will be dropped after
	 * socket is created, wait for troubles.
	 */
	child = inet_csk(sk)->icsk_af_ops->syn_recv_sock(sk, skb, req, NULL,
							 req, &own_req);
	if (!child)
		goto listen_overflow;

	sock_rps_save_rxhash(child, skb);
	tcp_synack_rtt_meas(child, req);
	*req_stolen = !own_req;
	return inet_csk_complete_hashdance(sk, child, req, own_req);

listen_overflow:
	if (!sock_net(sk)->ipv4.sysctl_tcp_abort_on_overflow) {
		inet_rsk(req)->acked = 1;
		return NULL;
	}

embryonic_reset:
	if (!(flg & TCP_FLAG_RST)) {
		/* Received a bad SYN pkt - for TFO We try not to reset
		 * the local connection unless it's really necessary to
		 * avoid becoming vulnerable to outside attack aiming at
		 * resetting legit local connections.
		 */
		req->rsk_ops->send_reset(sk, skb);
	} else if (fastopen) { /* received a valid RST pkt */
		reqsk_fastopen_remove(sk, req, true);
		tcp_reset(sk);
	}
	if (!fastopen) {
		inet_csk_reqsk_queue_drop(sk, req);
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_EMBRYONICRSTS);
	}
	return NULL;
}