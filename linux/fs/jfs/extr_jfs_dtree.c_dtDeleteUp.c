#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct tlock {int /*<<< orphan*/  lock; } ;
struct pxd_lock {int index; int /*<<< orphan*/  pxd; void* flag; } ;
struct metapage {int dummy; } ;
struct lv {int length; scalar_t__ offset; } ;
struct inode {int /*<<< orphan*/  i_size; } ;
struct dt_lock {size_t index; size_t maxcnt; struct lv* lv; } ;
struct btstack {int dummy; } ;
struct btframe {int index; int /*<<< orphan*/  bn; } ;
struct TYPE_8__ {int nextindex; int flag; scalar_t__ prev; scalar_t__ stblindex; int /*<<< orphan*/  self; } ;
struct TYPE_9__ {TYPE_1__ header; } ;
typedef  TYPE_2__ dtpage_t ;

/* Variables and functions */
 scalar_t__ BT_IS_ROOT (struct metapage*) ; 
 int /*<<< orphan*/  BT_MARK_DIRTY (struct metapage*,struct inode*) ; 
 struct btframe* BT_POP (struct btstack*) ; 
 int /*<<< orphan*/  BT_PUTPAGE (struct metapage*) ; 
 int BT_ROOT ; 
 int /*<<< orphan*/  DO_INDEX (struct inode*) ; 
 int /*<<< orphan*/  DT_GETPAGE (struct inode*,int /*<<< orphan*/ ,struct metapage*,scalar_t__,TYPE_2__*,int) ; 
 int /*<<< orphan*/  DT_PUTPAGE (struct metapage*) ; 
 int L2DTSLOTSIZE ; 
 int /*<<< orphan*/  PARENT (struct inode*) ; 
 scalar_t__ PSIZE ; 
 int /*<<< orphan*/  discard_metapage (struct metapage*) ; 
 int /*<<< orphan*/  dquot_free_block (struct inode*,int) ; 
 int /*<<< orphan*/  dtDeleteEntry (TYPE_2__*,int,struct dt_lock**) ; 
 int /*<<< orphan*/  dtInitRoot (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 
 int dtRelink (int /*<<< orphan*/ ,struct inode*,TYPE_2__*) ; 
 int /*<<< orphan*/  dtTruncateEntry (TYPE_2__*,int /*<<< orphan*/ ,struct dt_lock**) ; 
 int lengthPXD (int /*<<< orphan*/ *) ; 
 void* mlckFREEPXD ; 
 int tlckDTREE ; 
 int tlckENTRY ; 
 int tlckFREE ; 
 scalar_t__ txLinelock (struct dt_lock*) ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct inode*,struct metapage*,int) ; 
 struct tlock* txMaplock (int /*<<< orphan*/ ,struct inode*,int) ; 

__attribute__((used)) static int dtDeleteUp(tid_t tid, struct inode *ip,
	   struct metapage * fmp, dtpage_t * fp, struct btstack * btstack)
{
	int rc = 0;
	struct metapage *mp;
	dtpage_t *p;
	int index, nextindex;
	int xlen;
	struct btframe *parent;
	struct dt_lock *dtlck;
	struct tlock *tlck;
	struct lv *lv;
	struct pxd_lock *pxdlock;
	int i;

	/*
	 *	keep the root leaf page which has become empty
	 */
	if (BT_IS_ROOT(fmp)) {
		/*
		 * reset the root
		 *
		 * dtInitRoot() acquires txlock on the root
		 */
		dtInitRoot(tid, ip, PARENT(ip));

		DT_PUTPAGE(fmp);

		return 0;
	}

	/*
	 *	free the non-root leaf page
	 */
	/*
	 * acquire a transaction lock on the page
	 *
	 * write FREEXTENT|NOREDOPAGE log record
	 * N.B. linelock is overlaid as freed extent descriptor, and
	 * the buffer page is freed;
	 */
	tlck = txMaplock(tid, ip, tlckDTREE | tlckFREE);
	pxdlock = (struct pxd_lock *) & tlck->lock;
	pxdlock->flag = mlckFREEPXD;
	pxdlock->pxd = fp->header.self;
	pxdlock->index = 1;

