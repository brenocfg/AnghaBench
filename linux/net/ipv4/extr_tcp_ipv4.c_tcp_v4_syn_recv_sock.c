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
typedef  union tcp_md5_addr {int dummy; } tcp_md5_addr ;
struct tcp_sock {int /*<<< orphan*/  advmss; } ;
struct tcp_md5sig_key {int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;
typedef  struct sock {int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_gso_type; } const sock ;
struct sk_buff {int dummy; } ;
struct request_sock {int dummy; } ;
struct TYPE_4__ {scalar_t__ optlen; } ;
struct ip_options_rcu {TYPE_1__ opt; } ;
struct inet_sock {int /*<<< orphan*/ * inet_opt; int /*<<< orphan*/  inet_daddr; int /*<<< orphan*/  inet_id; int /*<<< orphan*/  rcv_tos; int /*<<< orphan*/  mc_ttl; int /*<<< orphan*/  mc_index; int /*<<< orphan*/  inet_saddr; } ;
struct inet_request_sock {int /*<<< orphan*/ * ireq_opt; int /*<<< orphan*/  ir_loc_addr; int /*<<< orphan*/  ir_iif; int /*<<< orphan*/  ir_rmt_addr; } ;
struct dst_entry {int dummy; } ;
struct TYPE_6__ {scalar_t__ icsk_ext_hdr_len; } ;
struct TYPE_5__ {int /*<<< orphan*/  tos; int /*<<< orphan*/  ttl; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LINUX_MIB_LISTENOVERFLOWS ; 
 int /*<<< orphan*/  NETIF_F_GSO_MASK ; 
 int /*<<< orphan*/  NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ *,struct ip_options_rcu*) ; 
 int /*<<< orphan*/  SKB_GSO_TCPV4 ; 
 scalar_t__ __inet_inherit_port (struct sock const*,struct sock const*) ; 
 int /*<<< orphan*/  dst_metric_advmss (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 TYPE_3__* inet_csk (struct sock const*) ; 
 int /*<<< orphan*/  inet_csk_prepare_forced_close (struct sock const*) ; 
 struct dst_entry* inet_csk_route_child_sock (struct sock const*,struct sock const*,struct request_sock*) ; 
 int inet_ehash_nolisten (struct sock const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_iif (struct sk_buff*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 struct inet_sock* inet_sk (struct sock const*) ; 
 int /*<<< orphan*/  inet_sk_rx_dst_set (struct sock const*,struct sk_buff*) ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  prandom_u32 () ; 
 struct ip_options_rcu* rcu_dereference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  req_to_sk (struct request_sock*) ; 
 scalar_t__ sk_acceptq_is_full (struct sock const*) ; 
 int /*<<< orphan*/  sk_daddr_set (struct sock const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_nocaps_add (struct sock const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_rcv_saddr_set (struct sock const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_setup_caps (struct sock const*,struct dst_entry*) ; 
 int /*<<< orphan*/  sock_net (struct sock const*) ; 
 int /*<<< orphan*/  tcp_ca_openreq_child (struct sock const*,struct dst_entry*) ; 
 struct sock const* tcp_create_openreq_child (struct sock const*,struct request_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_done (struct sock const*) ; 
 int /*<<< orphan*/  tcp_initialize_rcv_mss (struct sock const*) ; 
 int /*<<< orphan*/  tcp_listendrop (struct sock const*) ; 
 int /*<<< orphan*/  tcp_md5_do_add (struct sock const*,union tcp_md5_addr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcp_md5sig_key* tcp_md5_do_lookup (struct sock const*,union tcp_md5_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_move_syn (struct tcp_sock*,struct request_sock*) ; 
 int /*<<< orphan*/  tcp_mss_clamp (struct tcp_sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock const*) ; 
 int /*<<< orphan*/  tcp_sync_mss (struct sock const*,int /*<<< orphan*/ ) ; 

struct sock *tcp_v4_syn_recv_sock(const struct sock *sk, struct sk_buff *skb,
				  struct request_sock *req,
				  struct dst_entry *dst,
				  struct request_sock *req_unhash,
				  bool *own_req)
{
	struct inet_request_sock *ireq;
	struct inet_sock *newinet;
	struct tcp_sock *newtp;
	struct sock *newsk;
#ifdef CONFIG_TCP_MD5SIG
	struct tcp_md5sig_key *key;
#endif
	struct ip_options_rcu *inet_opt;

	if (sk_acceptq_is_full(sk))
		goto exit_overflow;

	newsk = tcp_create_openreq_child(sk, req, skb);
	if (!newsk)
		goto exit_nonewsk;

	newsk->sk_gso_type = SKB_GSO_TCPV4;
	inet_sk_rx_dst_set(newsk, skb);

	newtp		      = tcp_sk(newsk);
	newinet		      = inet_sk(newsk);
	ireq		      = inet_rsk(req);
	sk_daddr_set(newsk, ireq->ir_rmt_addr);
	sk_rcv_saddr_set(newsk, ireq->ir_loc_addr);
	newsk->sk_bound_dev_if = ireq->ir_iif;
	newinet->inet_saddr   = ireq->ir_loc_addr;
	inet_opt	      = rcu_dereference(ireq->ireq_opt);
	RCU_INIT_POINTER(newinet->inet_opt, inet_opt);
	newinet->mc_index     = inet_iif(skb);
	newinet->mc_ttl	      = ip_hdr(skb)->ttl;
	newinet->rcv_tos      = ip_hdr(skb)->tos;
	inet_csk(newsk)->icsk_ext_hdr_len = 0;
	if (inet_opt)
		inet_csk(newsk)->icsk_ext_hdr_len = inet_opt->opt.optlen;
	newinet->inet_id = prandom_u32();

	if (!dst) {
		dst = inet_csk_route_child_sock(sk, newsk, req);
		if (!dst)
			goto put_and_exit;
	} else {
		/* syncookie case : see end of cookie_v4_check() */
	}
	sk_setup_caps(newsk, dst);

	tcp_ca_openreq_child(newsk, dst);

	tcp_sync_mss(newsk, dst_mtu(dst));
	newtp->advmss = tcp_mss_clamp(tcp_sk(sk), dst_metric_advmss(dst));

	tcp_initialize_rcv_mss(newsk);

#ifdef CONFIG_TCP_MD5SIG
	/* Copy over the MD5 key from the original socket */
	key = tcp_md5_do_lookup(sk, (union tcp_md5_addr *)&newinet->inet_daddr,
				AF_INET);
	if (key) {
		/*
		 * We're using one, so create a matching key
		 * on the newsk structure. If we fail to get
		 * memory, then we end up not copying the key
		 * across. Shucks.
		 */
		tcp_md5_do_add(newsk, (union tcp_md5_addr *)&newinet->inet_daddr,
			       AF_INET, 32, key->key, key->keylen, GFP_ATOMIC);
		sk_nocaps_add(newsk, NETIF_F_GSO_MASK);
	}
#endif

	if (__inet_inherit_port(sk, newsk) < 0)
		goto put_and_exit;
	*own_req = inet_ehash_nolisten(newsk, req_to_sk(req_unhash));
	if (likely(*own_req)) {
		tcp_move_syn(newtp, req);
		ireq->ireq_opt = NULL;
	} else {
		newinet->inet_opt = NULL;
	}
	return newsk;

exit_overflow:
	NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENOVERFLOWS);
exit_nonewsk:
	dst_release(dst);
exit:
	tcp_listendrop(sk);
	return NULL;
put_and_exit:
	newinet->inet_opt = NULL;
	inet_csk_prepare_forced_close(newsk);
	tcp_done(newsk);
	goto exit;
}