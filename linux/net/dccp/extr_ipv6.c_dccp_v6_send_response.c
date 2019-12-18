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
struct sock {int /*<<< orphan*/  sk_priority; int /*<<< orphan*/  sk_mark; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int dummy; } ;
struct ipv6_txoptions {int dummy; } ;
struct ipv6_pinfo {int /*<<< orphan*/  tclass; int /*<<< orphan*/  opt; } ;
struct inet_request_sock {struct ipv6_txoptions* ipv6_opt; int /*<<< orphan*/  ir_v6_rmt_addr; int /*<<< orphan*/  ir_v6_loc_addr; int /*<<< orphan*/  ir_num; int /*<<< orphan*/  ir_rmt_port; int /*<<< orphan*/  ir_iif; } ;
struct in6_addr {int dummy; } ;
struct flowi6 {int /*<<< orphan*/  daddr; int /*<<< orphan*/  fl6_sport; int /*<<< orphan*/  fl6_dport; int /*<<< orphan*/  flowi6_oif; scalar_t__ flowlabel; int /*<<< orphan*/  saddr; int /*<<< orphan*/  flowi6_proto; } ;
struct dst_entry {int dummy; } ;
struct dccp_hdr {int /*<<< orphan*/  dccph_checksum; } ;
typedef  int /*<<< orphan*/  fl6 ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_DCCP ; 
 scalar_t__ IS_ERR (struct dst_entry*) ; 
 int PTR_ERR (struct dst_entry*) ; 
 struct dccp_hdr* dccp_hdr (struct sk_buff*) ; 
 struct sk_buff* dccp_make_response (struct sock const*,struct dst_entry*,struct request_sock*) ; 
 int /*<<< orphan*/  dccp_v6_csum_finish (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 struct in6_addr* fl6_update_dst (struct flowi6*,struct ipv6_txoptions*,struct in6_addr*) ; 
 int /*<<< orphan*/  flowi6_to_flowi (struct flowi6*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct ipv6_pinfo* inet6_sk (struct sock const*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 struct dst_entry* ip6_dst_lookup_flow (struct sock const*,struct flowi6*,struct in6_addr*) ; 
 int ip6_xmit (struct sock const*,struct sk_buff*,struct flowi6*,int /*<<< orphan*/ ,struct ipv6_txoptions*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct flowi6*,int /*<<< orphan*/ ,int) ; 
 int net_xmit_eval (int) ; 
 struct ipv6_txoptions* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  security_req_classify_flow (struct request_sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dccp_v6_send_response(const struct sock *sk, struct request_sock *req)
{
	struct inet_request_sock *ireq = inet_rsk(req);
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct sk_buff *skb;
	struct in6_addr *final_p, final;
	struct flowi6 fl6;
	int err = -1;
	struct dst_entry *dst;

	memset(&fl6, 0, sizeof(fl6));
	fl6.flowi6_proto = IPPROTO_DCCP;
	fl6.daddr = ireq->ir_v6_rmt_addr;
	fl6.saddr = ireq->ir_v6_loc_addr;
	fl6.flowlabel = 0;
	fl6.flowi6_oif = ireq->ir_iif;
	fl6.fl6_dport = ireq->ir_rmt_port;
	fl6.fl6_sport = htons(ireq->ir_num);
	security_req_classify_flow(req, flowi6_to_flowi(&fl6));


	rcu_read_lock();
	final_p = fl6_update_dst(&fl6, rcu_dereference(np->opt), &final);
	rcu_read_unlock();

	dst = ip6_dst_lookup_flow(sk, &fl6, final_p);
	if (IS_ERR(dst)) {
		err = PTR_ERR(dst);
		dst = NULL;
		goto done;
	}

	skb = dccp_make_response(sk, dst, req);
	if (skb != NULL) {
		struct dccp_hdr *dh = dccp_hdr(skb);
		struct ipv6_txoptions *opt;

		dh->dccph_checksum = dccp_v6_csum_finish(skb,
							 &ireq->ir_v6_loc_addr,
							 &ireq->ir_v6_rmt_addr);
		fl6.daddr = ireq->ir_v6_rmt_addr;
		rcu_read_lock();
		opt = ireq->ipv6_opt;
		if (!opt)
			opt = rcu_dereference(np->opt);
		err = ip6_xmit(sk, skb, &fl6, sk->sk_mark, opt, np->tclass,
			       sk->sk_priority);
		rcu_read_unlock();
		err = net_xmit_eval(err);
	}

done:
	dst_release(dst);
	return err;
}