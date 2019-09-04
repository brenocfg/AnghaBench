#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct cxgbit_sock {int /*<<< orphan*/  waitq; TYPE_1__ rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_tail (TYPE_1__*,struct sk_buff*) ; 
 int skb_queue_len (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cxgbit_queue_lro_skb(struct cxgbit_sock *csk, struct sk_buff *skb)
{
	bool wakeup_thread = false;

	spin_lock(&csk->rxq.lock);
	__skb_queue_tail(&csk->rxq, skb);
	if (skb_queue_len(&csk->rxq) == 1)
		wakeup_thread = true;
	spin_unlock(&csk->rxq.lock);

	if (wakeup_thread)
		wake_up(&csk->waitq);
}