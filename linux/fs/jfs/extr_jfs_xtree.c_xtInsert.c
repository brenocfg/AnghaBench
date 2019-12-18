#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nextindex; int /*<<< orphan*/  maxentry; } ;
struct TYPE_7__ {TYPE_1__ header; int /*<<< orphan*/ * xad; } ;
typedef  TYPE_3__ xtpage_t ;
typedef  int /*<<< orphan*/  xad_t ;
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  tid_t ;
struct xtsplit {int index; int flag; int /*<<< orphan*/ * pxdlist; scalar_t__ addr; scalar_t__ len; scalar_t__ off; struct metapage* mp; } ;
struct TYPE_6__ {int offset; int length; } ;
struct xtlock {TYPE_2__ lwm; } ;
struct tlock {int /*<<< orphan*/  lock; } ;
struct metapage {int dummy; } ;
struct inode {int dummy; } ;
struct btstack {int /*<<< orphan*/  top; } ;
typedef  scalar_t__ s64 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MARK_DIRTY (struct metapage*,struct inode*) ; 
 int /*<<< orphan*/  COMMIT_Nolink ; 
 int EEXIST ; 
 int XAD_NEW ; 
 int XTENTRYSTART ; 
 int /*<<< orphan*/  XT_GETSEARCH (struct inode*,int /*<<< orphan*/ ,scalar_t__,struct metapage*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  XT_INSERT ; 
 int /*<<< orphan*/  XT_PUTENTRY (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XT_PUTPAGE (struct metapage*) ; 
 scalar_t__ addressXAD (int /*<<< orphan*/ *) ; 
 int dbAlloc (struct inode*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  dbFree (struct inode*,scalar_t__,scalar_t__) ; 
 int dquot_alloc_block (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  dquot_free_block (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  jfs_info (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ lengthXAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  test_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int tlckGROW ; 
 int tlckXTREE ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct inode*,struct metapage*,int) ; 
 int xtSearch (struct inode*,scalar_t__,scalar_t__*,int*,struct btstack*,int /*<<< orphan*/ ) ; 
 int xtSplitUp (int /*<<< orphan*/ ,struct inode*,struct xtsplit*,struct btstack*) ; 

int xtInsert(tid_t tid,		/* transaction id */
	     struct inode *ip, int xflag, s64 xoff, s32 xlen, s64 * xaddrp,
	     int flag)
{
	int rc = 0;
	s64 xaddr, hint;
	struct metapage *mp;	/* meta-page buffer */
	xtpage_t *p;		/* base B+-tree index page */
	s64 bn;
	int index, nextindex;
	struct btstack btstack;	/* traverse stack */
	struct xtsplit split;	/* split information */
	xad_t *xad;
	int cmp;
	s64 next;
	struct tlock *tlck;
	struct xtlock *xtlck;

	jfs_info("xtInsert: nxoff:0x%lx nxlen:0x%x", (ulong) xoff, xlen);

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

	/* This test must follow XT_GETSEARCH since mp must be valid if
	 * we branch to out: */
	if ((cmp == 0) || (next && (xlen > next - xoff))) {
		rc = -EEXIST;
		goto out;
	}

	/*
	 * allocate data extent requested
	 *
	 * allocation hint: last xad
	 */
	if ((xaddr = *xaddrp) == 0) {
		if (index > XTENTRYSTART) {
			xad = &p->xad[index - 1];
			hint = addressXAD(xad) + lengthXAD(xad) - 1;
		} else
			hint = 0;
		if ((rc = dquot_alloc_block(ip, xlen)))
			goto out;
		if ((rc = dbAlloc(ip, hint, (s64) xlen, &xaddr))) {
			dquot_free_block(ip, xlen);
			goto out;
		}
	}

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
	if (nextindex == le16_to_cpu(p->header.maxentry)) {
		split.mp = mp;
		split.index = index;
		split.flag = xflag;
		split.off = xoff;
		split.len = xlen;
		split.addr = xaddr;
		split.pxdlist = NULL;
		if ((rc = xtSplitUp(tid, ip, &split, &btstack))) {
			/* undo data extent allocation */
			if (*xaddrp == 0) {
				dbFree(ip, xaddr, (s64) xlen);
				dquot_free_block(ip, xlen);
			}
			return rc;
		}

		*xaddrp = xaddr;
		return 0;
	}

	/*
	 *	insert the new entry into the leaf page
	 */
	/*
	 * acquire a transaction lock on the leaf page;
	 *
	 * action: xad insertion/extension;
	 */
	BT_MARK_DIRTY(mp, ip);

	/* if insert into middle, shift right remaining entries. */
	if (index < nextindex)
		memmove(&p->xad[index + 1], &p->xad[index],
			(nextindex - index) * sizeof(xad_t));

	/* insert the new entry: mark the entry NEW */
	xad = &p->xad[index];
	XT_PUTENTRY(xad, xflag, xoff, xlen, xaddr);

	/* advance next available entry index */
	le16_add_cpu(&p->header.nextindex, 1);

	/* Don't log it if there are no links to the file */
	if (!test_cflag(COMMIT_Nolink, ip)) {
		tlck = txLock(tid, ip, mp, tlckXTREE | tlckGROW);
		xtlck = (struct xtlock *) & tlck->lock;
		xtlck->lwm.offset =
		    (xtlck->lwm.offset) ? min(index,
					      (int)xtlck->lwm.offset) : index;
		xtlck->lwm.length =
		    le16_to_cpu(p->header.nextindex) - xtlck->lwm.offset;
	}

	*xaddrp = xaddr;

      out:
	/* unpin the leaf page */
	XT_PUTPAGE(mp);

	return rc;
}