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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int dummy; } ;
struct inet_sock {int /*<<< orphan*/ * inet_opt; int /*<<< orphan*/  inet_id; int /*<<< orphan*/  mc_ttl; int /*<<< orphan*/  mc_index; int /*<<< orphan*/  inet_saddr; } ;
struct inet_request_sock {int /*<<< orphan*/ * ireq_opt; int /*<<< orphan*/  ir_loc_addr; int /*<<< orphan*/  ir_rmt_addr; } ;
struct dst_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ttl; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_LISTENDROPS ; 
 int /*<<< orphan*/  LINUX_MIB_LISTENOVERFLOWS ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __inet_inherit_port (struct sock const*,struct sock*) ; 
 struct sock* dccp_create_openreq_child (struct sock const*,struct request_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_done (struct sock*) ; 
 int /*<<< orphan*/  dccp_sync_mss (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  inet_csk_prepare_forced_close (struct sock*) ; 
 struct dst_entry* inet_csk_route_child_sock (struct sock const*,struct sock*,struct request_sock*) ; 
 int inet_ehash_nolisten (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_iif (struct sk_buff*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  prandom_u32 () ; 
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  req_to_sk (struct request_sock*) ; 
 scalar_t__ sk_acceptq_is_full (struct sock const*) ; 
 int /*<<< orphan*/  sk_daddr_set (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_rcv_saddr_set (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_setup_caps (struct sock*,struct dst_entry*) ; 
 int /*<<< orphan*/  sock_net (struct sock const*) ; 

struct sock *dccp_v4_request_recv_sock(const struct sock *sk,
				       struct sk_buff *skb,
				       struct request_sock *req,
				       struct dst_entry *dst,
				       struct request_sock *req_unhash,
				       bool *own_req)
{
	struct inet_request_sock *ireq;
	struct inet_sock *newinet;
	struct sock *newsk;

	if (sk_acceptq_is_full(sk))
		goto exit_overflow;

	newsk = dccp_create_openreq_child(sk, req, skb);
	if (newsk == NULL)
		goto exit_nonewsk;

	newinet		   = inet_sk(newsk);
	ireq		   = inet_rsk(req);
	sk_daddr_set(newsk, ireq->ir_rmt_addr);
	sk_rcv_saddr_set(newsk, ireq->ir_loc_addr);
	newinet->inet_saddr	= ireq->ir_loc_addr;
	RCU_INIT_POINTER(newinet->inet_opt, rcu_dereference(ireq->ireq_opt));
	newinet->mc_index  = inet_iif(skb);
	newinet->mc_ttl	   = ip_hdr(skb)->ttl;
	newinet->inet_id   = prandom_u32();

	if (dst == NULL && (dst = inet_csk_route_child_sock(sk, newsk, req)) == NULL)
		goto put_and_exit;

	sk_setup_caps(newsk, dst);

	dccp_sync_mss(newsk, dst_mtu(dst));

	if (__inet_inherit_port(sk, newsk) < 0)
		goto put_and_exit;
	*own_req = inet_ehash_nolisten(newsk, req_to_sk(req_unhash));
	if (*own_req)
		ireq->ireq_opt = NULL;
	else
		newinet->inet_opt = NULL;
	return newsk;

exit_overflow:
	__NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENOVERFLOWS);
exit_nonewsk:
	dst_release(dst);
exit:
	__NET_INC_STATS(sock_net(sk), LINUX_MIB_LISTENDROPS);
	return NULL;
put_and_exit:
	newinet->inet_opt = NULL;
	inet_csk_prepare_forced_close(newsk);
	dccp_done(newsk);
	goto exit;
}