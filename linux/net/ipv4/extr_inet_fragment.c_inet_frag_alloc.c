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
struct inet_frags {int /*<<< orphan*/  frag_expire; int /*<<< orphan*/  qsize; int /*<<< orphan*/  (* constructor ) (struct inet_frag_queue*,void*) ;int /*<<< orphan*/  frags_cachep; } ;
struct inet_frag_queue {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; struct fqdir* fqdir; } ;
struct fqdir {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  add_frag_mem_limit (struct fqdir*,int /*<<< orphan*/ ) ; 
 struct inet_frag_queue* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct inet_frag_queue*,void*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inet_frag_queue *inet_frag_alloc(struct fqdir *fqdir,
					       struct inet_frags *f,
					       void *arg)
{
	struct inet_frag_queue *q;

	q = kmem_cache_zalloc(f->frags_cachep, GFP_ATOMIC);
	if (!q)
		return NULL;

	q->fqdir = fqdir;
	f->constructor(q, arg);
	add_frag_mem_limit(fqdir, f->qsize);

	timer_setup(&q->timer, f->frag_expire, 0);
	spin_lock_init(&q->lock);
	refcount_set(&q->refcnt, 3);

	return q;
}