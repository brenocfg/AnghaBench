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
struct smap_psock {int /*<<< orphan*/  maps_lock; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  ingress; int /*<<< orphan*/  maps; int /*<<< orphan*/  gc_work; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  rxqueue; struct sock* sock; int /*<<< orphan*/  eval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct smap_psock* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  __SK_NONE ; 
 struct smap_psock* kzalloc_node (int,int,int) ; 
 int /*<<< orphan*/  rcu_assign_sk_user_data (struct sock*,struct smap_psock*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smap_gc_work ; 
 int /*<<< orphan*/  smap_tx_work ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct smap_psock *smap_init_psock(struct sock *sock, int node)
{
	struct smap_psock *psock;

	psock = kzalloc_node(sizeof(struct smap_psock),
			     GFP_ATOMIC | __GFP_NOWARN,
			     node);
	if (!psock)
		return ERR_PTR(-ENOMEM);

	psock->eval =  __SK_NONE;
	psock->sock = sock;
	skb_queue_head_init(&psock->rxqueue);
	INIT_WORK(&psock->tx_work, smap_tx_work);
	INIT_WORK(&psock->gc_work, smap_gc_work);
	INIT_LIST_HEAD(&psock->maps);
	INIT_LIST_HEAD(&psock->ingress);
	refcount_set(&psock->refcnt, 1);
	spin_lock_init(&psock->maps_lock);

	rcu_assign_sk_user_data(sock, psock);
	sock_hold(sock);
	return psock;
}