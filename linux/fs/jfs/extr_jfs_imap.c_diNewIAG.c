#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct super_block {int dummy; } ;
struct metapage {scalar_t__ data; } ;
struct jfs_sb_info {int nbperpage; int /*<<< orphan*/  l2nbperpage; } ;
struct inomap {int im_freeiag; scalar_t__ im_nextiag; struct inode* im_ipimap; } ;
struct inode {int i_size; struct super_block* i_sb; } ;
struct iag {void* iagfree; void** inosmap; void* nfreeexts; scalar_t__ nfreeinos; void* extfreeback; void* extfreefwd; void* inofreeback; void* inofreefwd; void* iagnum; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_2__ {int /*<<< orphan*/  commit_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_FORCE ; 
 int /*<<< orphan*/  COMMIT_PWMAP ; 
 int EIO ; 
 int ENOSPC ; 
 int EXTSPERIAG ; 
 int /*<<< orphan*/  IAGFREE_LOCK (struct inomap*) ; 
 int /*<<< orphan*/  IAGFREE_UNLOCK (struct inomap*) ; 
 int /*<<< orphan*/  IAGTOLBLK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IREAD_LOCK (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IREAD_UNLOCK (struct inode*) ; 
 int /*<<< orphan*/  IWRITE_LOCK (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWRITE_UNLOCK (struct inode*) ; 
 TYPE_1__* JFS_IP (struct inode*) ; 
 struct jfs_sb_info* JFS_SBI (struct super_block*) ; 
 scalar_t__ L2PSIZE ; 
 int MAXIAGS ; 
 int ONES ; 
 int PSIZE ; 
 int /*<<< orphan*/  RDWRLOCK_IMAP ; 
 int SMAPSZ ; 
 void* cpu_to_le32 (int) ; 
 int dbAlloc (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbFree (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int diIAGRead (struct inomap*,int,struct metapage**) ; 
 int /*<<< orphan*/  diSync (struct inode*) ; 
 int /*<<< orphan*/  duplicateIXtree (struct super_block*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_metapage (struct metapage*) ; 
 struct metapage* get_metapage (struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_add_bytes (struct inode*,int) ; 
 int /*<<< orphan*/  jfs_error (struct super_block*,char*) ; 
 int le32_to_cpu (void*) ; 
 int /*<<< orphan*/  memset (struct iag*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txAbort (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txBegin (struct super_block*,int /*<<< orphan*/ ) ; 
 int txCommit (int /*<<< orphan*/ ,int,struct inode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 
 int xtInsert (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtTruncate (int /*<<< orphan*/ ,struct inode*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
diNewIAG(struct inomap * imap, int *iagnop, int agno, struct metapage ** mpp)
{
	int rc;
	int iagno, i, xlen;
	struct inode *ipimap;
	struct super_block *sb;
	struct jfs_sb_info *sbi;
	struct metapage *mp;
	struct iag *iagp;
	s64 xaddr = 0;
	s64 blkno;
	tid_t tid;
	struct inode *iplist[1];

	/* pick up pointers to the inode map and mount inodes */
	ipimap = imap->im_ipimap;
	sb = ipimap->i_sb;
	sbi = JFS_SBI(sb);

	/* acquire the free iag lock */
	IAGFREE_LOCK(imap);

	/* if there are any iags on the inode map free iag list,
	 * allocate the iag from the head of the list.
	 */
	if (imap->im_freeiag >= 0) {
		/* pick up the iag number at the head of the list */
		iagno = imap->im_freeiag;

		/* determine the logical block number of the iag */
		blkno = IAGTOLBLK(iagno, sbi->l2nbperpage);
	} else {
		/* no free iags. the inode map will have to be extented
		 * to include a new iag.
		 */

		/* acquire inode map lock */
		IWRITE_LOCK(ipimap, RDWRLOCK_IMAP);

		if (ipimap->i_size >> L2PSIZE != imap->im_nextiag + 1) {
			IWRITE_UNLOCK(ipimap);
			IAGFREE_UNLOCK(imap);
			jfs_error(imap->im_ipimap->i_sb,
				  "ipimap->i_size is wrong\n");
			return -EIO;
		}


		/* get the next available iag number */
		iagno = imap->im_nextiag;

		/* make sure that we have not exceeded the maximum inode
		 * number limit.
		 */
		if (iagno > (MAXIAGS - 1)) {
			/* release the inode map lock */
			IWRITE_UNLOCK(ipimap);

			rc = -ENOSPC;
			goto out;
		}

		/*
		 * synchronously append new iag page.
		 */
		/* determine the logical address of iag page to append */
		blkno = IAGTOLBLK(iagno, sbi->l2nbperpage);

		/* Allocate extent for new iag page */
		xlen = sbi->nbperpage;
		if ((rc = dbAlloc(ipimap, 0, (s64) xlen, &xaddr))) {
			/* release the inode map lock */
			IWRITE_UNLOCK(ipimap);

			goto out;
		}

		/*
		 * start transaction of update of the inode map
		 * addressing structure pointing to the new iag page;
		 */
		tid = txBegin(sb, COMMIT_FORCE);
		mutex_lock(&JFS_IP(ipimap)->commit_mutex);

		/* update the inode map addressing structure to point to it */
		if ((rc =
		     xtInsert(tid, ipimap, 0, blkno, xlen, &xaddr, 0))) {
			txEnd(tid);
			mutex_unlock(&JFS_IP(ipimap)->commit_mutex);
			/* Free the blocks allocated for the iag since it was
			 * not successfully added to the inode map
			 */
			dbFree(ipimap, xaddr, (s64) xlen);

			/* release the inode map lock */
			IWRITE_UNLOCK(ipimap);

			goto out;
		}

		/* update the inode map's inode to reflect the extension */
		ipimap->i_size += PSIZE;
		inode_add_bytes(ipimap, PSIZE);

		/* assign a buffer for the page */
		mp = get_metapage(ipimap, blkno, PSIZE, 0);
		if (!mp) {
			/*
			 * This is very unlikely since we just created the
			 * extent, but let's try to handle it correctly
			 */
			xtTruncate(tid, ipimap, ipimap->i_size - PSIZE,
				   COMMIT_PWMAP);

			txAbort(tid, 0);
			txEnd(tid);
			mutex_unlock(&JFS_IP(ipimap)->commit_mutex);

			/* release the inode map lock */
			IWRITE_UNLOCK(ipimap);

			rc = -EIO;
			goto out;
		}
		iagp = (struct iag *) mp->data;

		/* init the iag */
		memset(iagp, 0, sizeof(struct iag));
		iagp->iagnum = cpu_to_le32(iagno);
		iagp->inofreefwd = iagp->inofreeback = cpu_to_le32(-1);
		iagp->extfreefwd = iagp->extfreeback = cpu_to_le32(-1);
		iagp->iagfree = cpu_to_le32(-1);
		iagp->nfreeinos = 0;
		iagp->nfreeexts = cpu_to_le32(EXTSPERIAG);

		/* initialize the free inode summary map (free extent
		 * summary map initialization handled by bzero).
		 */
		for (i = 0; i < SMAPSZ; i++)
			iagp->inosmap[i] = cpu_to_le32(ONES);

		/*
		 * Write and sync the metapage
		 */
		flush_metapage(mp);

		/*
		 * txCommit(COMMIT_FORCE) will synchronously write address
		 * index pages and inode after commit in careful update order
		 * of address index pages (right to left, bottom up);
		 */
		iplist[0] = ipimap;
		rc = txCommit(tid, 1, &iplist[0], COMMIT_FORCE);

		txEnd(tid);
		mutex_unlock(&JFS_IP(ipimap)->commit_mutex);

		duplicateIXtree(sb, blkno, xlen, &xaddr);

		/* update the next available iag number */
		imap->im_nextiag += 1;

		/* Add the iag to the iag free list so we don't lose the iag
		 * if a failure happens now.
		 */
		imap->im_freeiag = iagno;

		/* Until we have logredo working, we want the imap inode &
		 * control page to be up to date.
		 */
		diSync(ipimap);

		/* release the inode map lock */
		IWRITE_UNLOCK(ipimap);
	}

	/* obtain read lock on map */
	IREAD_LOCK(ipimap, RDWRLOCK_IMAP);

	/* read the iag */
	if ((rc = diIAGRead(imap, iagno, &mp))) {
		IREAD_UNLOCK(ipimap);
		rc = -EIO;
		goto out;
	}
	iagp = (struct iag *) mp->data;

	/* remove the iag from the iag free list */
	imap->im_freeiag = le32_to_cpu(iagp->iagfree);
	iagp->iagfree = cpu_to_le32(-1);

	/* set the return iag number and buffer pointer */
	*iagnop = iagno;
	*mpp = mp;

      out:
	/* release the iag free lock */
	IAGFREE_UNLOCK(imap);

	return (rc);
}