#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tcphdr {int doff; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {scalar_t__ pkt_type; int /*<<< orphan*/ * dev; scalar_t__ data; } ;
struct request_sock {struct sock* rsk_listener; } ;
struct net {int dummy; } ;
struct ipv6hdr {scalar_t__ hop_limit; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct inet_timewait_sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ min_hopcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  LINUX_MIB_TCPMINTTLDROP ; 
 scalar_t__ PACKET_HOST ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  TCP_MIB_CSUMERRORS ; 
 int /*<<< orphan*/  TCP_MIB_INERRS ; 
 int /*<<< orphan*/  TCP_MIB_INSEGS ; 
 scalar_t__ TCP_NEW_SYN_RECV ; 
 scalar_t__ TCP_TIME_WAIT ; 
#define  TCP_TW_ACK 131 
#define  TCP_TW_RST 130 
#define  TCP_TW_SUCCESS 129 
#define  TCP_TW_SYN 128 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 int /*<<< orphan*/  __NET_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __TCP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 struct sock* __inet6_lookup_skb (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  __tcp_hdrlen (struct tcphdr const*) ; 
 int /*<<< orphan*/  bh_lock_sock_nested (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct net* dev_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet6_iif (struct sk_buff*) ; 
 struct sock* inet6_lookup_listener (struct net*,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int inet6_sdif (struct sk_buff*) ; 
 TYPE_1__* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reqsk_queue_drop_and_put (struct sock*,struct request_sock*) ; 
 struct request_sock* inet_reqsk (struct sock*) ; 
 struct inet_timewait_sock* inet_twsk (struct sock*) ; 
 int /*<<< orphan*/  inet_twsk_deschedule_put (struct inet_timewait_sock*) ; 
 int /*<<< orphan*/  inet_twsk_put (struct inet_timewait_sock*) ; 
 int /*<<< orphan*/  ip6_compute_pseudo ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  reqsk_put (struct request_sock*) ; 
 int /*<<< orphan*/  sk_drops_add (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sk_incoming_cpu_update (struct sock*) ; 
 scalar_t__ skb_checksum_init (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 scalar_t__ tcp_add_backlog (struct sock*,struct sk_buff*) ; 
 struct sock* tcp_check_req (struct sock*,struct sk_buff*,struct request_sock*,int,int*) ; 
 scalar_t__ tcp_checksum_complete (struct sk_buff*) ; 
 scalar_t__ tcp_child_process (struct sock*,struct sock*,struct sk_buff*) ; 
 scalar_t__ tcp_filter (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_hashinfo ; 
 int /*<<< orphan*/  tcp_segs_in (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_sk (struct sock*) ; 
 int tcp_timewait_state_process (struct inet_timewait_sock*,struct sk_buff*,struct tcphdr const*) ; 
 int tcp_v6_do_rcv (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v6_fill_cb (struct sk_buff*,struct ipv6hdr const*,struct tcphdr const*) ; 
 int /*<<< orphan*/  tcp_v6_iif_l3_slave (struct sk_buff*) ; 
 scalar_t__ tcp_v6_inbound_md5_hash (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v6_restore_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v6_send_reset (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v6_timewait_ack (struct sock*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xfrm6_policy_check (struct sock*,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int tcp_v6_rcv(struct sk_buff *skb)
{
	int sdif = inet6_sdif(skb);
	const struct tcphdr *th;
	const struct ipv6hdr *hdr;
	bool refcounted;
	struct sock *sk;
	int ret;
	struct net *net = dev_net(skb->dev);

	if (skb->pkt_type != PACKET_HOST)
		goto discard_it;

	/*
	 *	Count it even if it's bad.
	 */
	__TCP_INC_STATS(net, TCP_MIB_INSEGS);

	if (!pskb_may_pull(skb, sizeof(struct tcphdr)))
		goto discard_it;

	th = (const struct tcphdr *)skb->data;

	if (unlikely(th->doff < sizeof(struct tcphdr)/4))
		goto bad_packet;
	if (!pskb_may_pull(skb, th->doff*4))
		goto discard_it;

	if (skb_checksum_init(skb, IPPROTO_TCP, ip6_compute_pseudo))
		goto csum_error;

	th = (const struct tcphdr *)skb->data;
	hdr = ipv6_hdr(skb);

lookup:
	sk = __inet6_lookup_skb(&tcp_hashinfo, skb, __tcp_hdrlen(th),
				th->source, th->dest, inet6_iif(skb), sdif,
				&refcounted);
	if (!sk)
		goto no_tcp_socket;

process:
	if (sk->sk_state == TCP_TIME_WAIT)
		goto do_time_wait;

	if (sk->sk_state == TCP_NEW_SYN_RECV) {
		struct request_sock *req = inet_reqsk(sk);
		bool req_stolen = false;
		struct sock *nsk;

		sk = req->rsk_listener;
		if (tcp_v6_inbound_md5_hash(sk, skb)) {
			sk_drops_add(sk, skb);
			reqsk_put(req);
			goto discard_it;
		}
		if (tcp_checksum_complete(skb)) {
			reqsk_put(req);
			goto csum_error;
		}
		if (unlikely(sk->sk_state != TCP_LISTEN)) {
			inet_csk_reqsk_queue_drop_and_put(sk, req);
			goto lookup;
		}
		sock_hold(sk);
		refcounted = true;
		nsk = NULL;
		if (!tcp_filter(sk, skb)) {
			th = (const struct tcphdr *)skb->data;
			hdr = ipv6_hdr(skb);
			tcp_v6_fill_cb(skb, hdr, th);
			nsk = tcp_check_req(sk, skb, req, false, &req_stolen);
		}
		if (!nsk) {
			reqsk_put(req);
			if (req_stolen) {
				/* Another cpu got exclusive access to req
				 * and created a full blown socket.
				 * Try to feed this packet to this socket
				 * instead of discarding it.
				 */
				tcp_v6_restore_cb(skb);
				sock_put(sk);
				goto lookup;
			}
			goto discard_and_relse;
		}
		if (nsk == sk) {
			reqsk_put(req);
			tcp_v6_restore_cb(skb);
		} else if (tcp_child_process(sk, nsk, skb)) {
			tcp_v6_send_reset(nsk, skb);
			goto discard_and_relse;
		} else {
			sock_put(sk);
			return 0;
		}
	}
	if (hdr->hop_limit < inet6_sk(sk)->min_hopcount) {
		__NET_INC_STATS(net, LINUX_MIB_TCPMINTTLDROP);
		goto discard_and_relse;
	}

	if (!xfrm6_policy_check(sk, XFRM_POLICY_IN, skb))
		goto discard_and_relse;

	if (tcp_v6_inbound_md5_hash(sk, skb))
		goto discard_and_relse;

	if (tcp_filter(sk, skb))
		goto discard_and_relse;
	th = (const struct tcphdr *)skb->data;
	hdr = ipv6_hdr(skb);
	tcp_v6_fill_cb(skb, hdr, th);

	skb->dev = NULL;

	if (sk->sk_state == TCP_LISTEN) {
		ret = tcp_v6_do_rcv(sk, skb);
		goto put_and_return;
	}

	sk_incoming_cpu_update(sk);

	bh_lock_sock_nested(sk);
	tcp_segs_in(tcp_sk(sk), skb);
	ret = 0;
	if (!sock_owned_by_user(sk)) {
		ret = tcp_v6_do_rcv(sk, skb);
	} else if (tcp_add_backlog(sk, skb)) {
		goto discard_and_relse;
	}
	bh_unlock_sock(sk);

put_and_return:
	if (refcounted)
		sock_put(sk);
	return ret ? -1 : 0;

no_tcp_socket:
	if (!xfrm6_policy_check(NULL, XFRM_POLICY_IN, skb))
		goto discard_it;

	tcp_v6_fill_cb(skb, hdr, th);

	if (tcp_checksum_complete(skb)) {
csum_error:
		__TCP_INC_STATS(net, TCP_MIB_CSUMERRORS);
bad_packet:
		__TCP_INC_STATS(net, TCP_MIB_INERRS);
	} else {
		tcp_v6_send_reset(NULL, skb);
	}

discard_it:
	kfree_skb(skb);
	return 0;

discard_and_relse:
	sk_drops_add(sk, skb);
	if (refcounted)
		sock_put(sk);
	goto discard_it;

do_time_wait:
	if (!xfrm6_policy_check(NULL, XFRM_POLICY_IN, skb)) {
		inet_twsk_put(inet_twsk(sk));
		goto discard_it;
	}

	tcp_v6_fill_cb(skb, hdr, th);

	if (tcp_checksum_complete(skb)) {
		inet_twsk_put(inet_twsk(sk));
		goto csum_error;
	}

	switch (tcp_timewait_state_process(inet_twsk(sk), skb, th)) {
	case TCP_TW_SYN:
	{
		struct sock *sk2;

		sk2 = inet6_lookup_listener(dev_net(skb->dev), &tcp_hashinfo,
					    skb, __tcp_hdrlen(th),
					    &ipv6_hdr(skb)->saddr, th->source,
					    &ipv6_hdr(skb)->daddr,
					    ntohs(th->dest),
					    tcp_v6_iif_l3_slave(skb),
					    sdif);
		if (sk2) {
			struct inet_timewait_sock *tw = inet_twsk(sk);
			inet_twsk_deschedule_put(tw);
			sk = sk2;
			tcp_v6_restore_cb(skb);
			refcounted = false;
			goto process;
		}
	}
		/* to ACK */
		/* fall through */
	case TCP_TW_ACK:
		tcp_v6_timewait_ack(sk, skb);
		break;
	case TCP_TW_RST:
		tcp_v6_send_reset(sk, skb);
		inet_twsk_deschedule_put(inet_twsk(sk));
		goto discard_it;
	case TCP_TW_SUCCESS:
		;
	}
	goto discard_it;
}