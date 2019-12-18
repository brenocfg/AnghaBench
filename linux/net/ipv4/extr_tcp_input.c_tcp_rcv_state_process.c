#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tcphdr {scalar_t__ fin; int /*<<< orphan*/  window; scalar_t__ syn; scalar_t__ rst; scalar_t__ ack; } ;
struct TYPE_6__ {int snd_wscale; int /*<<< orphan*/  tstamp_ok; scalar_t__ saw_tstamp; } ;
struct tcp_sock {int snd_wnd; int /*<<< orphan*/  rcv_nxt; int /*<<< orphan*/  write_seq; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  syn_fastopen; int /*<<< orphan*/  linger2; int /*<<< orphan*/  lsndtime; int /*<<< orphan*/  advmss; TYPE_2__ rx_opt; int /*<<< orphan*/  copied_seq; int /*<<< orphan*/  retrans_stamp; int /*<<< orphan*/  srtt_us; int /*<<< orphan*/  delivered; int /*<<< orphan*/  fastopen_rsk; } ;
struct sock {int sk_state; int sk_shutdown; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_socket; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int dummy; } ;
struct inet_connection_sock {TYPE_3__* icsk_ca_ops; TYPE_1__* icsk_af_ops; } ;
struct TYPE_8__ {scalar_t__ end_seq; scalar_t__ seq; int /*<<< orphan*/  ack_seq; } ;
struct TYPE_7__ {int /*<<< orphan*/  cong_control; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* conn_request ) (struct sock*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB ; 
 int FLAG_NO_CHALLENGE_ACK ; 
 int FLAG_SLOWPATH ; 
 int FLAG_UPDATE_TS_RECENT ; 
 int /*<<< orphan*/  LINUX_MIB_TCPABORTONDATA ; 
 int /*<<< orphan*/  NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POLL_OUT ; 
 int RCV_SHUTDOWN ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  SOCK_WAKE_IO ; 
 int /*<<< orphan*/  TCPOLEN_TSTAMP_ALIGNED ; 
#define  TCP_CLOSE 137 
#define  TCP_CLOSE_WAIT 136 
#define  TCP_CLOSING 135 
#define  TCP_ESTABLISHED 134 
#define  TCP_FIN_WAIT1 133 
#define  TCP_FIN_WAIT2 132 
#define  TCP_LAST_ACK 131 
#define  TCP_LISTEN 130 
 TYPE_4__* TCP_SKB_CB (struct sk_buff*) ; 
#define  TCP_SYN_RECV 129 
#define  TCP_SYN_SENT 128 
 int TCP_TIMEWAIT_LEN ; 
 int TCP_TIME_WAIT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  after (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  before (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_keepalive_timer (struct sock*,int) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  lockdep_sock_is_held (struct sock*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct request_sock* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_dst_confirm (struct sock*) ; 
 int /*<<< orphan*/  sk_wake_async (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  stub3 (struct sock*) ; 
 scalar_t__ tcp_ack (struct sock*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  tcp_ack_snd_check (struct sock*) ; 
 int /*<<< orphan*/  tcp_check_req (struct sock*,struct sk_buff*,struct request_sock*,int,int*) ; 
 int /*<<< orphan*/  tcp_data_queue (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_data_snd_check (struct sock*) ; 
 int /*<<< orphan*/  tcp_done (struct sock*) ; 
 int /*<<< orphan*/  tcp_drop (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_fast_path_on (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_fastopen_active_disable (struct sock*) ; 
 int tcp_fin_time (struct sock*) ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_init_transfer (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_init_wl (struct tcp_sock*,scalar_t__) ; 
 int /*<<< orphan*/  tcp_initialize_rcv_mss (struct sock*) ; 
 int /*<<< orphan*/  tcp_jiffies32 ; 
 int /*<<< orphan*/  tcp_mstamp_refresh (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_rcv_synrecv_state_fastopen (struct sock*) ; 
 int tcp_rcv_synsent_state_process (struct sock*,struct sk_buff*,struct tcphdr const*) ; 
 int /*<<< orphan*/  tcp_reset (struct sock*) ; 
 int /*<<< orphan*/  tcp_send_challenge_ack (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_set_state (struct sock*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_synack_rtt_meas (struct sock*,struct request_sock*) ; 
 int /*<<< orphan*/  tcp_time_wait (struct sock*,int,int) ; 
 int /*<<< orphan*/  tcp_try_undo_spurious_syn (struct sock*) ; 
 int /*<<< orphan*/  tcp_update_metrics (struct sock*) ; 
 int /*<<< orphan*/  tcp_update_pacing_rate (struct sock*) ; 
 int /*<<< orphan*/  tcp_urg (struct sock*,struct sk_buff*,struct tcphdr const*) ; 
 int /*<<< orphan*/  tcp_validate_incoming (struct sock*,struct sk_buff*,struct tcphdr const*,int /*<<< orphan*/ ) ; 

int tcp_rcv_state_process(struct sock *sk, struct sk_buff *skb)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);
	const struct tcphdr *th = tcp_hdr(skb);
	struct request_sock *req;
	int queued = 0;
	bool acceptable;

	switch (sk->sk_state) {
	case TCP_CLOSE:
		goto discard;

	case TCP_LISTEN:
		if (th->ack)
			return 1;

		if (th->rst)
			goto discard;

		if (th->syn) {
			if (th->fin)
				goto discard;
			/* It is possible that we process SYN packets from backlog,
			 * so we need to make sure to disable BH and RCU right there.
			 */
			rcu_read_lock();
			local_bh_disable();
			acceptable = icsk->icsk_af_ops->conn_request(sk, skb) >= 0;
			local_bh_enable();
			rcu_read_unlock();

			if (!acceptable)
				return 1;
			consume_skb(skb);
			return 0;
		}
		goto discard;

	case TCP_SYN_SENT:
		tp->rx_opt.saw_tstamp = 0;
		tcp_mstamp_refresh(tp);
		queued = tcp_rcv_synsent_state_process(sk, skb, th);
		if (queued >= 0)
			return queued;

		/* Do step6 onward by hand. */
		tcp_urg(sk, skb, th);
		__kfree_skb(skb);
		tcp_data_snd_check(sk);
		return 0;
	}

	tcp_mstamp_refresh(tp);
	tp->rx_opt.saw_tstamp = 0;
	req = rcu_dereference_protected(tp->fastopen_rsk,
					lockdep_sock_is_held(sk));
	if (req) {
		bool req_stolen;

		WARN_ON_ONCE(sk->sk_state != TCP_SYN_RECV &&
		    sk->sk_state != TCP_FIN_WAIT1);

		if (!tcp_check_req(sk, skb, req, true, &req_stolen))
			goto discard;
	}

	if (!th->ack && !th->rst && !th->syn)
		goto discard;

	if (!tcp_validate_incoming(sk, skb, th, 0))
		return 0;

	/* step 5: check the ACK field */
	acceptable = tcp_ack(sk, skb, FLAG_SLOWPATH |
				      FLAG_UPDATE_TS_RECENT |
				      FLAG_NO_CHALLENGE_ACK) > 0;

	if (!acceptable) {
		if (sk->sk_state == TCP_SYN_RECV)
			return 1;	/* send one RST */
		tcp_send_challenge_ack(sk, skb);
		goto discard;
	}
	switch (sk->sk_state) {
	case TCP_SYN_RECV:
		tp->delivered++; /* SYN-ACK delivery isn't tracked in tcp_ack */
		if (!tp->srtt_us)
			tcp_synack_rtt_meas(sk, req);

		if (req) {
			tcp_rcv_synrecv_state_fastopen(sk);
		} else {
			tcp_try_undo_spurious_syn(sk);
			tp->retrans_stamp = 0;
			tcp_init_transfer(sk, BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB);
			WRITE_ONCE(tp->copied_seq, tp->rcv_nxt);
		}
		smp_mb();
		tcp_set_state(sk, TCP_ESTABLISHED);
		sk->sk_state_change(sk);

		/* Note, that this wakeup is only for marginal crossed SYN case.
		 * Passively open sockets are not waked up, because
		 * sk->sk_sleep == NULL and sk->sk_socket == NULL.
		 */
		if (sk->sk_socket)
			sk_wake_async(sk, SOCK_WAKE_IO, POLL_OUT);

		tp->snd_una = TCP_SKB_CB(skb)->ack_seq;
		tp->snd_wnd = ntohs(th->window) << tp->rx_opt.snd_wscale;
		tcp_init_wl(tp, TCP_SKB_CB(skb)->seq);

		if (tp->rx_opt.tstamp_ok)
			tp->advmss -= TCPOLEN_TSTAMP_ALIGNED;

		if (!inet_csk(sk)->icsk_ca_ops->cong_control)
			tcp_update_pacing_rate(sk);

		/* Prevent spurious tcp_cwnd_restart() on first data packet */
		tp->lsndtime = tcp_jiffies32;

		tcp_initialize_rcv_mss(sk);
		tcp_fast_path_on(tp);
		break;

	case TCP_FIN_WAIT1: {
		int tmo;

		if (req)
			tcp_rcv_synrecv_state_fastopen(sk);

		if (tp->snd_una != tp->write_seq)
			break;

		tcp_set_state(sk, TCP_FIN_WAIT2);
		sk->sk_shutdown |= SEND_SHUTDOWN;

		sk_dst_confirm(sk);

		if (!sock_flag(sk, SOCK_DEAD)) {
			/* Wake up lingering close() */
			sk->sk_state_change(sk);
			break;
		}

		if (tp->linger2 < 0) {
			tcp_done(sk);
			NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTONDATA);
			return 1;
		}
		if (TCP_SKB_CB(skb)->end_seq != TCP_SKB_CB(skb)->seq &&
		    after(TCP_SKB_CB(skb)->end_seq - th->fin, tp->rcv_nxt)) {
			/* Receive out of order FIN after close() */
			if (tp->syn_fastopen && th->fin)
				tcp_fastopen_active_disable(sk);
			tcp_done(sk);
			NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTONDATA);
			return 1;
		}

		tmo = tcp_fin_time(sk);
		if (tmo > TCP_TIMEWAIT_LEN) {
			inet_csk_reset_keepalive_timer(sk, tmo - TCP_TIMEWAIT_LEN);
		} else if (th->fin || sock_owned_by_user(sk)) {
			/* Bad case. We could lose such FIN otherwise.
			 * It is not a big problem, but it looks confusing
			 * and not so rare event. We still can lose it now,
			 * if it spins in bh_lock_sock(), but it is really
			 * marginal case.
			 */
			inet_csk_reset_keepalive_timer(sk, tmo);
		} else {
			tcp_time_wait(sk, TCP_FIN_WAIT2, tmo);
			goto discard;
		}
		break;
	}

	case TCP_CLOSING:
		if (tp->snd_una == tp->write_seq) {
			tcp_time_wait(sk, TCP_TIME_WAIT, 0);
			goto discard;
		}
		break;

	case TCP_LAST_ACK:
		if (tp->snd_una == tp->write_seq) {
			tcp_update_metrics(sk);
			tcp_done(sk);
			goto discard;
		}
		break;
	}

	/* step 6: check the URG bit */
	tcp_urg(sk, skb, th);

	/* step 7: process the segment text */
	switch (sk->sk_state) {
	case TCP_CLOSE_WAIT:
	case TCP_CLOSING:
	case TCP_LAST_ACK:
		if (!before(TCP_SKB_CB(skb)->seq, tp->rcv_nxt))
			break;
		/* fall through */
	case TCP_FIN_WAIT1:
	case TCP_FIN_WAIT2:
		/* RFC 793 says to queue data in these states,
		 * RFC 1122 says we MUST send a reset.
		 * BSD 4.4 also does reset.
		 */
		if (sk->sk_shutdown & RCV_SHUTDOWN) {
			if (TCP_SKB_CB(skb)->end_seq != TCP_SKB_CB(skb)->seq &&
			    after(TCP_SKB_CB(skb)->end_seq - th->fin, tp->rcv_nxt)) {
				NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTONDATA);
				tcp_reset(sk);
				return 1;
			}
		}
		/* Fall through */
	case TCP_ESTABLISHED:
		tcp_data_queue(sk, skb);
		queued = 1;
		break;
	}

	/* tcp_data could move socket to TIME-WAIT */
	if (sk->sk_state != TCP_CLOSE) {
		tcp_data_snd_check(sk);
		tcp_ack_snd_check(sk);
	}

	if (!queued) {
discard:
		tcp_drop(sk, skb);
	}
	return 0;
}