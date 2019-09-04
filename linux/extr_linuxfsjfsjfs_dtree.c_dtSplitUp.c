#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tid_t ;
struct tlock {int /*<<< orphan*/  lock; } ;
struct pxdlist {int maxnpxd; int npxd; int /*<<< orphan*/ * pxd; } ;
struct metapage {int dummy; } ;
struct lv {int length; scalar_t__ offset; } ;
struct jfs_sb_info {int bsize; int l2bsize; int nbperpage; int mntflag; int /*<<< orphan*/  ipbmap; } ;
struct inode {int i_size; int /*<<< orphan*/  i_sb; } ;
struct dtsplit {int nslot; int index; struct component_name* key; struct metapage* mp; struct pxdlist* pxdlist; TYPE_3__* data; } ;
struct dt_lock {scalar_t__ index; struct lv* lv; } ;
struct component_name {size_t namlen; int /*<<< orphan*/ * name; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct btstack {int nsplit; } ;
struct btframe {int index; int /*<<< orphan*/  bn; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  pxd_t ;
struct TYPE_12__ {int flag; int freecnt; int nextindex; scalar_t__ stblindex; int /*<<< orphan*/  prev; int /*<<< orphan*/  self; } ;
struct TYPE_13__ {TYPE_1__ header; } ;
typedef  TYPE_2__ dtpage_t ;
struct TYPE_14__ {int /*<<< orphan*/  xd; } ;
typedef  TYPE_3__ ddata_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  BT_INTERNAL 129 
#define  BT_LEAF 128 
 int /*<<< orphan*/  BT_MARK_DIRTY (struct metapage*,struct inode*) ; 
 struct btframe* BT_POP (struct btstack*) ; 
 int BT_ROOT ; 
 int BT_TYPE ; 
 int /*<<< orphan*/  DO_INDEX (struct inode*) ; 
 scalar_t__ DTROOTMAXSLOT ; 
 int /*<<< orphan*/  DT_GETPAGE (struct inode*,int /*<<< orphan*/ ,struct metapage*,int,TYPE_2__*,int) ; 
 TYPE_2__* DT_PAGE (struct inode*,struct metapage*) ; 
 int /*<<< orphan*/  DT_PUTPAGE (struct metapage*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ JFS_NAME_MAX ; 
 int JFS_OS2 ; 
 struct jfs_sb_info* JFS_SBI (int /*<<< orphan*/ ) ; 
 int L2DTSLOTSIZE ; 
 int NDTINTERNAL (size_t) ; 
 int PSIZE ; 
 int /*<<< orphan*/  PXDaddress (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  PXDlength (int /*<<< orphan*/ *,int) ; 
 scalar_t__ addressPXD (int /*<<< orphan*/ *) ; 
 int ciGetLeafPrefixKey (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,struct component_name*,int) ; 
 int /*<<< orphan*/  ciToUpper (struct component_name*) ; 
 int dbAlloc (struct inode*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  dbFree (struct inode*,scalar_t__,scalar_t__) ; 
 int dbReAlloc (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__*) ; 
 int dquot_alloc_block (struct inode*,int) ; 
 int /*<<< orphan*/  dquot_free_block (struct inode*,int) ; 
 int dtExtendPage (int /*<<< orphan*/ ,struct inode*,struct dtsplit*,struct btstack*) ; 
 int /*<<< orphan*/  dtGetKey (TYPE_2__*,int /*<<< orphan*/ ,struct component_name*,int) ; 
 int /*<<< orphan*/  dtInsertEntry (TYPE_2__*,int,struct component_name*,TYPE_3__*,struct dt_lock**) ; 
 int dtSplitPage (int /*<<< orphan*/ ,struct inode*,struct dtsplit*,struct metapage**,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int dtSplitRoot (int /*<<< orphan*/ ,struct inode*,struct dtsplit*,struct metapage**) ; 
 int /*<<< orphan*/  jfs_err (char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int lengthPXD (int /*<<< orphan*/ *) ; 
 int tlckDTREE ; 
 int tlckENTRY ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct inode*,struct metapage*,int) ; 

__attribute__((used)) static int dtSplitUp(tid_t tid,
	  struct inode *ip, struct dtsplit * split, struct btstack * btstack)
{
	struct jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	int rc = 0;
	struct metapage *smp;
	dtpage_t *sp;		/* split page */
	struct metapage *rmp;
	dtpage_t *rp;		/* new right page split from sp */
	pxd_t rpxd;		/* new right page extent descriptor */
	struct metapage *lmp;
	dtpage_t *lp;		/* left child page */
	int skip;		/* index of entry of insertion */
	struct btframe *parent;	/* parent page entry on traverse stack */
	s64 xaddr, nxaddr;
	int xlen, xsize;
	struct pxdlist pxdlist;
	pxd_t *pxd;
	struct component_name key = { 0, NULL };
	ddata_t *data = split->data;
	int n;
	struct dt_lock *dtlck;
	struct tlock *tlck;
	struct lv *lv;
	int quota_allocation = 0;

	/* get split page */
	smp = split->mp;
	sp = DT_PAGE(ip, smp);

	key.name = kmalloc_array(JFS_NAME_MAX + 2, sizeof(wchar_t), GFP_NOFS);
	if (!key.name) {
		DT_PUTPAGE(smp);
		rc = -ENOMEM;
		goto dtSplitUp_Exit;
	}

	/*
	 *	split leaf page
	 *
	 * The split routines insert the new entry, and
	 * acquire txLock as appropriate.
	 */
	/*
	 *	split root leaf page:
	 */
	if (sp->header.flag & BT_ROOT) {
		/*
		 * allocate a single extent child page
		 */
		xlen = 1;
		n = sbi->bsize >> L2DTSLOTSIZE;
		n -= (n + 31) >> L2DTSLOTSIZE;	/* stbl size */
		n -= DTROOTMAXSLOT - sp->header.freecnt; /* header + entries */
		if (n <= split->nslot)
			xlen++;
		if ((rc = dbAlloc(ip, 0, (s64) xlen, &xaddr))) {
			DT_PUTPAGE(smp);
			goto freeKeyName;
		}

		pxdlist.maxnpxd = 1;
		pxdlist.npxd = 0;
		pxd = &pxdlist.pxd[0];
		PXDaddress(pxd, xaddr);
		PXDlength(pxd, xlen);
		split->pxdlist = &pxdlist;
		rc = dtSplitRoot(tid, ip, split, &rmp);

		if (rc)
			dbFree(ip, xaddr, xlen);
		else
			DT_PUTPAGE(rmp);

		DT_PUTPAGE(smp);

		if (!DO_INDEX(ip))
			ip->i_size = xlen << sbi->l2bsize;

		goto freeKeyName;
	}

	/*
	 *	extend first leaf page
	 *
	 * extend the 1st extent if less than buffer page size
	 * (dtExtendPage() reurns leaf page unpinned)
	 */
	pxd = &sp->header.self;
	xlen = lengthPXD(pxd);
	xsize = xlen << sbi->l2bsize;
	if (xsize < PSIZE) {
		xaddr = addressPXD(pxd);
		n = xsize >> L2DTSLOTSIZE;
		n -= (n + 31) >> L2DTSLOTSIZE;	/* stbl size */
		if ((n + sp->header.freecnt) <= split->nslot)
			n = xlen + (xlen << 1);
		else
			n = xlen;

		/* Allocate blocks to quota. */
		rc = dquot_alloc_block(ip, n);
		if (rc)
			goto extendOut;
		quota_allocation += n;

		if ((rc = dbReAlloc(sbi->ipbmap, xaddr, (s64) xlen,
				    (s64) n, &nxaddr)))
			goto extendOut;

		pxdlist.maxnpxd = 1;
		pxdlist.npxd = 0;
		pxd = &pxdlist.pxd[0];
		PXDaddress(pxd, nxaddr);
		PXDlength(pxd, xlen + n);
		split->pxdlist = &pxdlist;
		if ((rc = dtExtendPage(tid, ip, split, btstack))) {
			nxaddr = addressPXD(pxd);
			if (xaddr != nxaddr) {
				/* free relocated extent */
				xlen = lengthPXD(pxd);
				dbFree(ip, nxaddr, (s64) xlen);
			} else {
				/* free extended delta */
				xlen = lengthPXD(pxd) - n;
				xaddr = addressPXD(pxd) + xlen;
				dbFree(ip, xaddr, (s64) n);
			}
		} else if (!DO_INDEX(ip))
			ip->i_size = lengthPXD(pxd) << sbi->l2bsize;


	      extendOut:
		DT_PUTPAGE(smp);
		goto freeKeyName;
	}

	/*
	 *	split leaf page <sp> into <sp> and a new right page <rp>.
	 *
	 * return <rp> pinned and its extent descriptor <rpxd>
	 */
	/*
	 * allocate new directory page extent and
	 * new index page(s) to cover page split(s)
	 *
	 * allocation hint: ?
	 */
	n = btstack->nsplit;
	pxdlist.maxnpxd = pxdlist.npxd = 0;
	xlen = sbi->nbperpage;
	for (pxd = pxdlist.pxd; n > 0; n--, pxd++) {
		if ((rc = dbAlloc(ip, 0, (s64) xlen, &xaddr)) == 0) {
			PXDaddress(pxd, xaddr);
			PXDlength(pxd, xlen);
			pxdlist.maxnpxd++;
			continue;
		}

		DT_PUTPAGE(smp);

		/* undo allocation */
		goto splitOut;
	}

	split->pxdlist = &pxdlist;
	if ((rc = dtSplitPage(tid, ip, split, &rmp, &rp, &rpxd))) {
		DT_PUTPAGE(smp);

		/* undo allocation */
		goto splitOut;
	}

	if (!DO_INDEX(ip))
		ip->i_size += PSIZE;

	/*
	 * propagate up the router entry for the leaf page just split
	 *
	 * insert a router entry for the new page into the parent page,
	 * propagate the insert/split up the tree by walking back the stack
	 * of (bn of parent page, index of child page entry in parent page)
	 * that were traversed during the search for the page that split.
	 *
	 * the propagation of insert/split up the tree stops if the root
	 * splits or the page inserted into doesn't have to split to hold
	 * the new entry.
	 *
	 * the parent entry for the split page remains the same, and
	 * a new entry is inserted at its right with the first key and
	 * block number of the new right page.
	 *
	 * There are a maximum of 4 pages pinned at any time:
	 * two children, left parent and right parent (when the parent splits).
	 * keep the child pages pinned while working on the parent.
	 * make sure that all pins are released at exit.
	 */
	while ((parent = BT_POP(btstack)) != NULL) {
		/* parent page specified by stack frame <parent> */

		/* keep current child pages (<lp>, <rp>) pinned */
		lmp = smp;
		lp = sp;

		/*
		 * insert router entry in parent for new right child page <rp>
		 */
		/* get the parent page <sp> */
		DT_GETPAGE(ip, parent->bn, smp, PSIZE, sp, rc);
		if (rc) {
			DT_PUTPAGE(lmp);
			DT_PUTPAGE(rmp);
			goto splitOut;
		}

		/*
		 * The new key entry goes ONE AFTER the index of parent entry,
		 * because the split was to the right.
		 */
		skip = parent->index + 1;

		/*
		 * compute the key for the router entry
		 *
		 * key suffix compression:
		 * for internal pages that have leaf pages as children,
		 * retain only what's needed to distinguish between
		 * the new entry and the entry on the page to its left.
		 * If the keys compare equal, retain the entire key.
		 *
		 * note that compression is performed only at computing
		 * router key at the lowest internal level.
		 * further compression of the key between pairs of higher
		 * level internal pages loses too much information and
		 * the search may fail.
		 * (e.g., two adjacent leaf pages of {a, ..., x} {xx, ...,}
		 * results in two adjacent parent entries (a)(xx).
		 * if split occurs between these two entries, and
		 * if compression is applied, the router key of parent entry
		 * of right page (x) will divert search for x into right
		 * subtree and miss x in the left subtree.)
		 *
		 * the entire key must be retained for the next-to-leftmost
		 * internal key at any level of the tree, or search may fail
		 * (e.g., ?)
		 */
		switch (rp->header.flag & BT_TYPE) {
		case BT_LEAF:
			/*
			 * compute the length of prefix for suffix compression
			 * between last entry of left page and first entry
			 * of right page
			 */
			if ((sp->header.flag & BT_ROOT && skip > 1) ||
			    sp->header.prev != 0 || skip > 1) {
				/* compute uppercase router prefix key */
				rc = ciGetLeafPrefixKey(lp,
							lp->header.nextindex-1,
							rp, 0, &key,
							sbi->mntflag);
				if (rc) {
					DT_PUTPAGE(lmp);
					DT_PUTPAGE(rmp);
					DT_PUTPAGE(smp);
					goto splitOut;
				}
			} else {
				/* next to leftmost entry of
				   lowest internal level */

				/* compute uppercase router key */
				dtGetKey(rp, 0, &key, sbi->mntflag);
				key.name[key.namlen] = 0;

				if ((sbi->mntflag & JFS_OS2) == JFS_OS2)
					ciToUpper(&key);
			}

			n = NDTINTERNAL(key.namlen);
			break;

		case BT_INTERNAL:
			dtGetKey(rp, 0, &key, sbi->mntflag);
			n = NDTINTERNAL(key.namlen);
			break;

		default:
			jfs_err("dtSplitUp(): UFO!");
			break;
		}

		/* unpin left child page */
		DT_PUTPAGE(lmp);

		/*
		 * compute the data for the router entry
		 */
		data->xd = rpxd;	/* child page xd */

		/*
		 * parent page is full - split the parent page
		 */
		if (n > sp->header.freecnt) {
			/* init for parent page split */
			split->mp = smp;
			split->index = skip;	/* index at insert */
			split->nslot = n;
			split->key = &key;
			/* split->data = data; */

			/* unpin right child page */
			DT_PUTPAGE(rmp);

			/* The split routines insert the new entry,
			 * acquire txLock as appropriate.
			 * return <rp> pinned and its block number <rbn>.
			 */
			rc = (sp->header.flag & BT_ROOT) ?
			    dtSplitRoot(tid, ip, split, &rmp) :
			    dtSplitPage(tid, ip, split, &rmp, &rp, &rpxd);
			if (rc) {
				DT_PUTPAGE(smp);
				goto splitOut;
			}

			/* smp and rmp are pinned */
		}
		/*
		 * parent page is not full - insert router entry in parent page
		 */
		else {
			BT_MARK_DIRTY(smp, ip);
			/*
			 * acquire a transaction lock on the parent page
			 */
			tlck = txLock(tid, ip, smp, tlckDTREE | tlckENTRY);
			dtlck = (struct dt_lock *) & tlck->lock;
			ASSERT(dtlck->index == 0);
			lv = & dtlck->lv[0];

			/* linelock header */
			lv->offset = 0;
			lv->length = 1;
			dtlck->index++;

			/* linelock stbl of non-root parent page */
			if (!(sp->header.flag & BT_ROOT)) {
				lv++;
				n = skip >> L2DTSLOTSIZE;
				lv->offset = sp->header.stblindex + n;
				lv->length =
				    ((sp->header.nextindex -
				      1) >> L2DTSLOTSIZE) - n + 1;
				dtlck->index++;
			}

			dtInsertEntry(sp, skip, &key, data, &dtlck);

			/* exit propagate up */
			break;
		}
	}

	/* unpin current split and its right page */
	DT_PUTPAGE(smp);
	DT_PUTPAGE(rmp);

	/*
	 * free remaining extents allocated for split
	 */
      splitOut:
	n = pxdlist.npxd;
	pxd = &pxdlist.pxd[n];
	for (; n < pxdlist.maxnpxd; n++, pxd++)
		dbFree(ip, addressPXD(pxd), (s64) lengthPXD(pxd));

      freeKeyName:
	kfree(key.name);

	/* Rollback quota allocation */
	if (rc && quota_allocation)
		dquot_free_block(ip, quota_allocation);

      dtSplitUp_Exit:

	return rc;
}