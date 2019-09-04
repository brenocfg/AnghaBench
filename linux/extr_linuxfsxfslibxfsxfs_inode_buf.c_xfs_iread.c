#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_18__ ;
typedef  struct TYPE_20__   TYPE_17__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_22__ {int m_flags; int /*<<< orphan*/  m_sb; } ;
typedef  TYPE_1__ xfs_mount_t ;
struct TYPE_20__ {int di_version; int /*<<< orphan*/  di_flushiter; } ;
struct TYPE_23__ {scalar_t__ i_delayed_blks; TYPE_17__ i_d; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_imap; } ;
typedef  TYPE_2__ xfs_inode_t ;
typedef  scalar_t__ xfs_failaddr_t ;
struct TYPE_24__ {int di_version; int /*<<< orphan*/  di_flushiter; int /*<<< orphan*/  di_gen; scalar_t__ di_mode; } ;
typedef  TYPE_3__ xfs_dinode_t ;
typedef  int /*<<< orphan*/  xfs_buf_t ;
typedef  int uint ;
struct TYPE_21__ {scalar_t__ i_mode; int /*<<< orphan*/  i_generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EFSCORRUPTED ; 
 TYPE_18__* VFS_I (TYPE_2__*) ; 
 int XFS_IGET_CREATE ; 
 int /*<<< orphan*/  XFS_INO_REF ; 
 int XFS_MOUNT_IKEEP ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_17__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prandom_u32 () ; 
 int /*<<< orphan*/  xfs_buf_set_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_dinode_verify (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int xfs_iformat_fork (TYPE_2__*,TYPE_3__*) ; 
 int xfs_imap (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int xfs_imap_to_bp (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__**,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_inode_from_disk (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_inode_verifier_error (TYPE_2__*,int,char*,TYPE_3__*,int,scalar_t__) ; 
 scalar_t__ xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
xfs_iread(
	xfs_mount_t	*mp,
	xfs_trans_t	*tp,
	xfs_inode_t	*ip,
	uint		iget_flags)
{
	xfs_buf_t	*bp;
	xfs_dinode_t	*dip;
	xfs_failaddr_t	fa;
	int		error;

	/*
	 * Fill in the location information in the in-core inode.
	 */
	error = xfs_imap(mp, tp, ip->i_ino, &ip->i_imap, iget_flags);
	if (error)
		return error;

	/* shortcut IO on inode allocation if possible */
	if ((iget_flags & XFS_IGET_CREATE) &&
	    xfs_sb_version_hascrc(&mp->m_sb) &&
	    !(mp->m_flags & XFS_MOUNT_IKEEP)) {
		/* initialise the on-disk inode core */
		memset(&ip->i_d, 0, sizeof(ip->i_d));
		VFS_I(ip)->i_generation = prandom_u32();
		ip->i_d.di_version = 3;
		return 0;
	}

	/*
	 * Get pointers to the on-disk inode and the buffer containing it.
	 */
	error = xfs_imap_to_bp(mp, tp, &ip->i_imap, &dip, &bp, 0, iget_flags);
	if (error)
		return error;

	/* even unallocated inodes are verified */
	fa = xfs_dinode_verify(mp, ip->i_ino, dip);
	if (fa) {
		xfs_inode_verifier_error(ip, -EFSCORRUPTED, "dinode", dip,
				sizeof(*dip), fa);
		error = -EFSCORRUPTED;
		goto out_brelse;
	}

	/*
	 * If the on-disk inode is already linked to a directory
	 * entry, copy all of the inode into the in-core inode.
	 * xfs_iformat_fork() handles copying in the inode format
	 * specific information.
	 * Otherwise, just get the truly permanent information.
	 */
	if (dip->di_mode) {
		xfs_inode_from_disk(ip, dip);
		error = xfs_iformat_fork(ip, dip);
		if (error)  {
#ifdef DEBUG
			xfs_alert(mp, "%s: xfs_iformat() returned error %d",
				__func__, error);
#endif /* DEBUG */
			goto out_brelse;
		}
	} else {
		/*
		 * Partial initialisation of the in-core inode. Just the bits
		 * that xfs_ialloc won't overwrite or relies on being correct.
		 */
		ip->i_d.di_version = dip->di_version;
		VFS_I(ip)->i_generation = be32_to_cpu(dip->di_gen);
		ip->i_d.di_flushiter = be16_to_cpu(dip->di_flushiter);

		/*
		 * Make sure to pull in the mode here as well in
		 * case the inode is released without being used.
		 * This ensures that xfs_inactive() will see that
		 * the inode is already free and not try to mess
		 * with the uninitialized part of it.
		 */
		VFS_I(ip)->i_mode = 0;
	}

	ASSERT(ip->i_d.di_version >= 2);
	ip->i_delayed_blks = 0;

	/*
	 * Mark the buffer containing the inode as something to keep
	 * around for a while.  This helps to keep recently accessed
	 * meta-data in-core longer.
	 */
	xfs_buf_set_ref(bp, XFS_INO_REF);

	/*
	 * Use xfs_trans_brelse() to release the buffer containing the on-disk
	 * inode, because it was acquired with xfs_trans_read_buf() in
	 * xfs_imap_to_bp() above.  If tp is NULL, this is just a normal
	 * brelse().  If we're within a transaction, then xfs_trans_brelse()
	 * will only release the buffer if it is not dirty within the
	 * transaction.  It will be OK to release the buffer in this case,
	 * because inodes on disk are never destroyed and we will be locking the
	 * new in-core inode before putting it in the cache where other
	 * processes can find it.  Thus we don't have to worry about the inode
	 * being changed just because we released the buffer.
	 */
 out_brelse:
	xfs_trans_brelse(tp, bp);
	return error;
}