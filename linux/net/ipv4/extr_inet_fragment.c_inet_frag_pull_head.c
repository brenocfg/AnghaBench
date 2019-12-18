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
struct sk_buff {int /*<<< orphan*/  truesize; int /*<<< orphan*/  rbnode; } ;
struct inet_frag_queue {int /*<<< orphan*/  fqdir; struct sk_buff* fragments_tail; int /*<<< orphan*/  rb_fragments; } ;
struct TYPE_2__ {struct sk_buff* next_frag; } ;

/* Variables and functions */
 TYPE_1__* FRAG_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_replace_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_rb_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sub_frag_mem_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct sk_buff *inet_frag_pull_head(struct inet_frag_queue *q)
{
	struct sk_buff *head, *skb;

	head = skb_rb_first(&q->rb_fragments);
	if (!head)
		return NULL;
	skb = FRAG_CB(head)->next_frag;
	if (skb)
		rb_replace_node(&head->rbnode, &skb->rbnode,
				&q->rb_fragments);
	else
		rb_erase(&head->rbnode, &q->rb_fragments);
	memset(&head->rbnode, 0, sizeof(head->rbnode));
	barrier();

	if (head == q->fragments_tail)
		q->fragments_tail = NULL;

	sub_frag_mem_limit(q->fqdir, head->truesize);

	return head;
}