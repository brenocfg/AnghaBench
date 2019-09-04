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
struct sock {int /*<<< orphan*/  sk_uid; int /*<<< orphan*/  sk_protocol; } ;
struct dst_entry {int dummy; } ;
struct rtable {struct dst_entry dst; scalar_t__ rt_uses_gateway; } ;
struct request_sock {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {scalar_t__ is_strictroute; int /*<<< orphan*/  faddr; scalar_t__ srr; } ;
struct ip_options_rcu {TYPE_1__ opt; } ;
struct inet_request_sock {int /*<<< orphan*/  ir_num; int /*<<< orphan*/  ir_rmt_port; int /*<<< orphan*/  ir_loc_addr; int /*<<< orphan*/  ir_rmt_addr; int /*<<< orphan*/  ir_mark; int /*<<< orphan*/  ir_iif; int /*<<< orphan*/  ireq_opt; int /*<<< orphan*/  ireq_net; } ;
struct flowi4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSTATS_MIB_OUTNOROUTES ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  RT_CONN_FLAGS (struct sock const*) ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int /*<<< orphan*/  __IP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flowi4_init_output (struct flowi4*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flowi4_to_flowi (struct flowi4*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct inet_request_sock* inet_rsk (struct request_sock const*) ; 
 int /*<<< orphan*/  inet_sk_flowi_flags (struct sock const*) ; 
 struct rtable* ip_route_output_flow (struct net*,struct flowi4*,struct sock const*) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 struct ip_options_rcu* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct net* read_pnet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  security_req_classify_flow (struct request_sock const*,int /*<<< orphan*/ ) ; 

struct dst_entry *inet_csk_route_req(const struct sock *sk,
				     struct flowi4 *fl4,
				     const struct request_sock *req)
{
	const struct inet_request_sock *ireq = inet_rsk(req);
	struct net *net = read_pnet(&ireq->ireq_net);
	struct ip_options_rcu *opt;
	struct rtable *rt;

	rcu_read_lock();
	opt = rcu_dereference(ireq->ireq_opt);

	flowi4_init_output(fl4, ireq->ir_iif, ireq->ir_mark,
			   RT_CONN_FLAGS(sk), RT_SCOPE_UNIVERSE,
			   sk->sk_protocol, inet_sk_flowi_flags(sk),
			   (opt && opt->opt.srr) ? opt->opt.faddr : ireq->ir_rmt_addr,
			   ireq->ir_loc_addr, ireq->ir_rmt_port,
			   htons(ireq->ir_num), sk->sk_uid);
	security_req_classify_flow(req, flowi4_to_flowi(fl4));
	rt = ip_route_output_flow(net, fl4, sk);
	if (IS_ERR(rt))
		goto no_route;
	if (opt && opt->opt.is_strictroute && rt->rt_uses_gateway)
		goto route_err;
	rcu_read_unlock();
	return &rt->dst;

route_err:
	ip_rt_put(rt);
no_route:
	rcu_read_unlock();
	__IP_INC_STATS(net, IPSTATS_MIB_OUTNOROUTES);
	return NULL;
}