	/* update sibling pointers */
	if ((rc = dtRelink(tid, ip, fp))) {
		BT_PUTPAGE(fmp);
		return rc;
	}

	xlen = lengthPXD(&fp->header.self);

	/* Free quota allocation. */
	dquot_free_block(ip, xlen);

	/* free/invalidate its buffer page */
	discard_metapage(fmp);

	/*
	 *	propagate page deletion up the directory tree
	 *
	 * If the delete from the parent page makes it empty,
	 * continue all the way up the tree.
	 * stop if the root page is reached (which is never deleted) or
	 * if the entry deletion does not empty the page.
	 */
	while ((parent = BT_POP(btstack)) != NULL) {
		/* pin the parent page <sp> */
		DT_GETPAGE(ip, parent->bn, mp, PSIZE, p, rc);
		if (rc)
			return rc;

		/*
		 * free the extent of the child page deleted
		 */
		index = parent->index;

		/*
		 * delete the entry for the child page from parent
		 */
		nextindex = p->header.nextindex;

		/*
		 * the parent has the single entry being deleted:
		 *
		 * free the parent page which has become empty.
		 */
		if (nextindex == 1) {
			/*
			 * keep the root internal page which has become empty
			 */
			if (p->header.flag & BT_ROOT) {
				/*
				 * reset the root
				 *
				 * dtInitRoot() acquires txlock on the root
				 */
				dtInitRoot(tid, ip, PARENT(ip));

				DT_PUTPAGE(mp);

				return 0;
			}
			/*
			 * free the parent page
			 */
			else {
				/*
				 * acquire a transaction lock on the page
				 *
				 * write FREEXTENT|NOREDOPAGE log record
				 */
				tlck =
				    txMaplock(tid, ip,
					      tlckDTREE | tlckFREE);
				pxdlock = (struct pxd_lock *) & tlck->lock;
				pxdlock->flag = mlckFREEPXD;
				pxdlock->pxd = p->header.self;
				pxdlock->index = 1;

				/* update sibling pointers */
				if ((rc = dtRelink(tid, ip, p))) {
					DT_PUTPAGE(mp);
					return rc;
				}

				xlen = lengthPXD(&p->header.self);

				/* Free quota allocation */
				dquot_free_block(ip, xlen);

				/* free/invalidate its buffer page */
				discard_metapage(mp);

				/* propagate up */
				continue;
			}
		}

		/*
		 * the parent has other entries remaining:
		 *
		 * delete the router entry from the parent page.
		 */
		BT_MARK_DIRTY(mp, ip);
		/*
		 * acquire a transaction lock on the page
		 *
		 * action: router entry deletion
		 */
		tlck = txLock(tid, ip, mp, tlckDTREE | tlckENTRY);
		dtlck = (struct dt_lock *) & tlck->lock;

		/* linelock header */
		if (dtlck->index >= dtlck->maxcnt)
			dtlck = (struct dt_lock *) txLinelock(dtlck);
		lv = & dtlck->lv[dtlck->index];
		lv->offset = 0;
		lv->length = 1;
		dtlck->index++;

		/* linelock stbl of non-root leaf page */
		if (!(p->header.flag & BT_ROOT)) {
			if (dtlck->index < dtlck->maxcnt)
				lv++;
			else {
				dtlck = (struct dt_lock *) txLinelock(dtlck);
				lv = & dtlck->lv[0];
			}
			i = index >> L2DTSLOTSIZE;
			lv->offset = p->header.stblindex + i;
			lv->length =
			    ((p->header.nextindex - 1) >> L2DTSLOTSIZE) -
			    i + 1;
			dtlck->index++;
		}

		/* free the router entry */
		dtDeleteEntry(p, index, &dtlck);

		/* reset key of new leftmost entry of level (for consistency) */
		if (index == 0 &&
		    ((p->header.flag & BT_ROOT) || p->header.prev == 0))
			dtTruncateEntry(p, 0, &dtlck);

		/* unpin the parent page */
		DT_PUTPAGE(mp);

		/* exit propagation up */
		break;
	}

	if (!DO_INDEX(ip))
		ip->i_size -= PSIZE;

	return 0;
}