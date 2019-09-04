#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct metapage {scalar_t__ data; } ;
struct inomap {TYPE_2__* im_agctl; } ;
struct inode {int i_ino; int /*<<< orphan*/  i_sb; } ;
struct iag {int /*<<< orphan*/ * extsmap; int /*<<< orphan*/ * inosmap; int /*<<< orphan*/ * wmap; int /*<<< orphan*/ * inoext; scalar_t__ nfreeinos; scalar_t__ nfreeexts; } ;
typedef  int ino_t ;
struct TYPE_9__ {int /*<<< orphan*/  agstart; int /*<<< orphan*/  fileset; struct inode* ipimap; struct inomap* i_imap; } ;
struct TYPE_8__ {int /*<<< orphan*/  ipbmap; TYPE_1__* bmap; struct inode* ipimap; } ;
struct TYPE_7__ {int numfree; } ;
struct TYPE_6__ {int /*<<< orphan*/ * db_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG_LOCK (struct inomap*,int) ; 
 int /*<<< orphan*/  AG_UNLOCK (struct inomap*,int) ; 
 int BLKTOAG (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int EIO ; 
 int ENOSPC ; 
 int EXTSPERIAG ; 
 int EXTSPERSUM ; 
 int /*<<< orphan*/  FILESYSTEM_I ; 
 int INOSPEREXT ; 
 int INOSPERIAG ; 
 int INOTOIAG (int) ; 
 int /*<<< orphan*/  IREAD_LOCK (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IREAD_UNLOCK (struct inode*) ; 
 TYPE_4__* JFS_IP (struct inode*) ; 
 TYPE_3__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int L2EXTSPERSUM ; 
 int L2INOSPEREXT ; 
 int ONES ; 
 int /*<<< orphan*/  RDWRLOCK_IMAP ; 
 int SMAPSZ ; 
 scalar_t__ addressPXD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int dbNextAG (int /*<<< orphan*/ ) ; 
 int diAllocAG (struct inomap*,int,int,struct inode*) ; 
 int diAllocAny (struct inomap*,int,int,struct inode*) ; 
 int diAllocBit (struct inomap*,struct iag*,int) ; 
 int diFindFree (int,int) ; 
 int diIAGRead (struct inomap*,int,struct metapage**) ; 
 int /*<<< orphan*/  diInitInode (struct inode*,int,int,int,struct iag*) ; 
 int diNewExt (struct inomap*,struct iag*,int) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_metapage_dirty (struct metapage*) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 

int diAlloc(struct inode *pip, bool dir, struct inode *ip)
{
	int rc, ino, iagno, addext, extno, bitno, sword;
	int nwords, rem, i, agno;
	u32 mask, inosmap, extsmap;
	struct inode *ipimap;
	struct metapage *mp;
	ino_t inum;
	struct iag *iagp;
	struct inomap *imap;

	/* get the pointers to the inode map inode and the
	 * corresponding imap control structure.
	 */
	ipimap = JFS_SBI(pip->i_sb)->ipimap;
	imap = JFS_IP(ipimap)->i_imap;
	JFS_IP(ip)->ipimap = ipimap;
	JFS_IP(ip)->fileset = FILESYSTEM_I;

	/* for a directory, the allocation policy is to start
	 * at the ag level using the preferred ag.
	 */
	if (dir) {
		agno = dbNextAG(JFS_SBI(pip->i_sb)->ipbmap);
		AG_LOCK(imap, agno);
		goto tryag;
	}

	/* for files, the policy starts off by trying to allocate from
	 * the same iag containing the parent disk inode:
	 * try to allocate the new disk inode close to the parent disk
	 * inode, using parent disk inode number + 1 as the allocation
	 * hint.  (we use a left-to-right policy to attempt to avoid
	 * moving backward on the disk.)  compute the hint within the
	 * file system and the iag.
	 */

	/* get the ag number of this iag */
	agno = BLKTOAG(JFS_IP(pip)->agstart, JFS_SBI(pip->i_sb));

	if (atomic_read(&JFS_SBI(pip->i_sb)->bmap->db_active[agno])) {
		/*
		 * There is an open file actively growing.  We want to
		 * allocate new inodes from a different ag to avoid
		 * fragmentation problems.
		 */
		agno = dbNextAG(JFS_SBI(pip->i_sb)->ipbmap);
		AG_LOCK(imap, agno);
		goto tryag;
	}

	inum = pip->i_ino + 1;
	ino = inum & (INOSPERIAG - 1);

	/* back off the hint if it is outside of the iag */
	if (ino == 0)
		inum = pip->i_ino;

	/* lock the AG inode map information */
	AG_LOCK(imap, agno);

	/* Get read lock on imap inode */
	IREAD_LOCK(ipimap, RDWRLOCK_IMAP);

	/* get the iag number and read the iag */
	iagno = INOTOIAG(inum);
	if ((rc = diIAGRead(imap, iagno, &mp))) {
		IREAD_UNLOCK(ipimap);
		AG_UNLOCK(imap, agno);
		return (rc);
	}
	iagp = (struct iag *) mp->data;

	/* determine if new inode extent is allowed to be added to the iag.
	 * new inode extent can be added to the iag if the ag
	 * has less than 32 free disk inodes and the iag has free extents.
	 */
	addext = (imap->im_agctl[agno].numfree < 32 && iagp->nfreeexts);

	/*
	 *	try to allocate from the IAG
	 */
	/* check if the inode may be allocated from the iag
	 * (i.e. the inode has free inodes or new extent can be added).
	 */
	if (iagp->nfreeinos || addext) {
		/* determine the extent number of the hint.
		 */
		extno = ino >> L2INOSPEREXT;

		/* check if the extent containing the hint has backed
		 * inodes.  if so, try to allocate within this extent.
		 */
		if (addressPXD(&iagp->inoext[extno])) {
			bitno = ino & (INOSPEREXT - 1);
			if ((bitno =
			     diFindFree(le32_to_cpu(iagp->wmap[extno]),
					bitno))
			    < INOSPEREXT) {
				ino = (extno << L2INOSPEREXT) + bitno;

				/* a free inode (bit) was found within this
				 * extent, so allocate it.
				 */
				rc = diAllocBit(imap, iagp, ino);
				IREAD_UNLOCK(ipimap);
				if (rc) {
					assert(rc == -EIO);
				} else {
					/* set the results of the allocation
					 * and write the iag.
					 */
					diInitInode(ip, iagno, ino, extno,
						    iagp);
					mark_metapage_dirty(mp);
				}
				release_metapage(mp);

				/* free the AG lock and return.
				 */
				AG_UNLOCK(imap, agno);
				return (rc);
			}

			if (!addext)
				extno =
				    (extno ==
				     EXTSPERIAG - 1) ? 0 : extno + 1;
		}

		/*
		 * no free inodes within the extent containing the hint.
		 *
		 * try to allocate from the backed extents following
		 * hint or, if appropriate (i.e. addext is true), allocate
		 * an extent of free inodes at or following the extent
		 * containing the hint.
		 *
		 * the free inode and free extent summary maps are used
		 * here, so determine the starting summary map position
		 * and the number of words we'll have to examine.  again,
		 * the approach is to allocate following the hint, so we
		 * might have to initially ignore prior bits of the summary
		 * map that represent extents prior to the extent containing
		 * the hint and later revisit these bits.
		 */
		bitno = extno & (EXTSPERSUM - 1);
		nwords = (bitno == 0) ? SMAPSZ : SMAPSZ + 1;
		sword = extno >> L2EXTSPERSUM;

		/* mask any prior bits for the starting words of the
		 * summary map.
		 */
		mask = (bitno == 0) ? 0 : (ONES << (EXTSPERSUM - bitno));
		inosmap = le32_to_cpu(iagp->inosmap[sword]) | mask;
		extsmap = le32_to_cpu(iagp->extsmap[sword]) | mask;

		/* scan the free inode and free extent summary maps for
		 * free resources.
		 */
		for (i = 0; i < nwords; i++) {
			/* check if this word of the free inode summary
			 * map describes an extent with free inodes.
			 */
			if (~inosmap) {
				/* an extent with free inodes has been
				 * found. determine the extent number
				 * and the inode number within the extent.
				 */
				rem = diFindFree(inosmap, 0);
				extno = (sword << L2EXTSPERSUM) + rem;
				rem = diFindFree(le32_to_cpu(iagp->wmap[extno]),
						 0);
				if (rem >= INOSPEREXT) {
					IREAD_UNLOCK(ipimap);
					release_metapage(mp);
					AG_UNLOCK(imap, agno);
					jfs_error(ip->i_sb,
						  "can't find free bit in wmap\n");
					return -EIO;
				}

				/* determine the inode number within the
				 * iag and allocate the inode from the
				 * map.
				 */
				ino = (extno << L2INOSPEREXT) + rem;
				rc = diAllocBit(imap, iagp, ino);
				IREAD_UNLOCK(ipimap);
				if (rc)
					assert(rc == -EIO);
				else {
					/* set the results of the allocation
					 * and write the iag.
					 */
					diInitInode(ip, iagno, ino, extno,
						    iagp);
					mark_metapage_dirty(mp);
				}
				release_metapage(mp);

				/* free the AG lock and return.
				 */
				AG_UNLOCK(imap, agno);
				return (rc);

			}

			/* check if we may allocate an extent of free
			 * inodes and whether this word of the free
			 * extents summary map describes a free extent.
			 */
			if (addext && ~extsmap) {
				/* a free extent has been found.  determine
				 * the extent number.
				 */
				rem = diFindFree(extsmap, 0);
				extno = (sword << L2EXTSPERSUM) + rem;

				/* allocate an extent of free inodes.
				 */
				if ((rc = diNewExt(imap, iagp, extno))) {
					/* if there is no disk space for a
					 * new extent, try to allocate the
					 * disk inode from somewhere else.
					 */
					if (rc == -ENOSPC)
						break;

					assert(rc == -EIO);
				} else {
					/* set the results of the allocation
					 * and write the iag.
					 */
					diInitInode(ip, iagno,
						    extno << L2INOSPEREXT,
						    extno, iagp);
					mark_metapage_dirty(mp);
				}
				release_metapage(mp);
				/* free the imap inode & the AG lock & return.
				 */
				IREAD_UNLOCK(ipimap);
				AG_UNLOCK(imap, agno);
				return (rc);
			}

			/* move on to the next set of summary map words.
			 */
			sword = (sword == SMAPSZ - 1) ? 0 : sword + 1;
			inosmap = le32_to_cpu(iagp->inosmap[sword]);
			extsmap = le32_to_cpu(iagp->extsmap[sword]);
		}
	}
	/* unlock imap inode */
	IREAD_UNLOCK(ipimap);

	/* nothing doing in this iag, so release it. */
	release_metapage(mp);

      tryag:
	/*
	 * try to allocate anywhere within the same AG as the parent inode.
	 */
	rc = diAllocAG(imap, agno, dir, ip);

	AG_UNLOCK(imap, agno);

	if (rc != -ENOSPC)
		return (rc);

	/*
	 * try to allocate in any AG.
	 */
	return (diAllocAny(imap, agno, dir, ip));
}