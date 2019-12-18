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
struct lbuf {int l_pn; int l_flag; struct lbuf* l_wqnext; scalar_t__ l_blkno; } ;
struct jfs_log {int l2bsize; struct lbuf* wqueue; scalar_t__ base; } ;

/* Variables and functions */
 int L2LOGPSIZE ; 
 int /*<<< orphan*/  LCACHE_LOCK (unsigned long) ; 
 int /*<<< orphan*/  LCACHE_UNLOCK (unsigned long) ; 
 int /*<<< orphan*/  LOGGC_LOCK (struct jfs_log*) ; 
 int /*<<< orphan*/  LOGGC_UNLOCK (struct jfs_log*) ; 
 int /*<<< orphan*/  jfs_info (char*,struct lbuf*,int,int) ; 
 int /*<<< orphan*/  lbmRedrive (struct lbuf*) ; 
 int lbmSYNC ; 
 int /*<<< orphan*/  lbmStartIO (struct lbuf*) ; 
 int lbmWRITE ; 

__attribute__((used)) static void lbmWrite(struct jfs_log * log, struct lbuf * bp, int flag,
		     int cant_block)
{
	struct lbuf *tail;
	unsigned long flags;

	jfs_info("lbmWrite: bp:0x%p flag:0x%x pn:0x%x", bp, flag, bp->l_pn);

	/* map the logical block address to physical block address */
	bp->l_blkno =
	    log->base + (bp->l_pn << (L2LOGPSIZE - log->l2bsize));

	LCACHE_LOCK(flags);		/* disable+lock */

	/*
	 * initialize buffer for device driver
	 */
	bp->l_flag = flag;

	/*
	 *	insert bp at tail of write queue associated with log
	 *
	 * (request is either for bp already/currently at head of queue
	 * or new bp to be inserted at tail)
	 */
	tail = log->wqueue;

	/* is buffer not already on write queue ? */
	if (bp->l_wqnext == NULL) {
		/* insert at tail of wqueue */
		if (tail == NULL) {
			log->wqueue = bp;
			bp->l_wqnext = bp;
		} else {
			log->wqueue = bp;
			bp->l_wqnext = tail->l_wqnext;
			tail->l_wqnext = bp;
		}

		tail = bp;
	}

	/* is buffer at head of wqueue and for write ? */
	if ((bp != tail->l_wqnext) || !(flag & lbmWRITE)) {
		LCACHE_UNLOCK(flags);	/* unlock+enable */
		return;
	}

	LCACHE_UNLOCK(flags);	/* unlock+enable */

	if (cant_block)
		lbmRedrive(bp);
	else if (flag & lbmSYNC)
		lbmStartIO(bp);
	else {
		LOGGC_UNLOCK(log);
		lbmStartIO(bp);
		LOGGC_LOCK(log);
	}
}