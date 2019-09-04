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
struct net {int dummy; } ;
struct inet_request_sock {int /*<<< orphan*/  ireq_opt; } ;
struct TYPE_2__ {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  req_to_sk (struct request_sock*) ; 
 int /*<<< orphan*/  sk_daddr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_rcv_saddr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* sock_net (struct sock const*) ; 
 int /*<<< orphan*/  tcp_v4_save_options (struct net*,struct sk_buff*) ; 

__attribute__((used)) static void tcp_v4_init_req(struct request_sock *req,
			    const struct sock *sk_listener,
			    struct sk_buff *skb)
{
	struct inet_request_sock *ireq = inet_rsk(req);
	struct net *net = sock_net(sk_listener);

	sk_rcv_saddr_set(req_to_sk(req), ip_hdr(skb)->daddr);
	sk_daddr_set(req_to_sk(req), ip_hdr(skb)->saddr);
	RCU_INIT_POINTER(ireq->ireq_opt, tcp_v4_save_options(net, skb));
}