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
struct lbuf {int l_pn; scalar_t__ l_ceor; scalar_t__ l_blkno; struct lbuf* l_freelist; int /*<<< orphan*/ * l_wqnext; scalar_t__ l_flag; } ;
struct jfs_log {int l2bsize; scalar_t__ base; struct lbuf* lbuf_free; int /*<<< orphan*/  free_wait; } ;

/* Variables and functions */
 int L2LOGPSIZE ; 
 int /*<<< orphan*/  LCACHE_LOCK (unsigned long) ; 
 int /*<<< orphan*/  LCACHE_SLEEP_COND (int /*<<< orphan*/ ,struct lbuf*,unsigned long) ; 
 int /*<<< orphan*/  LCACHE_UNLOCK (unsigned long) ; 

__attribute__((used)) static struct lbuf *lbmAllocate(struct jfs_log * log, int pn)
{
	struct lbuf *bp;
	unsigned long flags;

	/*
	 * recycle from log buffer freelist if any
	 */
	LCACHE_LOCK(flags);
	LCACHE_SLEEP_COND(log->free_wait, (bp = log->lbuf_free), flags);
	log->lbuf_free = bp->l_freelist;
	LCACHE_UNLOCK(flags);

	bp->l_flag = 0;

	bp->l_wqnext = NULL;
	bp->l_freelist = NULL;

	bp->l_pn = pn;
	bp->l_blkno = log->base + (pn << (L2LOGPSIZE - log->l2bsize));
	bp->l_ceor = 0;

	return bp;
}