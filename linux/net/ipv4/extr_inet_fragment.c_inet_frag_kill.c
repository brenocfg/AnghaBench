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
struct inet_frag_queue {int flags; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  node; struct fqdir* fqdir; int /*<<< orphan*/  timer; } ;
struct fqdir {TYPE_1__* f; int /*<<< orphan*/  rhashtable; int /*<<< orphan*/  dead; } ;
struct TYPE_2__ {int /*<<< orphan*/  rhash_params; } ;

/* Variables and functions */
 int INET_FRAG_COMPLETE ; 
 int INET_FRAG_HASH_DEAD ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void inet_frag_kill(struct inet_frag_queue *fq)
{
	if (del_timer(&fq->timer))
		refcount_dec(&fq->refcnt);

	if (!(fq->flags & INET_FRAG_COMPLETE)) {
		struct fqdir *fqdir = fq->fqdir;

		fq->flags |= INET_FRAG_COMPLETE;
		rcu_read_lock();
		/* The RCU read lock provides a memory barrier
		 * guaranteeing that if fqdir->dead is false then
		 * the hash table destruction will not start until
		 * after we unlock.  Paired with inet_frags_exit_net().
		 */
		if (!fqdir->dead) {
			rhashtable_remove_fast(&fqdir->rhashtable, &fq->node,
					       fqdir->f->rhash_params);
			refcount_dec(&fq->refcnt);
		} else {
			fq->flags |= INET_FRAG_HASH_DEAD;
		}
		rcu_read_unlock();
	}
}