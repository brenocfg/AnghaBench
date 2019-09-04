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
struct sk_buff {int dummy; } ;
struct cxgbit_sock {int /*<<< orphan*/  lro_hskb; int /*<<< orphan*/  skbq; int /*<<< orphan*/  ppodq; int /*<<< orphan*/  backlogq; int /*<<< orphan*/  rxq; int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 struct sk_buff* cxgbit_sock_dequeue_wr (struct cxgbit_sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static void cxgbit_free_skb(struct cxgbit_sock *csk)
{
	struct sk_buff *skb;

	__skb_queue_purge(&csk->txq);
	__skb_queue_purge(&csk->rxq);
	__skb_queue_purge(&csk->backlogq);
	__skb_queue_purge(&csk->ppodq);
	__skb_queue_purge(&csk->skbq);

	while ((skb = cxgbit_sock_dequeue_wr(csk)))
		kfree_skb(skb);

	__kfree_skb(csk->lro_hskb);
}