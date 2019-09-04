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
struct sk_buff {scalar_t__ truesize; struct sk_buff* next; } ;
struct netns_frags {struct inet_frags* f; } ;
struct inet_frags {unsigned int qsize; } ;
struct inet_frag_queue {int flags; int /*<<< orphan*/  rcu; int /*<<< orphan*/  rb_fragments; struct netns_frags* net; struct sk_buff* fragments; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int INET_FRAG_COMPLETE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_frag_destroy_rcu ; 
 unsigned int inet_frag_rbtree_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sub_frag_mem_limit (struct netns_frags*,unsigned int) ; 

void inet_frag_destroy(struct inet_frag_queue *q)
{
	struct sk_buff *fp;
	struct netns_frags *nf;
	unsigned int sum, sum_truesize = 0;
	struct inet_frags *f;

	WARN_ON(!(q->flags & INET_FRAG_COMPLETE));
	WARN_ON(del_timer(&q->timer) != 0);

	/* Release all fragment data. */
	fp = q->fragments;
	nf = q->net;
	f = nf->f;
	if (fp) {
		do {
			struct sk_buff *xp = fp->next;

			sum_truesize += fp->truesize;
			kfree_skb(fp);
			fp = xp;
		} while (fp);
	} else {
		sum_truesize = inet_frag_rbtree_purge(&q->rb_fragments);
	}
	sum = sum_truesize + f->qsize;

	call_rcu(&q->rcu, inet_frag_destroy_rcu);

	sub_frag_mem_limit(nf, sum);
}