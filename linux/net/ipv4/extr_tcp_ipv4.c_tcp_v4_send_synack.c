#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcp_fastopen_cookie {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int dummy; } ;
struct inet_request_sock {int /*<<< orphan*/  ireq_opt; int /*<<< orphan*/  ir_rmt_addr; int /*<<< orphan*/  ir_loc_addr; } ;
struct flowi4 {int dummy; } ;
struct flowi {int dummy; } ;
struct dst_entry {int dummy; } ;
typedef  enum tcp_synack_type { ____Placeholder_tcp_synack_type } tcp_synack_type ;

/* Variables and functions */
 int /*<<< orphan*/  __tcp_v4_send_check (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dst_entry* inet_csk_route_req (struct sock const*,struct flowi4*,struct request_sock*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 int ip_build_and_send_pkt (struct sk_buff*,struct sock const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int net_xmit_eval (int) ; 
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sk_buff* tcp_make_synack (struct sock const*,struct dst_entry*,struct request_sock*,struct tcp_fastopen_cookie*,int) ; 

__attribute__((used)) static int tcp_v4_send_synack(const struct sock *sk, struct dst_entry *dst,
			      struct flowi *fl,
			      struct request_sock *req,
			      struct tcp_fastopen_cookie *foc,
			      enum tcp_synack_type synack_type)
{
	const struct inet_request_sock *ireq = inet_rsk(req);
	struct flowi4 fl4;
	int err = -1;
	struct sk_buff *skb;

	/* First, grab a route. */
	if (!dst && (dst = inet_csk_route_req(sk, &fl4, req)) == NULL)
		return -1;

	skb = tcp_make_synack(sk, dst, req, foc, synack_type);

	if (skb) {
		__tcp_v4_send_check(skb, ireq->ir_loc_addr, ireq->ir_rmt_addr);

		rcu_read_lock();
		err = ip_build_and_send_pkt(skb, sk, ireq->ir_loc_addr,
					    ireq->ir_rmt_addr,
					    rcu_dereference(ireq->ireq_opt));
		rcu_read_unlock();
		err = net_xmit_eval(err);
	}

	return err;
}