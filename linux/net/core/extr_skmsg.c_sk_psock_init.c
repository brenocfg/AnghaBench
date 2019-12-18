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
struct sock {int dummy; } ;
struct sk_psock {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  ingress_skb; int /*<<< orphan*/  ingress_msg; int /*<<< orphan*/  work; int /*<<< orphan*/  link_lock; int /*<<< orphan*/  link; int /*<<< orphan*/  eval; struct sock* sk; } ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SK_PSOCK_TX_ENABLED ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  __SK_NONE ; 
 struct sk_psock* kzalloc_node (int,int,int) ; 
 int /*<<< orphan*/  rcu_assign_sk_user_data (struct sock*,struct sk_psock*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sk_psock_backlog ; 
 int /*<<< orphan*/  sk_psock_set_state (struct sk_psock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct sk_psock *sk_psock_init(struct sock *sk, int node)
{
	struct sk_psock *psock = kzalloc_node(sizeof(*psock),
					      GFP_ATOMIC | __GFP_NOWARN,
					      node);
	if (!psock)
		return NULL;

	psock->sk = sk;
	psock->eval =  __SK_NONE;

	INIT_LIST_HEAD(&psock->link);
	spin_lock_init(&psock->link_lock);

	INIT_WORK(&psock->work, sk_psock_backlog);
	INIT_LIST_HEAD(&psock->ingress_msg);
	skb_queue_head_init(&psock->ingress_skb);

	sk_psock_set_state(psock, SK_PSOCK_TX_ENABLED);
	refcount_set(&psock->refcnt, 1);

	rcu_assign_sk_user_data(sk, psock);
	sock_hold(sk);

	return psock;
}