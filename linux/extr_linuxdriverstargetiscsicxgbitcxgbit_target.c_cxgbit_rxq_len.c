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
struct sk_buff_head {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct cxgbit_sock {TYPE_1__ rxq; } ;

/* Variables and functions */
 scalar_t__ skb_queue_len (TYPE_1__*) ; 
 int /*<<< orphan*/  skb_queue_splice_init (TYPE_1__*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cxgbit_rxq_len(struct cxgbit_sock *csk, struct sk_buff_head *rxq)
{
	spin_lock_bh(&csk->rxq.lock);
	if (skb_queue_len(&csk->rxq)) {
		skb_queue_splice_init(&csk->rxq, rxq);
		spin_unlock_bh(&csk->rxq.lock);
		return true;
	}
	spin_unlock_bh(&csk->rxq.lock);
	return false;
}