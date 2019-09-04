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
typedef  int u32 ;
struct tblock {int lsn; int clsn; int /*<<< orphan*/  synclist; int /*<<< orphan*/  sb; } ;
struct metapage {int lsn; int clsn; int /*<<< orphan*/  synclist; struct jfs_log* log; scalar_t__ data; } ;
struct jfs_log {int /*<<< orphan*/  count; } ;
struct inomap {int im_nextiag; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct iag {int /*<<< orphan*/ * pmap; int /*<<< orphan*/ * wmap; } ;
struct TYPE_4__ {struct inomap* i_imap; } ;
struct TYPE_3__ {struct jfs_log* log; } ;

/* Variables and functions */
 int EIO ; 
 int HIGHORDER ; 
 int INOSPEREXT ; 
 int INOSPERIAG ; 
 int INOTOIAG (unsigned long) ; 
 int /*<<< orphan*/  IREAD_LOCK (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IREAD_UNLOCK (struct inode*) ; 
 TYPE_2__* JFS_IP (struct inode*) ; 
 TYPE_1__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int L2INOSPEREXT ; 
 int /*<<< orphan*/  LOGSYNC_LOCK (struct jfs_log*,unsigned long) ; 
 int /*<<< orphan*/  LOGSYNC_UNLOCK (struct jfs_log*,unsigned long) ; 
 int /*<<< orphan*/  RDWRLOCK_IMAP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int diIAGRead (struct inomap*,int,struct metapage**) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logdiff (int,int,struct jfs_log*) ; 
 int /*<<< orphan*/  metapage_wait_for_io (struct metapage*) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 int /*<<< orphan*/  write_metapage (struct metapage*) ; 

int
diUpdatePMap(struct inode *ipimap,
	     unsigned long inum, bool is_free, struct tblock * tblk)
{
	int rc;
	struct iag *iagp;
	struct metapage *mp;
	int iagno, ino, extno, bitno;
	struct inomap *imap;
	u32 mask;
	struct jfs_log *log;
	int lsn, difft, diffp;
	unsigned long flags;

	imap = JFS_IP(ipimap)->i_imap;
	/* get the iag number containing the inode */
	iagno = INOTOIAG(inum);
	/* make sure that the iag is contained within the map */
	if (iagno >= imap->im_nextiag) {
		jfs_error(ipimap->i_sb, "the iag is outside the map\n");
		return -EIO;
	}
	/* read the iag */
	IREAD_LOCK(ipimap, RDWRLOCK_IMAP);
	rc = diIAGRead(imap, iagno, &mp);
	IREAD_UNLOCK(ipimap);
	if (rc)
		return (rc);
	metapage_wait_for_io(mp);
	iagp = (struct iag *) mp->data;
	/* get the inode number and extent number of the inode within
	 * the iag and the inode number within the extent.
	 */
	ino = inum & (INOSPERIAG - 1);
	extno = ino >> L2INOSPEREXT;
	bitno = ino & (INOSPEREXT - 1);
	mask = HIGHORDER >> bitno;
	/*
	 * mark the inode free in persistent map:
	 */
	if (is_free) {
		/* The inode should have been allocated both in working
		 * map and in persistent map;
		 * the inode will be freed from working map at the release
		 * of last reference release;
		 */
		if (!(le32_to_cpu(iagp->wmap[extno]) & mask)) {
			jfs_error(ipimap->i_sb,
				  "inode %ld not marked as allocated in wmap!\n",
				  inum);
		}
		if (!(le32_to_cpu(iagp->pmap[extno]) & mask)) {
			jfs_error(ipimap->i_sb,
				  "inode %ld not marked as allocated in pmap!\n",
				  inum);
		}
		/* update the bitmap for the extent of the freed inode */
		iagp->pmap[extno] &= cpu_to_le32(~mask);
	}
	/*
	 * mark the inode allocated in persistent map:
	 */
	else {
		/* The inode should be already allocated in the working map
		 * and should be free in persistent map;
		 */
		if (!(le32_to_cpu(iagp->wmap[extno]) & mask)) {
			release_metapage(mp);
			jfs_error(ipimap->i_sb,
				  "the inode is not allocated in the working map\n");
			return -EIO;
		}
		if ((le32_to_cpu(iagp->pmap[extno]) & mask) != 0) {
			release_metapage(mp);
			jfs_error(ipimap->i_sb,
				  "the inode is not free in the persistent map\n");
			return -EIO;
		}
		/* update the bitmap for the extent of the allocated inode */
		iagp->pmap[extno] |= cpu_to_le32(mask);
	}
	/*
	 * update iag lsn
	 */
	lsn = tblk->lsn;
	log = JFS_SBI(tblk->sb)->log;
	LOGSYNC_LOCK(log, flags);
	if (mp->lsn != 0) {
		/* inherit older/smaller lsn */
		logdiff(difft, lsn, log);
		logdiff(diffp, mp->lsn, log);
		if (difft < diffp) {
			mp->lsn = lsn;
			/* move mp after tblock in logsync list */
			list_move(&mp->synclist, &tblk->synclist);
		}
		/* inherit younger/larger clsn */
		assert(mp->clsn);
		logdiff(difft, tblk->clsn, log);
		logdiff(diffp, mp->clsn, log);
		if (difft > diffp)
			mp->clsn = tblk->clsn;
	} else {
		mp->log = log;
		mp->lsn = lsn;
		/* insert mp after tblock in logsync list */
		log->count++;
		list_add(&mp->synclist, &tblk->synclist);
		mp->clsn = tblk->clsn;
	}
	LOGSYNC_UNLOCK(log, flags);
	write_metapage(mp);
	return (0);
}