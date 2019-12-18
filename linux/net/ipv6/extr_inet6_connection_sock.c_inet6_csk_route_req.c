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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int /*<<< orphan*/  sk_uid; } ;
struct request_sock {int dummy; } ;
struct ipv6_pinfo {int /*<<< orphan*/  opt; } ;
struct inet_request_sock {int /*<<< orphan*/  ir_num; int /*<<< orphan*/  ir_rmt_port; int /*<<< orphan*/  ir_mark; int /*<<< orphan*/  ir_iif; int /*<<< orphan*/  ir_v6_loc_addr; int /*<<< orphan*/  ir_v6_rmt_addr; } ;
struct in6_addr {int dummy; } ;
struct flowi6 {int /*<<< orphan*/  flowi6_uid; int /*<<< orphan*/  fl6_sport; int /*<<< orphan*/  fl6_dport; int /*<<< orphan*/  flowi6_mark; int /*<<< orphan*/  flowi6_oif; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi6_proto; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dst_entry*) ; 
 struct in6_addr* fl6_update_dst (struct flowi6*,int /*<<< orphan*/ ,struct in6_addr*) ; 
 int /*<<< orphan*/  flowi6_to_flowi (struct flowi6*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct ipv6_pinfo* inet6_sk (struct sock const*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock const*) ; 
 struct dst_entry* ip6_dst_lookup_flow (struct sock const*,struct flowi6*,struct in6_addr*) ; 
 int /*<<< orphan*/  memset (struct flowi6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  security_req_classify_flow (struct request_sock const*,int /*<<< orphan*/ ) ; 

struct dst_entry *inet6_csk_route_req(const struct sock *sk,
				      struct flowi6 *fl6,
				      const struct request_sock *req,
				      u8 proto)
{
	struct inet_request_sock *ireq = inet_rsk(req);
	const struct ipv6_pinfo *np = inet6_sk(sk);
	struct in6_addr *final_p, final;
	struct dst_entry *dst;

	memset(fl6, 0, sizeof(*fl6));
	fl6->flowi6_proto = proto;
	fl6->daddr = ireq->ir_v6_rmt_addr;
	rcu_read_lock();
	final_p = fl6_update_dst(fl6, rcu_dereference(np->opt), &final);
	rcu_read_unlock();
	fl6->saddr = ireq->ir_v6_loc_addr;
	fl6->flowi6_oif = ireq->ir_iif;
	fl6->flowi6_mark = ireq->ir_mark;
	fl6->fl6_dport = ireq->ir_rmt_port;
	fl6->fl6_sport = htons(ireq->ir_num);
	fl6->flowi6_uid = sk->sk_uid;
	security_req_classify_flow(req, flowi6_to_flowi(fl6));

	dst = ip6_dst_lookup_flow(sk, fl6, final_p);
	if (IS_ERR(dst))
		return NULL;

	return dst;
}