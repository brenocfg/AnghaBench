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
struct inet_frag_queue {int /*<<< orphan*/  refcnt; } ;
struct fqdir {scalar_t__ high_thresh; TYPE_1__* f; int /*<<< orphan*/  rhashtable; } ;
struct TYPE_2__ {int /*<<< orphan*/  rhash_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct inet_frag_queue*) ; 
 scalar_t__ frag_mem_limit (struct fqdir*) ; 
 struct inet_frag_queue* inet_frag_create (struct fqdir*,void*,struct inet_frag_queue**) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct inet_frag_queue* rhashtable_lookup (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

struct inet_frag_queue *inet_frag_find(struct fqdir *fqdir, void *key)
{
	struct inet_frag_queue *fq = NULL, *prev;

	if (!fqdir->high_thresh || frag_mem_limit(fqdir) > fqdir->high_thresh)
		return NULL;

	rcu_read_lock();

	prev = rhashtable_lookup(&fqdir->rhashtable, key, fqdir->f->rhash_params);
	if (!prev)
		fq = inet_frag_create(fqdir, key, &prev);
	if (!IS_ERR_OR_NULL(prev)) {
		fq = prev;
		if (!refcount_inc_not_zero(&fq->refcnt))
			fq = NULL;
	}
	rcu_read_unlock();
	return fq;
}