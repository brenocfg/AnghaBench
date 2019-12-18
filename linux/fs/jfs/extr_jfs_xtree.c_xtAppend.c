#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  nextindex; int /*<<< orphan*/  maxentry; } ;
struct TYPE_8__ {TYPE_1__ header; int /*<<< orphan*/ * xad; } ;
typedef  TYPE_3__ xtpage_t ;
typedef  int /*<<< orphan*/  xad_t ;
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  tid_t ;
struct xtsplit {int index; int flag; int len; void* addr; void* off; struct metapage* mp; struct pxdlist* pxdlist; } ;
struct TYPE_7__ {int offset; int length; } ;
struct xtlock {TYPE_2__ lwm; } ;
struct tlock {int /*<<< orphan*/  lock; } ;
struct pxdlist {scalar_t__ maxnpxd; int /*<<< orphan*/ * pxd; scalar_t__ npxd; } ;
struct metapage {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btstack {int nsplit; int /*<<< orphan*/  top; } ;
typedef  void* s64 ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  pxd_t ;
struct TYPE_9__ {int nbperpage; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MARK_DIRTY (struct metapage*,struct inode*) ; 
 int EEXIST ; 
 TYPE_5__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PXDaddress (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  PXDlength (int /*<<< orphan*/ *,int) ; 
 int XAD_NEW ; 
 int /*<<< orphan*/  XT_GETSEARCH (struct inode*,int /*<<< orphan*/ ,void*,struct metapage*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  XT_INSERT ; 
 int /*<<< orphan*/  XT_PUTENTRY (int /*<<< orphan*/ *,int,void*,int,void*) ; 
 int /*<<< orphan*/  XT_PUTPAGE (struct metapage*) ; 
 int dbAllocBottomUp (struct inode*,void*,void*) ; 
 int /*<<< orphan*/  dbFree (struct inode*,void*,void*) ; 
 int /*<<< orphan*/  jfs_info (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int tlckGROW ; 
 int tlckXTREE ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct inode*,struct metapage*,int) ; 
 int xtSearch (struct inode*,void*,void**,int*,struct btstack*,int /*<<< orphan*/ ) ; 
 int xtSplitUp (int /*<<< orphan*/ ,struct inode*,struct xtsplit*,struct btstack*) ; 

int xtAppend(tid_t tid,		/* transaction id */
	     struct inode *ip, int xflag, s64 xoff, s32 maxblocks,
	     s32 * xlenp,	/* (in/out) */
	     s64 * xaddrp,	/* (in/out) */
	     int flag)
{
	int rc = 0;
	struct metapage *mp;	/* meta-page buffer */
	xtpage_t *p;		/* base B+-tree index page */
	s64 bn, xaddr;
	int index, nextindex;
	struct btstack btstack;	/* traverse stack */
	struct xtsplit split;	/* split information */
	xad_t *xad;
	int cmp;
	struct tlock *tlck;
	struct xtlock *xtlck;
	int nsplit, nblocks, xlen;
	struct pxdlist pxdlist;
	pxd_t *pxd;
	s64 next;

	xaddr = *xaddrp;
	xlen = *xlenp;
	jfs_info("xtAppend: xoff:0x%lx maxblocks:%d xlen:%d xaddr:0x%lx",
		 (ulong) xoff, maxblocks, xlen, (ulong) xaddr);

	/*
	 *	search for the entry location at which to insert:
	 *
	 * xtFastSearch() and xtSearch() both returns (leaf page
	 * pinned, index at which to insert).
	 * n.b. xtSearch() may return index of maxentry of
	 * the full page.
	 */
	if ((rc = xtSearch(ip, xoff, &next, &cmp, &btstack, XT_INSERT)))
		return rc;

	/* retrieve search result */
	XT_GETSEARCH(ip, btstack.top, bn, mp, p, index);

	if (cmp == 0) {
		rc = -EEXIST;
		goto out;
	}

	if (next)
		xlen = min(xlen, (int)(next - xoff));
//insert:
	/*
	 *	insert entry for new extent
	 */
	xflag |= XAD_NEW;

	/*
	 *	if the leaf page is full, split the page and
	 *	propagate up the router entry for the new page from split
	 *
	 * The xtSplitUp() will insert the entry and unpin the leaf page.
	 */
	nextindex = le16_to_cpu(p->header.nextindex);
	if (nextindex < le16_to_cpu(p->header.maxentry))
		goto insertLeaf;

	/*
	 * allocate new index blocks to cover index page split(s)
	 */
	nsplit = btstack.nsplit;
	split.pxdlist = &pxdlist;
	pxdlist.maxnpxd = pxdlist.npxd = 0;
	pxd = &pxdlist.pxd[0];
	nblocks = JFS_SBI(ip->i_sb)->nbperpage;
	for (; nsplit > 0; nsplit--, pxd++, xaddr += nblocks, maxblocks -= nblocks) {
		if ((rc = dbAllocBottomUp(ip, xaddr, (s64) nblocks)) == 0) {
			PXDaddress(pxd, xaddr);
			PXDlength(pxd, nblocks);

			pxdlist.maxnpxd++;

			continue;
		}

		/* undo allocation */

		goto out;
	}

	xlen = min(xlen, maxblocks);

	/*
	 * allocate data extent requested
	 */
	if ((rc = dbAllocBottomUp(ip, xaddr, (s64) xlen)))
		goto out;

	split.mp = mp;
	split.index = index;
	split.flag = xflag;
	split.off = xoff;
	split.len = xlen;
	split.addr = xaddr;
	if ((rc = xtSplitUp(tid, ip, &split, &btstack))) {
		/* undo data extent allocation */
		dbFree(ip, *xaddrp, (s64) * xlenp);

		return rc;
	}

	*xaddrp = xaddr;
	*xlenp = xlen;
	return 0;

	/*
	 *	insert the new entry into the leaf page
	 */
      insertLeaf:
	/*
	 * allocate data extent requested
	 */
	if ((rc = dbAllocBottomUp(ip, xaddr, (s64) xlen)))
		goto out;

	BT_MARK_DIRTY(mp, ip);
	/*
	 * acquire a transaction lock on the leaf page;
	 *
	 * action: xad insertion/extension;
	 */
	tlck = txLock(tid, ip, mp, tlckXTREE | tlckGROW);
	xtlck = (struct xtlock *) & tlck->lock;

	/* insert the new entry: mark the entry NEW */
	xad = &p->xad[index];
	XT_PUTENTRY(xad, xflag, xoff, xlen, xaddr);

	/* advance next available entry index */
	le16_add_cpu(&p->header.nextindex, 1);

	xtlck->lwm.offset =
	    (xtlck->lwm.offset) ? min(index,(int) xtlck->lwm.offset) : index;
	xtlck->lwm.length = le16_to_cpu(p->header.nextindex) -
	    xtlck->lwm.offset;

	*xaddrp = xaddr;
	*xlenp = xlen;

      out:
	/* unpin the leaf page */
	XT_PUTPAGE(mp);

	return rc;
}