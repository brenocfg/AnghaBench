#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct tlock {int /*<<< orphan*/  lock; } ;
struct metapage {int dummy; } ;
struct lv {int length; scalar_t__ offset; } ;
struct inode {int dummy; } ;
struct dtsplit {int index; int nslot; TYPE_4__* data; struct component_name* key; struct metapage* mp; } ;
struct dt_lock {size_t index; size_t maxcnt; struct lv* lv; } ;
struct component_name {int /*<<< orphan*/  namlen; } ;
struct btstack {int /*<<< orphan*/  top; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_10__ {int freecnt; int flag; int nextindex; scalar_t__ stblindex; } ;
struct TYPE_11__ {TYPE_2__ header; } ;
typedef  TYPE_3__ dtpage_t ;
struct TYPE_9__ {int /*<<< orphan*/  ino; struct inode* ip; int /*<<< orphan*/  tid; } ;
struct TYPE_12__ {TYPE_1__ leaf; } ;
typedef  TYPE_4__ ddata_t ;
struct TYPE_13__ {scalar_t__ next_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BT_MARK_DIRTY (struct metapage*,struct inode*) ; 
 int BT_ROOT ; 
 scalar_t__ DIREND ; 
 scalar_t__ DO_INDEX (struct inode*) ; 
 int /*<<< orphan*/  DT_GETSEARCH (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct metapage*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  DT_PUTPAGE (struct metapage*) ; 
 int EMLINK ; 
 TYPE_7__* JFS_IP (struct inode*) ; 
 int L2DTSLOTSIZE ; 
 int NDTLEAF (int /*<<< orphan*/ ) ; 
 int NDTLEAF_LEGACY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtInsertEntry (TYPE_3__*,int,struct component_name*,TYPE_4__*,struct dt_lock**) ; 
 int dtSplitUp (int /*<<< orphan*/ ,struct inode*,struct dtsplit*,struct btstack*) ; 
 int tlckDTREE ; 
 int tlckENTRY ; 
 scalar_t__ txLinelock (struct dt_lock*) ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct inode*,struct metapage*,int) ; 

int dtInsert(tid_t tid, struct inode *ip,
	 struct component_name * name, ino_t * fsn, struct btstack * btstack)
{
	int rc = 0;
	struct metapage *mp;	/* meta-page buffer */
	dtpage_t *p;		/* base B+-tree index page */
	s64 bn;
	int index;
	struct dtsplit split;	/* split information */
	ddata_t data;
	struct dt_lock *dtlck;
	int n;
	struct tlock *tlck;
	struct lv *lv;

	/*
	 *	retrieve search result
	 *
	 * dtSearch() returns (leaf page pinned, index at which to insert).
	 * n.b. dtSearch() may return index of (maxindex + 1) of
	 * the full page.
	 */
	DT_GETSEARCH(ip, btstack->top, bn, mp, p, index);

	/*
	 *	insert entry for new key
	 */
	if (DO_INDEX(ip)) {
		if (JFS_IP(ip)->next_index == DIREND) {
			DT_PUTPAGE(mp);
			return -EMLINK;
		}
		n = NDTLEAF(name->namlen);
		data.leaf.tid = tid;
		data.leaf.ip = ip;
	} else {
		n = NDTLEAF_LEGACY(name->namlen);
		data.leaf.ip = NULL;	/* signifies legacy directory format */
	}
	data.leaf.ino = *fsn;

	/*
	 *	leaf page does not have enough room for new entry:
	 *
	 *	extend/split the leaf page;
	 *
	 * dtSplitUp() will insert the entry and unpin the leaf page.
	 */
	if (n > p->header.freecnt) {
		split.mp = mp;
		split.index = index;
		split.nslot = n;
		split.key = name;
		split.data = &data;
		rc = dtSplitUp(tid, ip, &split, btstack);
		return rc;
	}

	/*
	 *	leaf page does have enough room for new entry:
	 *
	 *	insert the new data entry into the leaf page;
	 */
	BT_MARK_DIRTY(mp, ip);
	/*
	 * acquire a transaction lock on the leaf page
	 */
	tlck = txLock(tid, ip, mp, tlckDTREE | tlckENTRY);
	dtlck = (struct dt_lock *) & tlck->lock;
	ASSERT(dtlck->index == 0);
	lv = & dtlck->lv[0];

	/* linelock header */
	lv->offset = 0;
	lv->length = 1;
	dtlck->index++;

	dtInsertEntry(p, index, name, &data, &dtlck);

	/* linelock stbl of non-root leaf page */
	if (!(p->header.flag & BT_ROOT)) {
		if (dtlck->index >= dtlck->maxcnt)
			dtlck = (struct dt_lock *) txLinelock(dtlck);
		lv = & dtlck->lv[dtlck->index];
		n = index >> L2DTSLOTSIZE;
		lv->offset = p->header.stblindex + n;
		lv->length =
		    ((p->header.nextindex - 1) >> L2DTSLOTSIZE) - n + 1;
		dtlck->index++;
	}

	/* unpin the leaf page */
	DT_PUTPAGE(mp);

	return 0;
}