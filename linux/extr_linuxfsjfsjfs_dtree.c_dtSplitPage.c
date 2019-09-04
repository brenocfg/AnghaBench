#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  tid_t ;
struct tlock {int /*<<< orphan*/  lock; scalar_t__ data; } ;
struct pxdlist {size_t npxd; int /*<<< orphan*/ * pxd; } ;
struct metapage {int /*<<< orphan*/  lock; scalar_t__ data; } ;
struct lv {int offset; int length; } ;
struct ldtentry {int /*<<< orphan*/  index; int /*<<< orphan*/  namlen; } ;
struct inode {int /*<<< orphan*/  lock; scalar_t__ data; } ;
struct idtentry {int /*<<< orphan*/  namlen; } ;
struct dtsplit {int index; int nslot; int /*<<< orphan*/  data; int /*<<< orphan*/  key; struct pxdlist* pxdlist; struct tlock* mp; } ;
struct dtslot {int next; } ;
struct dt_lock {size_t index; size_t maxcnt; struct lv* lv; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  pxd_t ;
struct TYPE_10__ {int flag; int nextindex; int stblindex; int maxslot; int freelist; int freecnt; void* prev; void* next; int /*<<< orphan*/  self; } ;
struct TYPE_11__ {TYPE_1__ header; struct dtslot* slot; } ;
typedef  TYPE_2__ dtpage_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  BT_INTERNAL 129 
#define  BT_LEAF 128 
 int /*<<< orphan*/  BT_MARK_DIRTY (struct tlock*,struct tlock*) ; 
 int BT_TYPE ; 
 scalar_t__ DO_INDEX (struct tlock*) ; 
 int /*<<< orphan*/  DT_GETPAGE (struct tlock*,scalar_t__,struct tlock*,int,TYPE_2__*,int) ; 
 size_t* DT_GETSTBL (TYPE_2__*) ; 
 TYPE_2__* DT_PAGE (struct tlock*,struct tlock*) ; 
 int /*<<< orphan*/  DT_PUTPAGE (struct tlock*) ; 
 int EIO ; 
 int L2DTSLOTSIZE ; 
 int NDTINTERNAL (int /*<<< orphan*/ ) ; 
 int NDTLEAF (int /*<<< orphan*/ ) ; 
 int NDTLEAF_LEGACY (int /*<<< orphan*/ ) ; 
 int PSIZE ; 
 scalar_t__ addressPXD (int /*<<< orphan*/ *) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  discard_metapage (struct tlock*) ; 
 int dquot_alloc_block (struct tlock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtInsertEntry (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dt_lock**) ; 
 int /*<<< orphan*/  dtMoveEntry (TYPE_2__*,int,TYPE_2__*,struct dt_lock**,struct dt_lock**,scalar_t__) ; 
 struct tlock* get_metapage (struct tlock*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  jfs_info (char*,struct tlock*,struct tlock*,struct tlock*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (void*) ; 
 int /*<<< orphan*/  lengthPXD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modify_index (int /*<<< orphan*/ ,struct tlock*,int /*<<< orphan*/ ,scalar_t__,int,struct tlock**,scalar_t__*) ; 
 int /*<<< orphan*/  release_metapage (struct tlock*) ; 
 int tlckDTREE ; 
 int tlckENTRY ; 
 int tlckNEW ; 
 int tlckRELINK ; 
 scalar_t__ txLinelock (struct dt_lock*) ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct tlock*,struct tlock*,int) ; 

__attribute__((used)) static int dtSplitPage(tid_t tid, struct inode *ip, struct dtsplit * split,
	    struct metapage ** rmpp, dtpage_t ** rpp, pxd_t * rpxdp)
{
	int rc = 0;
	struct metapage *smp;
	dtpage_t *sp;
	struct metapage *rmp;
	dtpage_t *rp;		/* new right page allocated */
	s64 rbn;		/* new right page block number */
	struct metapage *mp;
	dtpage_t *p;
	s64 nextbn;
	struct pxdlist *pxdlist;
	pxd_t *pxd;
	int skip, nextindex, half, left, nxt, off, si;
	struct ldtentry *ldtentry;
	struct idtentry *idtentry;
	u8 *stbl;
	struct dtslot *f;
	int fsi, stblsize;
	int n;
	struct dt_lock *sdtlck, *rdtlck;
	struct tlock *tlck;
	struct dt_lock *dtlck;
	struct lv *slv, *rlv, *lv;

	/* get split page */
	smp = split->mp;
	sp = DT_PAGE(ip, smp);

	/*
	 * allocate the new right page for the split
	 */
	pxdlist = split->pxdlist;
	pxd = &pxdlist->pxd[pxdlist->npxd];
	pxdlist->npxd++;
	rbn = addressPXD(pxd);
	rmp = get_metapage(ip, rbn, PSIZE, 1);
	if (rmp == NULL)
		return -EIO;

	/* Allocate blocks to quota. */
	rc = dquot_alloc_block(ip, lengthPXD(pxd));
	if (rc) {
		release_metapage(rmp);
		return rc;
	}

	jfs_info("dtSplitPage: ip:0x%p smp:0x%p rmp:0x%p", ip, smp, rmp);

	BT_MARK_DIRTY(rmp, ip);
	/*
	 * acquire a transaction lock on the new right page
	 */
	tlck = txLock(tid, ip, rmp, tlckDTREE | tlckNEW);
	rdtlck = (struct dt_lock *) & tlck->lock;

	rp = (dtpage_t *) rmp->data;
	*rpp = rp;
	rp->header.self = *pxd;

	BT_MARK_DIRTY(smp, ip);
	/*
	 * acquire a transaction lock on the split page
	 *
	 * action:
	 */
	tlck = txLock(tid, ip, smp, tlckDTREE | tlckENTRY);
	sdtlck = (struct dt_lock *) & tlck->lock;

	/* linelock header of split page */
	ASSERT(sdtlck->index == 0);
	slv = & sdtlck->lv[0];
	slv->offset = 0;
	slv->length = 1;
	sdtlck->index++;

	/*
	 * initialize/update sibling pointers between sp and rp
	 */
	nextbn = le64_to_cpu(sp->header.next);
	rp->header.next = cpu_to_le64(nextbn);
	rp->header.prev = cpu_to_le64(addressPXD(&sp->header.self));
	sp->header.next = cpu_to_le64(rbn);

	/*
	 * initialize new right page
	 */
	rp->header.flag = sp->header.flag;

	/* compute sorted entry table at start of extent data area */
	rp->header.nextindex = 0;
	rp->header.stblindex = 1;

	n = PSIZE >> L2DTSLOTSIZE;
	rp->header.maxslot = n;
	stblsize = (n + 31) >> L2DTSLOTSIZE;	/* in unit of slot */

	/* init freelist */
	fsi = rp->header.stblindex + stblsize;
	rp->header.freelist = fsi;
	rp->header.freecnt = rp->header.maxslot - fsi;

	/*
	 *	sequential append at tail: append without split
	 *
	 * If splitting the last page on a level because of appending
	 * a entry to it (skip is maxentry), it's likely that the access is
	 * sequential. Adding an empty page on the side of the level is less
	 * work and can push the fill factor much higher than normal.
	 * If we're wrong it's no big deal, we'll just do the split the right
	 * way next time.
	 * (It may look like it's equally easy to do a similar hack for
	 * reverse sorted data, that is, split the tree left,
	 * but it's not. Be my guest.)
	 */
	if (nextbn == 0 && split->index == sp->header.nextindex) {
		/* linelock header + stbl (first slot) of new page */
		rlv = & rdtlck->lv[rdtlck->index];
		rlv->offset = 0;
		rlv->length = 2;
		rdtlck->index++;

		/*
		 * initialize freelist of new right page
		 */
		f = &rp->slot[fsi];
		for (fsi++; fsi < rp->header.maxslot; f++, fsi++)
			f->next = fsi;
		f->next = -1;

		/* insert entry at the first entry of the new right page */
		dtInsertEntry(rp, 0, split->key, split->data, &rdtlck);

		goto out;
	}

	/*
	 *	non-sequential insert (at possibly middle page)
	 */

	/*
	 * update prev pointer of previous right sibling page;
	 */
	if (nextbn != 0) {
		DT_GETPAGE(ip, nextbn, mp, PSIZE, p, rc);
		if (rc) {
			discard_metapage(rmp);
			return rc;
		}

		BT_MARK_DIRTY(mp, ip);
		/*
		 * acquire a transaction lock on the next page
		 */
		tlck = txLock(tid, ip, mp, tlckDTREE | tlckRELINK);
		jfs_info("dtSplitPage: tlck = 0x%p, ip = 0x%p, mp=0x%p",
			tlck, ip, mp);
		dtlck = (struct dt_lock *) & tlck->lock;

		/* linelock header of previous right sibling page */
		lv = & dtlck->lv[dtlck->index];
		lv->offset = 0;
		lv->length = 1;
		dtlck->index++;

		p->header.prev = cpu_to_le64(rbn);

		DT_PUTPAGE(mp);
	}

	/*
	 * split the data between the split and right pages.
	 */
	skip = split->index;
	half = (PSIZE >> L2DTSLOTSIZE) >> 1;	/* swag */
	left = 0;

	/*
	 *	compute fill factor for split pages
	 *
	 * <nxt> traces the next entry to move to rp
	 * <off> traces the next entry to stay in sp
	 */
	stbl = (u8 *) & sp->slot[sp->header.stblindex];
	nextindex = sp->header.nextindex;
	for (nxt = off = 0; nxt < nextindex; ++off) {
		if (off == skip)
			/* check for fill factor with new entry size */
			n = split->nslot;
		else {
			si = stbl[nxt];
			switch (sp->header.flag & BT_TYPE) {
			case BT_LEAF:
				ldtentry = (struct ldtentry *) & sp->slot[si];
				if (DO_INDEX(ip))
					n = NDTLEAF(ldtentry->namlen);
				else
					n = NDTLEAF_LEGACY(ldtentry->
							   namlen);
				break;

			case BT_INTERNAL:
				idtentry = (struct idtentry *) & sp->slot[si];
				n = NDTINTERNAL(idtentry->namlen);
				break;

			default:
				break;
			}

			++nxt;	/* advance to next entry to move in sp */
		}

		left += n;
		if (left >= half)
			break;
	}

	/* <nxt> poins to the 1st entry to move */

	/*
	 *	move entries to right page
	 *
	 * dtMoveEntry() initializes rp and reserves entry for insertion
	 *
	 * split page moved out entries are linelocked;
	 * new/right page moved in entries are linelocked;
	 */
	/* linelock header + stbl of new right page */
	rlv = & rdtlck->lv[rdtlck->index];
	rlv->offset = 0;
	rlv->length = 5;
	rdtlck->index++;

	dtMoveEntry(sp, nxt, rp, &sdtlck, &rdtlck, DO_INDEX(ip));

	sp->header.nextindex = nxt;

	/*
	 * finalize freelist of new right page
	 */
	fsi = rp->header.freelist;
	f = &rp->slot[fsi];
	for (fsi++; fsi < rp->header.maxslot; f++, fsi++)
		f->next = fsi;
	f->next = -1;

	/*
	 * Update directory index table for entries now in right page
	 */
	if ((rp->header.flag & BT_LEAF) && DO_INDEX(ip)) {
		s64 lblock;

		mp = NULL;
		stbl = DT_GETSTBL(rp);
		for (n = 0; n < rp->header.nextindex; n++) {
			ldtentry = (struct ldtentry *) & rp->slot[stbl[n]];
			modify_index(tid, ip, le32_to_cpu(ldtentry->index),
				     rbn, n, &mp, &lblock);
		}
		if (mp)
			release_metapage(mp);
	}

	/*
	 * the skipped index was on the left page,
	 */
	if (skip <= off) {
		/* insert the new entry in the split page */
		dtInsertEntry(sp, skip, split->key, split->data, &sdtlck);

		/* linelock stbl of split page */
		if (sdtlck->index >= sdtlck->maxcnt)
			sdtlck = (struct dt_lock *) txLinelock(sdtlck);
		slv = & sdtlck->lv[sdtlck->index];
		n = skip >> L2DTSLOTSIZE;
		slv->offset = sp->header.stblindex + n;
		slv->length =
		    ((sp->header.nextindex - 1) >> L2DTSLOTSIZE) - n + 1;
		sdtlck->index++;
	}
	/*
	 * the skipped index was on the right page,
	 */
	else {
		/* adjust the skip index to reflect the new position */
		skip -= nxt;

		/* insert the new entry in the right page */
		dtInsertEntry(rp, skip, split->key, split->data, &rdtlck);
	}

      out:
	*rmpp = rmp;
	*rpxdp = *pxd;

	return rc;
}