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
struct rb_node {int dummy; } ;
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  tstamp; int /*<<< orphan*/ * prev; scalar_t__ truesize; int /*<<< orphan*/  csum; scalar_t__ len; int /*<<< orphan*/  data_len; int /*<<< orphan*/ * sk; struct rb_node rbnode; struct sk_buff* next; scalar_t__ data; } ;
struct inet_frag_queue {int /*<<< orphan*/  stamp; int /*<<< orphan*/  net; int /*<<< orphan*/  rb_fragments; } ;
struct TYPE_2__ {struct sk_buff* next_frag; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 scalar_t__ CHECKSUM_NONE ; 
 TYPE_1__* FRAG_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  csum_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rb_node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rb_erase (struct rb_node*,int /*<<< orphan*/ *) ; 
 struct rb_node* rb_next (struct rb_node*) ; 
 struct sk_buff* rb_to_skb (struct rb_node*) ; 
 int /*<<< orphan*/  skb_mark_not_on_list (struct sk_buff*) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  sub_frag_mem_limit (int /*<<< orphan*/ ,scalar_t__) ; 

void inet_frag_reasm_finish(struct inet_frag_queue *q, struct sk_buff *head,
			    void *reasm_data)
{
	struct sk_buff **nextp = (struct sk_buff **)reasm_data;
	struct rb_node *rbn;
	struct sk_buff *fp;

	skb_push(head, head->data - skb_network_header(head));

	/* Traverse the tree in order, to build frag_list. */
	fp = FRAG_CB(head)->next_frag;
	rbn = rb_next(&head->rbnode);
	rb_erase(&head->rbnode, &q->rb_fragments);
	while (rbn || fp) {
		/* fp points to the next sk_buff in the current run;
		 * rbn points to the next run.
		 */
		/* Go through the current run. */
		while (fp) {
			*nextp = fp;
			nextp = &fp->next;
			fp->prev = NULL;
			memset(&fp->rbnode, 0, sizeof(fp->rbnode));
			fp->sk = NULL;
			head->data_len += fp->len;
			head->len += fp->len;
			if (head->ip_summed != fp->ip_summed)
				head->ip_summed = CHECKSUM_NONE;
			else if (head->ip_summed == CHECKSUM_COMPLETE)
				head->csum = csum_add(head->csum, fp->csum);
			head->truesize += fp->truesize;
			fp = FRAG_CB(fp)->next_frag;
		}
		/* Move to the next run. */
		if (rbn) {
			struct rb_node *rbnext = rb_next(rbn);

			fp = rb_to_skb(rbn);
			rb_erase(rbn, &q->rb_fragments);
			rbn = rbnext;
		}
	}
	sub_frag_mem_limit(q->net, head->truesize);

	*nextp = NULL;
	skb_mark_not_on_list(head);
	head->prev = NULL;
	head->tstamp = q->stamp;
}