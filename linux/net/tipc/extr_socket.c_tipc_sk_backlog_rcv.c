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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dupl_rcvcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  atomic_add (unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int sk_rmem_alloc_get (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tipc_node_distr_xmit (int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 TYPE_1__* tipc_sk (struct sock*) ; 
 int /*<<< orphan*/  tipc_sk_filter_rcv (struct sock*,struct sk_buff*,struct sk_buff_head*) ; 

__attribute__((used)) static int tipc_sk_backlog_rcv(struct sock *sk, struct sk_buff *skb)
{
	unsigned int before = sk_rmem_alloc_get(sk);
	struct sk_buff_head xmitq;
	unsigned int added;

	__skb_queue_head_init(&xmitq);

	tipc_sk_filter_rcv(sk, skb, &xmitq);
	added = sk_rmem_alloc_get(sk) - before;
	atomic_add(added, &tipc_sk(sk)->dupl_rcvcnt);

	/* Send pending response/rejected messages, if any */
	tipc_node_distr_xmit(sock_net(sk), &xmitq);
	return 0;
}