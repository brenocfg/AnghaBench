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
struct inet_frags {unsigned int qsize; } ;
struct inet_frag_queue {int flags; int /*<<< orphan*/  rcu; int /*<<< orphan*/  rb_fragments; struct fqdir* fqdir; int /*<<< orphan*/  timer; } ;
struct fqdir {struct inet_frags* f; } ;

/* Variables and functions */
 int INET_FRAG_COMPLETE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_frag_destroy_rcu ; 
 unsigned int inet_frag_rbtree_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sub_frag_mem_limit (struct fqdir*,unsigned int) ; 

void inet_frag_destroy(struct inet_frag_queue *q)
{
	struct fqdir *fqdir;
	unsigned int sum, sum_truesize = 0;
	struct inet_frags *f;

	WARN_ON(!(q->flags & INET_FRAG_COMPLETE));
	WARN_ON(del_timer(&q->timer) != 0);

	/* Release all fragment data. */
	fqdir = q->fqdir;
	f = fqdir->f;
	sum_truesize = inet_frag_rbtree_purge(&q->rb_fragments);
	sum = sum_truesize + f->qsize;

	call_rcu(&q->rcu, inet_frag_destroy_rcu);

	sub_frag_mem_limit(fqdir, sum);
}