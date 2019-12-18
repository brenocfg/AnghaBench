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
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_6__ {TYPE_2__* ip; } ;
struct tblock {int xflag; int flag; TYPE_1__ u; scalar_t__ last; scalar_t__ next; int /*<<< orphan*/  logtid; } ;
struct super_block {int dummy; } ;
struct lrd {scalar_t__ length; int /*<<< orphan*/  type; scalar_t__ backchain; int /*<<< orphan*/  logtid; } ;
struct jfs_log {int dummy; } ;
struct jfs_inode_info {scalar_t__ blid; scalar_t__ bxflag; int /*<<< orphan*/  anon_inode_list; scalar_t__ atltail; scalar_t__ atlhead; } ;
struct inode {scalar_t__ i_ino; struct super_block* i_sb; } ;
struct commit {int nip; struct inode** iplist; struct lrd lrd; struct jfs_log* log; int /*<<< orphan*/  tid; struct super_block* sb; } ;
typedef  scalar_t__ ino_t ;
struct TYPE_9__ {struct jfs_log* log; } ;
struct TYPE_8__ {scalar_t__ next; } ;
struct TYPE_7__ {int i_state; scalar_t__ i_nlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int COMMIT_DELETE ; 
 int /*<<< orphan*/  COMMIT_Dirty ; 
 int COMMIT_FORCE ; 
 int COMMIT_LAZY ; 
 int /*<<< orphan*/  COMMIT_Nolink ; 
 int COMMIT_SYNC ; 
 int EROFS ; 
 int I_SYNC ; 
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 TYPE_5__* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  LOG_COMMIT ; 
 int /*<<< orphan*/  TXN_LOCK () ; 
 int /*<<< orphan*/  TXN_UNLOCK () ; 
 int /*<<< orphan*/  clear_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int diWrite (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  ihold (TYPE_2__*) ; 
 scalar_t__ isReadOnly (struct inode*) ; 
 int /*<<< orphan*/  jfs_info (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* lid_to_tlock (scalar_t__) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lmGroupCommit (struct jfs_log*,struct tblock*) ; 
 int /*<<< orphan*/  lmLog (struct jfs_log*,struct tblock*,struct lrd*,int /*<<< orphan*/ *) ; 
 int tblkGC_LAZY ; 
 int /*<<< orphan*/  test_cflag (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct tblock* tid_to_tblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txAbort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  txBegin (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txForce (struct tblock*) ; 
 int txLog (struct jfs_log*,struct tblock*,struct commit*) ; 
 int /*<<< orphan*/  txRelease (struct tblock*) ; 
 int /*<<< orphan*/  txUnlock (struct tblock*) ; 
 int /*<<< orphan*/  txUpdateMap (struct tblock*) ; 

int txCommit(tid_t tid,		/* transaction identifier */
	     int nip,		/* number of inodes to commit */
	     struct inode **iplist,	/* list of inode to commit */
	     int flag)
{
	int rc = 0;
	struct commit cd;
	struct jfs_log *log;
	struct tblock *tblk;
	struct lrd *lrd;
	struct inode *ip;
	struct jfs_inode_info *jfs_ip;
	int k, n;
	ino_t top;
	struct super_block *sb;

	jfs_info("txCommit, tid = %d, flag = %d", tid, flag);
	/* is read-only file system ? */
	if (isReadOnly(iplist[0])) {
		rc = -EROFS;
		goto TheEnd;
	}

	sb = cd.sb = iplist[0]->i_sb;
	cd.tid = tid;

	if (tid == 0)
		tid = txBegin(sb, 0);
	tblk = tid_to_tblock(tid);

	/*
	 * initialize commit structure
	 */
	log = JFS_SBI(sb)->log;
	cd.log = log;

	/* initialize log record descriptor in commit */
	lrd = &cd.lrd;
	lrd->logtid = cpu_to_le32(tblk->logtid);
	lrd->backchain = 0;

	tblk->xflag |= flag;

	if ((flag & (COMMIT_FORCE | COMMIT_SYNC)) == 0)
		tblk->xflag |= COMMIT_LAZY;
	/*
	 *	prepare non-journaled objects for commit
	 *
	 * flush data pages of non-journaled file
	 * to prevent the file getting non-initialized disk blocks
	 * in case of crash.
	 * (new blocks - )
	 */
	cd.iplist = iplist;
	cd.nip = nip;

	/*
	 *	acquire transaction lock on (on-disk) inodes
	 *
	 * update on-disk inode from in-memory inode
	 * acquiring transaction locks for AFTER records
	 * on the on-disk inode of file object
	 *
	 * sort the inodes array by inode number in descending order
	 * to prevent deadlock when acquiring transaction lock
	 * of on-disk inodes on multiple on-disk inode pages by
	 * multiple concurrent transactions
	 */
	for (k = 0; k < cd.nip; k++) {
		top = (cd.iplist[k])->i_ino;
		for (n = k + 1; n < cd.nip; n++) {
			ip = cd.iplist[n];
			if (ip->i_ino > top) {
				top = ip->i_ino;
				cd.iplist[n] = cd.iplist[k];
				cd.iplist[k] = ip;
			}
		}

		ip = cd.iplist[k];
		jfs_ip = JFS_IP(ip);

		/*
		 * BUGBUG - This code has temporarily been removed.  The
		 * intent is to ensure that any file data is written before
		 * the metadata is committed to the journal.  This prevents
		 * uninitialized data from appearing in a file after the
		 * journal has been replayed.  (The uninitialized data
		 * could be sensitive data removed by another user.)
		 *
		 * The problem now is that we are holding the IWRITELOCK
		 * on the inode, and calling filemap_fdatawrite on an
		 * unmapped page will cause a deadlock in jfs_get_block.
		 *
		 * The long term solution is to pare down the use of
		 * IWRITELOCK.  We are currently holding it too long.
		 * We could also be smarter about which data pages need
		 * to be written before the transaction is committed and
		 * when we don't need to worry about it at all.
		 *
		 * if ((!S_ISDIR(ip->i_mode))
		 *    && (tblk->flag & COMMIT_DELETE) == 0)
		 *	filemap_write_and_wait(ip->i_mapping);
		 */

		/*
		 * Mark inode as not dirty.  It will still be on the dirty
		 * inode list, but we'll know not to commit it again unless
		 * it gets marked dirty again
		 */
		clear_cflag(COMMIT_Dirty, ip);

		/* inherit anonymous tlock(s) of inode */
		if (jfs_ip->atlhead) {
			lid_to_tlock(jfs_ip->atltail)->next = tblk->next;
			tblk->next = jfs_ip->atlhead;
			if (!tblk->last)
				tblk->last = jfs_ip->atltail;
			jfs_ip->atlhead = jfs_ip->atltail = 0;
			TXN_LOCK();
			list_del_init(&jfs_ip->anon_inode_list);
			TXN_UNLOCK();
		}

		/*
		 * acquire transaction lock on on-disk inode page
		 * (become first tlock of the tblk's tlock list)
		 */
		if (((rc = diWrite(tid, ip))))
			goto out;
	}

	/*
	 *	write log records from transaction locks
	 *
	 * txUpdateMap() resets XAD_NEW in XAD.
	 */
	if ((rc = txLog(log, tblk, &cd)))
		goto TheEnd;

	/*
	 * Ensure that inode isn't reused before
	 * lazy commit thread finishes processing
	 */
	if (tblk->xflag & COMMIT_DELETE) {
		ihold(tblk->u.ip);
		/*
		 * Avoid a rare deadlock
		 *
		 * If the inode is locked, we may be blocked in
		 * jfs_commit_inode.  If so, we don't want the
		 * lazy_commit thread doing the last iput() on the inode
		 * since that may block on the locked inode.  Instead,
		 * commit the transaction synchronously, so the last iput
		 * will be done by the calling thread (or later)
		 */
		/*
		 * I believe this code is no longer needed.  Splitting I_LOCK
		 * into two bits, I_NEW and I_SYNC should prevent this
		 * deadlock as well.  But since I don't have a JFS testload
		 * to verify this, only a trivial s/I_LOCK/I_SYNC/ was done.
		 * Joern
		 */
		if (tblk->u.ip->i_state & I_SYNC)
			tblk->xflag &= ~COMMIT_LAZY;
	}

	ASSERT((!(tblk->xflag & COMMIT_DELETE)) ||
	       ((tblk->u.ip->i_nlink == 0) &&
		!test_cflag(COMMIT_Nolink, tblk->u.ip)));

	/*
	 *	write COMMIT log record
	 */
	lrd->type = cpu_to_le16(LOG_COMMIT);
	lrd->length = 0;
	lmLog(log, tblk, lrd, NULL);

	lmGroupCommit(log, tblk);

	/*
	 *	- transaction is now committed -
	 */

	/*
	 * force pages in careful update
	 * (imap addressing structure update)
	 */
	if (flag & COMMIT_FORCE)
		txForce(tblk);

	/*
	 *	update allocation map.
	 *
	 * update inode allocation map and inode:
	 * free pager lock on memory object of inode if any.
	 * update block allocation map.
	 *
	 * txUpdateMap() resets XAD_NEW in XAD.
	 */
	if (tblk->xflag & COMMIT_FORCE)
		txUpdateMap(tblk);

	/*
	 *	free transaction locks and pageout/free pages
	 */
	txRelease(tblk);

	if ((tblk->flag & tblkGC_LAZY) == 0)
		txUnlock(tblk);


	/*
	 *	reset in-memory object state
	 */
	for (k = 0; k < cd.nip; k++) {
		ip = cd.iplist[k];
		jfs_ip = JFS_IP(ip);

		/*
		 * reset in-memory inode state
		 */
		jfs_ip->bxflag = 0;
		jfs_ip->blid = 0;
	}

      out:
	if (rc != 0)
		txAbort(tid, 1);

      TheEnd:
	jfs_info("txCommit: tid = %d, returning %d", tid, rc);
	return rc;
}