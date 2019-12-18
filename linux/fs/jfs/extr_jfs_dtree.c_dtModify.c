#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct tlock {int /*<<< orphan*/  lock; } ;
struct metapage {int dummy; } ;
struct lv {int offset; int length; } ;
struct ldtentry {int /*<<< orphan*/  inumber; } ;
struct inode {int dummy; } ;
struct dt_lock {int /*<<< orphan*/  index; struct lv* lv; } ;
struct component_name {int dummy; } ;
struct btstack {int /*<<< orphan*/  top; } ;
typedef  int s8 ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_4__ {int /*<<< orphan*/ * slot; } ;
typedef  TYPE_1__ dtpage_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BT_MARK_DIRTY (struct metapage*,struct inode*) ; 
 int /*<<< orphan*/  DT_GETSEARCH (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct metapage*,TYPE_1__*,int) ; 
 int* DT_GETSTBL (TYPE_1__*) ; 
 int /*<<< orphan*/  DT_PUTPAGE (struct metapage*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int dtSearch (struct inode*,struct component_name*,int /*<<< orphan*/ *,struct btstack*,int) ; 
 int tlckDTREE ; 
 int tlckENTRY ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct inode*,struct metapage*,int) ; 

int dtModify(tid_t tid, struct inode *ip,
	 struct component_name * key, ino_t * orig_ino, ino_t new_ino, int flag)
{
	int rc;
	s64 bn;
	struct metapage *mp;
	dtpage_t *p;
	int index;
	struct btstack btstack;
	struct tlock *tlck;
	struct dt_lock *dtlck;
	struct lv *lv;
	s8 *stbl;
	int entry_si;		/* entry slot index */
	struct ldtentry *entry;

	/*
	 *	search for the entry to modify:
	 *
	 * dtSearch() returns (leaf page pinned, index at which to modify).
	 */
	if ((rc = dtSearch(ip, key, orig_ino, &btstack, flag)))
		return rc;

	/* retrieve search result */
	DT_GETSEARCH(ip, btstack.top, bn, mp, p, index);

	BT_MARK_DIRTY(mp, ip);
	/*
	 * acquire a transaction lock on the leaf page of named entry
	 */
	tlck = txLock(tid, ip, mp, tlckDTREE | tlckENTRY);
	dtlck = (struct dt_lock *) & tlck->lock;

	/* get slot index of the entry */
	stbl = DT_GETSTBL(p);
	entry_si = stbl[index];

	/* linelock entry */
	ASSERT(dtlck->index == 0);
	lv = & dtlck->lv[0];
	lv->offset = entry_si;
	lv->length = 1;
	dtlck->index++;

	/* get the head/only segment */
	entry = (struct ldtentry *) & p->slot[entry_si];

	/* substitute the inode number of the entry */
	entry->inumber = cpu_to_le32(new_ino);

	/* unpin the leaf page */
	DT_PUTPAGE(mp);

	return 0;
}