#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tlock {scalar_t__ next; int flag; struct metapage* mp; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {struct inode* ip; int /*<<< orphan*/  ixpxd; } ;
struct tblock {int xflag; scalar_t__ next; int flag; TYPE_1__ u; int /*<<< orphan*/  ino; int /*<<< orphan*/  sb; } ;
struct pxd_lock {int index; int /*<<< orphan*/  pxd; int /*<<< orphan*/  flag; } ;
struct metapage {int xflag; scalar_t__ lid; int nohomeok; } ;
struct maplock {int index; int flag; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
typedef  scalar_t__ lid_t ;
struct TYPE_4__ {struct inode* ipimap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int COMMIT_CREATE ; 
 int COMMIT_DELETE ; 
 int COMMIT_PAGE ; 
 int COMMIT_PMAP ; 
 int COMMIT_PWMAP ; 
 TYPE_2__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  diUpdatePMap (struct inode*,int /*<<< orphan*/ ,int,struct tblock*) ; 
 int /*<<< orphan*/  discard_metapage (struct metapage*) ; 
 int /*<<< orphan*/  grab_metapage (struct metapage*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct tlock* lid_to_tlock (scalar_t__) ; 
 int /*<<< orphan*/  metapage_homeok (struct metapage*) ; 
 int mlckALLOC ; 
 int /*<<< orphan*/  mlckALLOCPXD ; 
 int tblkGC_LAZY ; 
 int tlckDIRECTORY ; 
 int tlckFREEPAGE ; 
 int tlckUPDATEMAP ; 
 int /*<<< orphan*/  txAllocPMap (struct inode*,struct maplock*,struct tblock*) ; 
 int /*<<< orphan*/  txFreeMap (struct inode*,struct maplock*,struct tblock*,int) ; 

__attribute__((used)) static void txUpdateMap(struct tblock * tblk)
{
	struct inode *ip;
	struct inode *ipimap;
	lid_t lid;
	struct tlock *tlck;
	struct maplock *maplock;
	struct pxd_lock pxdlock;
	int maptype;
	int k, nlock;
	struct metapage *mp = NULL;

	ipimap = JFS_SBI(tblk->sb)->ipimap;

	maptype = (tblk->xflag & COMMIT_PMAP) ? COMMIT_PMAP : COMMIT_PWMAP;


	/*
	 *	update block allocation map
	 *
	 * update allocation state in pmap (and wmap) and
	 * update lsn of the pmap page;
	 */
	/*
	 * scan each tlock/page of transaction for block allocation/free:
	 *
	 * for each tlock/page of transaction, update map.
	 *  ? are there tlock for pmap and pwmap at the same time ?
	 */
	for (lid = tblk->next; lid; lid = tlck->next) {
		tlck = lid_to_tlock(lid);

		if ((tlck->flag & tlckUPDATEMAP) == 0)
			continue;

		if (tlck->flag & tlckFREEPAGE) {
			/*
			 * Another thread may attempt to reuse freed space
			 * immediately, so we want to get rid of the metapage
			 * before anyone else has a chance to get it.
			 * Lock metapage, update maps, then invalidate
			 * the metapage.
			 */
			mp = tlck->mp;
			ASSERT(mp->xflag & COMMIT_PAGE);
			grab_metapage(mp);
		}

		/*
		 * extent list:
		 * . in-line PXD list:
		 * . out-of-line XAD list:
		 */
		maplock = (struct maplock *) & tlck->lock;
		nlock = maplock->index;

		for (k = 0; k < nlock; k++, maplock++) {
			/*
			 * allocate blocks in persistent map:
			 *
			 * blocks have been allocated from wmap at alloc time;
			 */
			if (maplock->flag & mlckALLOC) {
				txAllocPMap(ipimap, maplock, tblk);
			}
			/*
			 * free blocks in persistent and working map:
			 * blocks will be freed in pmap and then in wmap;
			 *
			 * ? tblock specifies the PMAP/PWMAP based upon
			 * transaction
			 *
			 * free blocks in persistent map:
			 * blocks will be freed from wmap at last reference
			 * release of the object for regular files;
			 *
			 * Alway free blocks from both persistent & working
			 * maps for directories
			 */
			else {	/* (maplock->flag & mlckFREE) */

				if (tlck->flag & tlckDIRECTORY)
					txFreeMap(ipimap, maplock,
						  tblk, COMMIT_PWMAP);
				else
					txFreeMap(ipimap, maplock,
						  tblk, maptype);
			}
		}
		if (tlck->flag & tlckFREEPAGE) {
			if (!(tblk->flag & tblkGC_LAZY)) {
				/* This is equivalent to txRelease */
				ASSERT(mp->lid == lid);
				tlck->mp->lid = 0;
			}
			assert(mp->nohomeok == 1);
			metapage_homeok(mp);
			discard_metapage(mp);
			tlck->mp = NULL;
		}
	}
	/*
	 *	update inode allocation map
	 *
	 * update allocation state in pmap and
	 * update lsn of the pmap page;
	 * update in-memory inode flag/state
	 *
	 * unlock mapper/write lock
	 */
	if (tblk->xflag & COMMIT_CREATE) {
		diUpdatePMap(ipimap, tblk->ino, false, tblk);
		/* update persistent block allocation map
		 * for the allocation of inode extent;
		 */
		pxdlock.flag = mlckALLOCPXD;
		pxdlock.pxd = tblk->u.ixpxd;
		pxdlock.index = 1;
		txAllocPMap(ipimap, (struct maplock *) & pxdlock, tblk);
	} else if (tblk->xflag & COMMIT_DELETE) {
		ip = tblk->u.ip;
		diUpdatePMap(ipimap, ip->i_ino, true, tblk);
		iput(ip);
	}
}