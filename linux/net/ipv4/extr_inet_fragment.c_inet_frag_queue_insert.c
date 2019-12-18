#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int ip_defrag_offset; int len; int /*<<< orphan*/  rbnode; } ;
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;
struct TYPE_3__ {struct rb_node* rb_node; } ;
struct inet_frag_queue {TYPE_1__ rb_fragments; struct sk_buff* fragments_tail; } ;
struct TYPE_4__ {int frag_run_len; } ;

/* Variables and functions */
 TYPE_2__* FRAG_CB (struct sk_buff*) ; 
 int IPFRAG_DUP ; 
 int IPFRAG_OK ; 
 int IPFRAG_OVERLAP ; 
 int /*<<< orphan*/  fragcb_clear (struct sk_buff*) ; 
 int /*<<< orphan*/  fragrun_append_to_last (struct inet_frag_queue*,struct sk_buff*) ; 
 int /*<<< orphan*/  fragrun_create (struct inet_frag_queue*,struct sk_buff*) ; 
 int /*<<< orphan*/  rb_insert_color (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  rb_link_node (int /*<<< orphan*/ *,struct rb_node*,struct rb_node**) ; 
 struct sk_buff* rb_to_skb (struct rb_node*) ; 

int inet_frag_queue_insert(struct inet_frag_queue *q, struct sk_buff *skb,
			   int offset, int end)
{
	struct sk_buff *last = q->fragments_tail;

	/* RFC5722, Section 4, amended by Errata ID : 3089
	 *                          When reassembling an IPv6 datagram, if
	 *   one or more its constituent fragments is determined to be an
	 *   overlapping fragment, the entire datagram (and any constituent
	 *   fragments) MUST be silently discarded.
	 *
	 * Duplicates, however, should be ignored (i.e. skb dropped, but the
	 * queue/fragments kept for later reassembly).
	 */
	if (!last)
		fragrun_create(q, skb);  /* First fragment. */
	else if (last->ip_defrag_offset + last->len < end) {
		/* This is the common case: skb goes to the end. */
		/* Detect and discard overlaps. */
		if (offset < last->ip_defrag_offset + last->len)
			return IPFRAG_OVERLAP;
		if (offset == last->ip_defrag_offset + last->len)
			fragrun_append_to_last(q, skb);
		else
			fragrun_create(q, skb);
	} else {
		/* Binary search. Note that skb can become the first fragment,
		 * but not the last (covered above).
		 */
		struct rb_node **rbn, *parent;

		rbn = &q->rb_fragments.rb_node;
		do {
			struct sk_buff *curr;
			int curr_run_end;

			parent = *rbn;
			curr = rb_to_skb(parent);
			curr_run_end = curr->ip_defrag_offset +
					FRAG_CB(curr)->frag_run_len;
			if (end <= curr->ip_defrag_offset)
				rbn = &parent->rb_left;
			else if (offset >= curr_run_end)
				rbn = &parent->rb_right;
			else if (offset >= curr->ip_defrag_offset &&
				 end <= curr_run_end)
				return IPFRAG_DUP;
			else
				return IPFRAG_OVERLAP;
		} while (*rbn);
		/* Here we have parent properly set, and rbn pointing to
		 * one of its NULL left/right children. Insert skb.
		 */
		fragcb_clear(skb);
		rb_link_node(&skb->rbnode, parent, rbn);
		rb_insert_color(&skb->rbnode, &q->rb_fragments);
	}

	skb->ip_defrag_offset = offset;

	return IPFRAG_OK;
}