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
struct sk_buff {int /*<<< orphan*/  rbnode; struct sk_buff* next; } ;
struct netem_sched_data {int /*<<< orphan*/  t_root; int /*<<< orphan*/ * t_tail; struct sk_buff* t_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netem_erase_head(struct netem_sched_data *q, struct sk_buff *skb)
{
	if (skb == q->t_head) {
		q->t_head = skb->next;
		if (!q->t_head)
			q->t_tail = NULL;
	} else {
		rb_erase(&skb->rbnode, &q->t_root);
	}
}