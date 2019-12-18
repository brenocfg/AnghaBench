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
struct sk_buff {int truesize; scalar_t__ ip_summed; int /*<<< orphan*/  tstamp; int /*<<< orphan*/ * prev; struct sk_buff* next; scalar_t__ len; int /*<<< orphan*/  data_len; int /*<<< orphan*/ * sk; struct rb_node rbnode; int /*<<< orphan*/  csum; scalar_t__ data; } ;
struct inet_frag_queue {int /*<<< orphan*/  stamp; int /*<<< orphan*/  fqdir; int /*<<< orphan*/  rb_fragments; } ;
struct TYPE_2__ {struct sk_buff* next_frag; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 scalar_t__ CHECKSUM_NONE ; 
 TYPE_1__* FRAG_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  csum_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb_partial (struct sk_buff*,int) ; 
 int /*<<< orphan*/  memset (struct rb_node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rb_erase (struct rb_node*,int /*<<< orphan*/ *) ; 
 struct rb_node* rb_next (struct rb_node*) ; 
 struct sk_buff* rb_to_skb (struct rb_node*) ; 
 int /*<<< orphan*/  skb_mark_not_on_list (struct sk_buff*) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_try_coalesce (struct sk_buff*,struct sk_buff*,int*,int*) ; 
 int /*<<< orphan*/  sub_frag_mem_limit (int /*<<< orphan*/ ,int) ; 

void inet_frag_reasm_finish(struct inet_frag_queue *q, struct sk_buff *head,
			    void *reasm_data, bool try_coalesce)
{
	struct sk_buff **nextp = (struct sk_buff **)reasm_data;
	struct rb_node *rbn;
	struct sk_buff *fp;
	int sum_truesize;

	skb_push(head, head->data - skb_network_header(head));

	/* Traverse the tree in order, to build frag_list. */
	fp = FRAG_CB(head)->next_frag;
	rbn = rb_next(&head->rbnode);
	rb_erase(&head->rbnode, &q->rb_fragments);

	sum_truesize = head->truesize;
	while (rbn || fp) {
		/* fp points to the next sk_buff in the current run;
		 * rbn points to the next run.
		 */
		/* Go through the current run. */
		while (fp) {
			struct sk_buff *next_frag = FRAG_CB(fp)->next_frag;
			bool stolen;
			int delta;

			sum_truesize += fp->truesize;
			if (head->ip_summed != fp->ip_summed)
				head->ip_summed = CHECKSUM_NONE;
			else if (head->ip_summed == CHECKSUM_COMPLETE)
				head->csum = csum_add(head->csum, fp->csum);

			if (try_coalesce && skb_try_coalesce(head, fp, &stolen,
							     &delta)) {
				kfree_skb_partial(fp, stolen);
			} else {
				fp->prev = NULL;
				memset(&fp->rbnode, 0, sizeof(fp->rbnode));
				fp->sk = NULL;

				head->data_len += fp->len;
				head->len += fp->len;
				head->truesize += fp->truesize;

				*nextp = fp;
				nextp = &fp->next;
			}

			fp = next_frag;
		}
		/* Move to the next run. */
		if (rbn) {
			struct rb_node *rbnext = rb_next(rbn);

			fp = rb_to_skb(rbn);
			rb_erase(rbn, &q->rb_fragments);
			rbn = rbnext;
		}
	}
	sub_frag_mem_limit(q->fqdir, sum_truesize);

	*nextp = NULL;
	skb_mark_not_on_list(head);
	head->prev = NULL;
	head->tstamp = q->stamp;
}