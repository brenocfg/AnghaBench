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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_errors; } ;
struct l2tp_session {scalar_t__ magic; TYPE_1__ stats; int /*<<< orphan*/  reorder_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ L2TP_SESSION_MAGIC ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2tp_session_queue_purge(struct l2tp_session *session)
{
	struct sk_buff *skb = NULL;
	BUG_ON(!session);
	BUG_ON(session->magic != L2TP_SESSION_MAGIC);
	while ((skb = skb_dequeue(&session->reorder_q))) {
		atomic_long_inc(&session->stats.rx_errors);
		kfree_skb(skb);
	}
	return 0;
}