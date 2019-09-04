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
struct netns_frags {scalar_t__ high_thresh; TYPE_1__* f; int /*<<< orphan*/  rhashtable; } ;
struct inet_frag_queue {int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  rhash_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct inet_frag_queue*) ; 
 scalar_t__ frag_mem_limit (struct netns_frags*) ; 
 struct inet_frag_queue* inet_frag_create (struct netns_frags*,void*,struct inet_frag_queue**) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct inet_frag_queue* rhashtable_lookup (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

struct inet_frag_queue *inet_frag_find(struct netns_frags *nf, void *key)
{
	struct inet_frag_queue *fq = NULL, *prev;

	if (!nf->high_thresh || frag_mem_limit(nf) > nf->high_thresh)
		return NULL;

	rcu_read_lock();

	prev = rhashtable_lookup(&nf->rhashtable, key, nf->f->rhash_params);
	if (!prev)
		fq = inet_frag_create(nf, key, &prev);
	if (prev && !IS_ERR(prev)) {
		fq = prev;
		if (!refcount_inc_not_zero(&fq->refcnt))
			fq = NULL;
	}
	rcu_read_unlock();
	return fq;
}