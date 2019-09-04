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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  tid_t ;
struct tlock {int /*<<< orphan*/  lock; } ;
struct tblock {scalar_t__ xflag; } ;
struct metapage {int dummy; } ;
struct lv {int length; scalar_t__ offset; } ;
struct TYPE_3__ {int flag; int freelist; int freecnt; int /*<<< orphan*/  idotdot; scalar_t__ nextindex; } ;
struct TYPE_4__ {TYPE_1__ header; struct dtslot* slot; } ;
struct jfs_inode_info {int next_index; TYPE_2__ i_dtroot; int /*<<< orphan*/  bxflag; } ;
struct inode {int i_size; } ;
struct dtslot {int next; } ;
struct dt_lock {scalar_t__ index; struct lv* lv; } ;
typedef  TYPE_2__ dtroot_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BT_LEAF ; 
 int BT_ROOT ; 
 int /*<<< orphan*/  COMMIT_PWMAP ; 
 int /*<<< orphan*/  COMMIT_Stale ; 
 scalar_t__ DO_INDEX (struct inode*) ; 
 int DTROOTMAXSLOT ; 
 int DXD_INDEX ; 
 int IDATASIZE ; 
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_dirtable_inline (struct inode*) ; 
 int /*<<< orphan*/  set_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 struct tblock* tid_to_tblock (int /*<<< orphan*/ ) ; 
 int tlckBTROOT ; 
 int tlckDTREE ; 
 int tlckENTRY ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct inode*,struct metapage*,int) ; 
 int /*<<< orphan*/  xtTruncate (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dtInitRoot(tid_t tid, struct inode *ip, u32 idotdot)
{
	struct jfs_inode_info *jfs_ip = JFS_IP(ip);
	dtroot_t *p;
	int fsi;
	struct dtslot *f;
	struct tlock *tlck;
	struct dt_lock *dtlck;
	struct lv *lv;
	u16 xflag_save;

	/*
	 * If this was previously an non-empty directory, we need to remove
	 * the old directory table.
	 */
	if (DO_INDEX(ip)) {
		if (!jfs_dirtable_inline(ip)) {
			struct tblock *tblk = tid_to_tblock(tid);
			/*
			 * We're playing games with the tid's xflag.  If
			 * we're removing a regular file, the file's xtree
			 * is committed with COMMIT_PMAP, but we always
			 * commit the directories xtree with COMMIT_PWMAP.
			 */
			xflag_save = tblk->xflag;
			tblk->xflag = 0;
			/*
			 * xtTruncate isn't guaranteed to fully truncate
			 * the xtree.  The caller needs to check i_size
			 * after committing the transaction to see if
			 * additional truncation is needed.  The
			 * COMMIT_Stale flag tells caller that we
			 * initiated the truncation.
			 */
			xtTruncate(tid, ip, 0, COMMIT_PWMAP);
			set_cflag(COMMIT_Stale, ip);

			tblk->xflag = xflag_save;
		} else
			ip->i_size = 1;

		jfs_ip->next_index = 2;
	} else
		ip->i_size = IDATASIZE;

	/*
	 * acquire a transaction lock on the root
	 *
	 * action: directory initialization;
	 */
	tlck = txLock(tid, ip, (struct metapage *) & jfs_ip->bxflag,
		      tlckDTREE | tlckENTRY | tlckBTROOT);
	dtlck = (struct dt_lock *) & tlck->lock;

	/* linelock root */
	ASSERT(dtlck->index == 0);
	lv = & dtlck->lv[0];
	lv->offset = 0;
	lv->length = DTROOTMAXSLOT;
	dtlck->index++;

	p = &jfs_ip->i_dtroot;

	p->header.flag = DXD_INDEX | BT_ROOT | BT_LEAF;

	p->header.nextindex = 0;

	/* init freelist */
	fsi = 1;
	f = &p->slot[fsi];

	/* init data area of root */
	for (fsi++; fsi < DTROOTMAXSLOT; f++, fsi++)
		f->next = fsi;
	f->next = -1;

	p->header.freelist = 1;
	p->header.freecnt = 8;

	/* init '..' entry */
	p->header.idotdot = cpu_to_le32(idotdot);

	return;
}