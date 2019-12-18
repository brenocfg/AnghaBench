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
typedef  int /*<<< orphan*/  u32 ;
struct tcphdr {int /*<<< orphan*/  seq; int /*<<< orphan*/  source; int /*<<< orphan*/  dest; } ;
struct tcp_sock {scalar_t__ tcp_mstamp; int /*<<< orphan*/  srtt_us; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  mtu_info; int /*<<< orphan*/  snd_nxt; int /*<<< orphan*/  fastopen_rsk; } ;
struct sock {int sk_state; int sk_err; int sk_err_soft; int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;int /*<<< orphan*/  sk_tsq_flags; } ;
struct sk_buff {int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct request_sock {int /*<<< orphan*/  sk; } ;
struct net {int dummy; } ;
struct iphdr {int ihl; scalar_t__ ttl; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct inet_sock {scalar_t__ min_ttl; scalar_t__ recverr; } ;
struct inet_connection_sock {scalar_t__ icsk_rto; int /*<<< orphan*/  icsk_backoff; int /*<<< orphan*/  icsk_retransmits; } ;
typedef  scalar_t__ s32 ;
struct TYPE_6__ {int errno; } ;
struct TYPE_5__ {int type; int code; } ;
struct TYPE_4__ {int /*<<< orphan*/  snt_isn; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int ENOENT ; 
 int EPROTO ; 
#define  ICMP_DEST_UNREACH 134 
 int const ICMP_FRAG_NEEDED ; 
 int const ICMP_HOST_UNREACH ; 
 int /*<<< orphan*/  ICMP_MIB_INERRORS ; 
 int const ICMP_NET_UNREACH ; 
#define  ICMP_PARAMETERPROB 133 
#define  ICMP_REDIRECT 132 
#define  ICMP_SOURCE_QUENCH 131 
#define  ICMP_TIME_EXCEEDED 130 
 int /*<<< orphan*/  ICSK_TIME_RETRANS ; 
 int /*<<< orphan*/  LINUX_MIB_LOCKDROPPEDICMPS ; 
 int /*<<< orphan*/  LINUX_MIB_OUTOFWINDOWICMPS ; 
 int /*<<< orphan*/  LINUX_MIB_TCPMINTTLDROP ; 
 int const NR_ICMP_UNREACH ; 
 int TCP_CLOSE ; 
 int TCP_LISTEN ; 
 int /*<<< orphan*/  TCP_MTU_REDUCED_DEFERRED ; 
 int TCP_NEW_SYN_RECV ; 
 int /*<<< orphan*/  TCP_RTO_MAX ; 
#define  TCP_SYN_RECV 129 
#define  TCP_SYN_SENT 128 
 scalar_t__ TCP_TIMEOUT_INIT ; 
 int TCP_TIME_WAIT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __ICMP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __NET_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 struct sock* __inet_lookup_established (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __tcp_set_rto (struct tcp_sock*) ; 
 int /*<<< orphan*/  between (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_redirect (struct sk_buff*,struct sock*) ; 
 TYPE_3__* icmp_err_convert ; 
 TYPE_2__* icmp_hdr (struct sk_buff*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ inet_csk_rto_backoff (struct inet_connection_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_iif (struct sk_buff*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  inet_twsk (struct sock*) ; 
 int /*<<< orphan*/  inet_twsk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct request_sock* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  tcp_done (struct sock*) ; 
 int /*<<< orphan*/  tcp_hashinfo ; 
 int /*<<< orphan*/  tcp_mstamp_refresh (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_req_err (struct sock*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_retransmit_timer (struct sock*) ; 
 TYPE_1__* tcp_rsk (struct request_sock*) ; 
 struct sk_buff* tcp_rtx_queue_head (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_skb_timestamp_us (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v4_mtu_reduced (struct sock*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ usecs_to_jiffies (int /*<<< orphan*/ ) ; 

int tcp_v4_err(struct sk_buff *icmp_skb, u32 info)
{
	const struct iphdr *iph = (const struct iphdr *)icmp_skb->data;
	struct tcphdr *th = (struct tcphdr *)(icmp_skb->data + (iph->ihl << 2));
	struct inet_connection_sock *icsk;
	struct tcp_sock *tp;
	struct inet_sock *inet;
	const int type = icmp_hdr(icmp_skb)->type;
	const int code = icmp_hdr(icmp_skb)->code;
	struct sock *sk;
	struct sk_buff *skb;
	struct request_sock *fastopen;
	u32 seq, snd_una;
	s32 remaining;
	u32 delta_us;
	int err;
	struct net *net = dev_net(icmp_skb->dev);

	sk = __inet_lookup_established(net, &tcp_hashinfo, iph->daddr,
				       th->dest, iph->saddr, ntohs(th->source),
				       inet_iif(icmp_skb), 0);
	if (!sk) {
		__ICMP_INC_STATS(net, ICMP_MIB_INERRORS);
		return -ENOENT;
	}
	if (sk->sk_state == TCP_TIME_WAIT) {
		inet_twsk_put(inet_twsk(sk));
		return 0;
	}
	seq = ntohl(th->seq);
	if (sk->sk_state == TCP_NEW_SYN_RECV) {
		tcp_req_err(sk, seq, type == ICMP_PARAMETERPROB ||
				     type == ICMP_TIME_EXCEEDED ||
				     (type == ICMP_DEST_UNREACH &&
				      (code == ICMP_NET_UNREACH ||
				       code == ICMP_HOST_UNREACH)));
		return 0;
	}

	bh_lock_sock(sk);
	/* If too many ICMPs get dropped on busy
	 * servers this needs to be solved differently.
	 * We do take care of PMTU discovery (RFC1191) special case :
	 * we can receive locally generated ICMP messages while socket is held.
	 */
	if (sock_owned_by_user(sk)) {
		if (!(type == ICMP_DEST_UNREACH && code == ICMP_FRAG_NEEDED))
			__NET_INC_STATS(net, LINUX_MIB_LOCKDROPPEDICMPS);
	}
	if (sk->sk_state == TCP_CLOSE)
		goto out;

	if (unlikely(iph->ttl < inet_sk(sk)->min_ttl)) {
		__NET_INC_STATS(net, LINUX_MIB_TCPMINTTLDROP);
		goto out;
	}

	icsk = inet_csk(sk);
	tp = tcp_sk(sk);
	/* XXX (TFO) - tp->snd_una should be ISN (tcp_create_openreq_child() */
	fastopen = rcu_dereference(tp->fastopen_rsk);
	snd_una = fastopen ? tcp_rsk(fastopen)->snt_isn : tp->snd_una;
	if (sk->sk_state != TCP_LISTEN &&
	    !between(seq, snd_una, tp->snd_nxt)) {
		__NET_INC_STATS(net, LINUX_MIB_OUTOFWINDOWICMPS);
		goto out;
	}

	switch (type) {
	case ICMP_REDIRECT:
		if (!sock_owned_by_user(sk))
			do_redirect(icmp_skb, sk);
		goto out;
	case ICMP_SOURCE_QUENCH:
		/* Just silently ignore these. */
		goto out;
	case ICMP_PARAMETERPROB:
		err = EPROTO;
		break;
	case ICMP_DEST_UNREACH:
		if (code > NR_ICMP_UNREACH)
			goto out;

		if (code == ICMP_FRAG_NEEDED) { /* PMTU discovery (RFC1191) */
			/* We are not interested in TCP_LISTEN and open_requests
			 * (SYN-ACKs send out by Linux are always <576bytes so
			 * they should go through unfragmented).
			 */
			if (sk->sk_state == TCP_LISTEN)
				goto out;

			tp->mtu_info = info;
			if (!sock_owned_by_user(sk)) {
				tcp_v4_mtu_reduced(sk);
			} else {
				if (!test_and_set_bit(TCP_MTU_REDUCED_DEFERRED, &sk->sk_tsq_flags))
					sock_hold(sk);
			}
			goto out;
		}

		err = icmp_err_convert[code].errno;
		/* check if icmp_skb allows revert of backoff
		 * (see draft-zimmermann-tcp-lcd) */
		if (code != ICMP_NET_UNREACH && code != ICMP_HOST_UNREACH)
			break;
		if (seq != tp->snd_una  || !icsk->icsk_retransmits ||
		    !icsk->icsk_backoff || fastopen)
			break;

		if (sock_owned_by_user(sk))
			break;

		skb = tcp_rtx_queue_head(sk);
		if (WARN_ON_ONCE(!skb))
			break;

		icsk->icsk_backoff--;
		icsk->icsk_rto = tp->srtt_us ? __tcp_set_rto(tp) :
					       TCP_TIMEOUT_INIT;
		icsk->icsk_rto = inet_csk_rto_backoff(icsk, TCP_RTO_MAX);


		tcp_mstamp_refresh(tp);
		delta_us = (u32)(tp->tcp_mstamp - tcp_skb_timestamp_us(skb));
		remaining = icsk->icsk_rto -
			    usecs_to_jiffies(delta_us);

		if (remaining > 0) {
			inet_csk_reset_xmit_timer(sk, ICSK_TIME_RETRANS,
						  remaining, TCP_RTO_MAX);
		} else {
			/* RTO revert clocked out retransmission.
			 * Will retransmit now */
			tcp_retransmit_timer(sk);
		}

		break;
	case ICMP_TIME_EXCEEDED:
		err = EHOSTUNREACH;
		break;
	default:
		goto out;
	}

	switch (sk->sk_state) {
	case TCP_SYN_SENT:
	case TCP_SYN_RECV:
		/* Only in fast or simultaneous open. If a fast open socket is
		 * is already accepted it is treated as a connected one below.
		 */
		if (fastopen && !fastopen->sk)
			break;

		if (!sock_owned_by_user(sk)) {
			sk->sk_err = err;

			sk->sk_error_report(sk);

			tcp_done(sk);
		} else {
			sk->sk_err_soft = err;
		}
		goto out;
	}

	/* If we've already connected we will keep trying
	 * until we time out, or the user gives up.
	 *
	 * rfc1122 4.2.3.9 allows to consider as hard errors
	 * only PROTO_UNREACH and PORT_UNREACH (well, FRAG_FAILED too,
	 * but it is obsoleted by pmtu discovery).
	 *
	 * Note, that in modern internet, where routing is unreliable
	 * and in each dark corner broken firewalls sit, sending random
	 * errors ordered by their masters even this two messages finally lose
	 * their original sense (even Linux sends invalid PORT_UNREACHs)
	 *
	 * Now we are in compliance with RFCs.
	 *							--ANK (980905)
	 */

	inet = inet_sk(sk);
	if (!sock_owned_by_user(sk) && inet->recverr) {
		sk->sk_err = err;
		sk->sk_error_report(sk);
	} else	{ /* Only an error on timeout */
		sk->sk_err_soft = err;
	}

out:
	bh_unlock_sock(sk);
	sock_put(sk);
	return 0;
}