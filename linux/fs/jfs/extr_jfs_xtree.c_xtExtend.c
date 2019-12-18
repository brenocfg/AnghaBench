#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int flag; int /*<<< orphan*/  nextindex; int /*<<< orphan*/  maxentry; } ;
struct TYPE_14__ {TYPE_1__ header; TYPE_4__* xad; } ;
typedef  TYPE_3__ xtpage_t ;
struct TYPE_15__ {int flag; } ;
typedef  TYPE_4__ xad_t ;
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  tid_t ;
struct xtsplit {int index; int flag; int len; int /*<<< orphan*/ * pxdlist; scalar_t__ addr; scalar_t__ off; struct metapage* mp; } ;
struct TYPE_13__ {int offset; int length; } ;
struct xtlock {TYPE_2__ lwm; } ;
struct tlock {int /*<<< orphan*/  lock; } ;
struct metapage {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btstack {int /*<<< orphan*/  top; } ;
typedef  scalar_t__ s64 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BT_INTERNAL ; 
 int /*<<< orphan*/  BT_MARK_DIRTY (struct metapage*,struct inode*) ; 
 int /*<<< orphan*/  COMMIT_Nolink ; 
 int EIO ; 
 scalar_t__ MAXXLEN ; 
 int /*<<< orphan*/  PSIZE ; 
 int XAD_EXTENDED ; 
 int XAD_NEW ; 
 int /*<<< orphan*/  XADlength (TYPE_4__*,scalar_t__) ; 
 int XTENTRYSTART ; 
 int /*<<< orphan*/  XT_GETPAGE (struct inode*,scalar_t__,struct metapage*,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  XT_GETSEARCH (struct inode*,int /*<<< orphan*/ ,scalar_t__,struct metapage*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  XT_INSERT ; 
 int /*<<< orphan*/  XT_PUTENTRY (TYPE_4__*,int,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  XT_PUTPAGE (struct metapage*) ; 
 scalar_t__ addressXAD (TYPE_4__*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jfs_info (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ lengthXAD (TYPE_4__*) ; 
 int min (int,int) ; 
 scalar_t__ offsetXAD (TYPE_4__*) ; 
 int /*<<< orphan*/  test_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int tlckGROW ; 
 int tlckXTREE ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct inode*,struct metapage*,int) ; 
 int xtSearch (struct inode*,scalar_t__,int /*<<< orphan*/ *,int*,struct btstack*,int /*<<< orphan*/ ) ; 
 int xtSplitUp (int /*<<< orphan*/ ,struct inode*,struct xtsplit*,struct btstack*) ; 

int xtExtend(tid_t tid,		/* transaction id */
	     struct inode *ip, s64 xoff,	/* delta extent offset */
	     s32 xlen,		/* delta extent length */
	     int flag)
{
	int rc = 0;
	int cmp;
	struct metapage *mp;	/* meta-page buffer */
	xtpage_t *p;		/* base B+-tree index page */
	s64 bn;
	int index, nextindex, len;
	struct btstack btstack;	/* traverse stack */
	struct xtsplit split;	/* split information */
	xad_t *xad;
	s64 xaddr;
	struct tlock *tlck;
	struct xtlock *xtlck = NULL;

	jfs_info("xtExtend: nxoff:0x%lx nxlen:0x%x", (ulong) xoff, xlen);

	/* there must exist extent to be extended */
	if ((rc = xtSearch(ip, xoff - 1, NULL, &cmp, &btstack, XT_INSERT)))
		return rc;

	/* retrieve search result */
	XT_GETSEARCH(ip, btstack.top, bn, mp, p, index);

	if (cmp != 0) {
		XT_PUTPAGE(mp);
		jfs_error(ip->i_sb, "xtSearch did not find extent\n");
		return -EIO;
	}

	/* extension must be contiguous */
	xad = &p->xad[index];
	if ((offsetXAD(xad) + lengthXAD(xad)) != xoff) {
		XT_PUTPAGE(mp);
		jfs_error(ip->i_sb, "extension is not contiguous\n");
		return -EIO;
	}

	/*
	 * acquire a transaction lock on the leaf page;
	 *
	 * action: xad insertion/extension;
	 */
	BT_MARK_DIRTY(mp, ip);
	if (!test_cflag(COMMIT_Nolink, ip)) {
		tlck = txLock(tid, ip, mp, tlckXTREE | tlckGROW);
		xtlck = (struct xtlock *) & tlck->lock;
	}

	/* extend will overflow extent ? */
	xlen = lengthXAD(xad) + xlen;
	if ((len = xlen - MAXXLEN) <= 0)
		goto extendOld;

	/*
	 *	extent overflow: insert entry for new extent
	 */
//insertNew:
	xoff = offsetXAD(xad) + MAXXLEN;
	xaddr = addressXAD(xad) + MAXXLEN;
	nextindex = le16_to_cpu(p->header.nextindex);

	/*
	 *	if the leaf page is full, insert the new entry and
	 *	propagate up the router entry for the new page from split
	 *
	 * The xtSplitUp() will insert the entry and unpin the leaf page.
	 */
	if (nextindex == le16_to_cpu(p->header.maxentry)) {
		/* xtSpliUp() unpins leaf pages */
		split.mp = mp;
		split.index = index + 1;
		split.flag = XAD_NEW;
		split.off = xoff;	/* split offset */
		split.len = len;
		split.addr = xaddr;
		split.pxdlist = NULL;
		if ((rc = xtSplitUp(tid, ip, &split, &btstack)))
			return rc;

		/* get back old page */
		XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
		if (rc)
			return rc;
		/*
		 * if leaf root has been split, original root has been
		 * copied to new child page, i.e., original entry now
		 * resides on the new child page;
		 */
		if (p->header.flag & BT_INTERNAL) {
			ASSERT(p->header.nextindex ==
			       cpu_to_le16(XTENTRYSTART + 1));
			xad = &p->xad[XTENTRYSTART];
			bn = addressXAD(xad);
			XT_PUTPAGE(mp);

			/* get new child page */
			XT_GETPAGE(ip, bn, mp, PSIZE, p, rc);
			if (rc)
				return rc;

			BT_MARK_DIRTY(mp, ip);
			if (!test_cflag(COMMIT_Nolink, ip)) {
				tlck = txLock(tid, ip, mp, tlckXTREE|tlckGROW);
				xtlck = (struct xtlock *) & tlck->lock;
			}
		}
	}
	/*
	 *	insert the new entry into the leaf page
	 */
	else {
		/* insert the new entry: mark the entry NEW */
		xad = &p->xad[index + 1];
		XT_PUTENTRY(xad, XAD_NEW, xoff, len, xaddr);

		/* advance next available entry index */
		le16_add_cpu(&p->header.nextindex, 1);
	}

	/* get back old entry */
	xad = &p->xad[index];
	xlen = MAXXLEN;

	/*
	 * extend old extent
	 */
      extendOld:
	XADlength(xad, xlen);
	if (!(xad->flag & XAD_NEW))
		xad->flag |= XAD_EXTENDED;

	if (!test_cflag(COMMIT_Nolink, ip)) {
		xtlck->lwm.offset =
		    (xtlck->lwm.offset) ? min(index,
					      (int)xtlck->lwm.offset) : index;
		xtlck->lwm.length =
		    le16_to_cpu(p->header.nextindex) - xtlck->lwm.offset;
	}

	/* unpin the leaf page */
	XT_PUTPAGE(mp);

	return rc;
}