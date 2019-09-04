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
struct sk_buff_head {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_splice_tail_init (struct sk_buff_head*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_skb_queue_splice_tail (struct sk_buff_head*,struct sk_buff_head*) ; 

__attribute__((used)) static inline void tipc_skb_queue_splice_tail_init(struct sk_buff_head *list,
						   struct sk_buff_head *head)
{
	struct sk_buff_head tmp;

	__skb_queue_head_init(&tmp);

	spin_lock_bh(&list->lock);
	skb_queue_splice_tail_init(list, &tmp);
	spin_unlock_bh(&list->lock);
	tipc_skb_queue_splice_tail(&tmp, head);
}