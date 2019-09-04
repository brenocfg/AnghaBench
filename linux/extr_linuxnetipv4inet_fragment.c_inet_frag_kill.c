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
struct netns_frags {TYPE_1__* f; int /*<<< orphan*/  rhashtable; } ;
struct inet_frag_queue {int flags; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  node; struct netns_frags* net; int /*<<< orphan*/  timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  rhash_params; } ;

/* Variables and functions */
 int INET_FRAG_COMPLETE ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void inet_frag_kill(struct inet_frag_queue *fq)
{
	if (del_timer(&fq->timer))
		refcount_dec(&fq->refcnt);

	if (!(fq->flags & INET_FRAG_COMPLETE)) {
		struct netns_frags *nf = fq->net;

		fq->flags |= INET_FRAG_COMPLETE;
		rhashtable_remove_fast(&nf->rhashtable, &fq->node, nf->f->rhash_params);
		refcount_dec(&fq->refcnt);
	}
}