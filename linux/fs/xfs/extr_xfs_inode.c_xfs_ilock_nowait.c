#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  i_mmaplock; int /*<<< orphan*/  i_lock; } ;
typedef  TYPE_1__ xfs_inode_t ;
typedef  int uint ;
struct TYPE_7__ {int /*<<< orphan*/  i_rwsem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_4__* VFS_I (TYPE_1__*) ; 
 int XFS_ILOCK_EXCL ; 
 int XFS_ILOCK_SHARED ; 
 int XFS_IOLOCK_EXCL ; 
 int XFS_IOLOCK_SHARED ; 
 int XFS_LOCK_MASK ; 
 int XFS_LOCK_SUBCLASS_MASK ; 
 int XFS_MMAPLOCK_EXCL ; 
 int XFS_MMAPLOCK_SHARED ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrtryaccess (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrtryupdate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrunlock_excl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrunlock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_ilock_nowait (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int
xfs_ilock_nowait(
	xfs_inode_t		*ip,
	uint			lock_flags)
{
	trace_xfs_ilock_nowait(ip, lock_flags, _RET_IP_);

	/*
	 * You can't set both SHARED and EXCL for the same lock,
	 * and only XFS_IOLOCK_SHARED, XFS_IOLOCK_EXCL, XFS_ILOCK_SHARED,
	 * and XFS_ILOCK_EXCL are valid values to set in lock_flags.
	 */
	ASSERT((lock_flags & (XFS_IOLOCK_SHARED | XFS_IOLOCK_EXCL)) !=
	       (XFS_IOLOCK_SHARED | XFS_IOLOCK_EXCL));
	ASSERT((lock_flags & (XFS_MMAPLOCK_SHARED | XFS_MMAPLOCK_EXCL)) !=
	       (XFS_MMAPLOCK_SHARED | XFS_MMAPLOCK_EXCL));
	ASSERT((lock_flags & (XFS_ILOCK_SHARED | XFS_ILOCK_EXCL)) !=
	       (XFS_ILOCK_SHARED | XFS_ILOCK_EXCL));
	ASSERT((lock_flags & ~(XFS_LOCK_MASK | XFS_LOCK_SUBCLASS_MASK)) == 0);

	if (lock_flags & XFS_IOLOCK_EXCL) {
		if (!down_write_trylock(&VFS_I(ip)->i_rwsem))
			goto out;
	} else if (lock_flags & XFS_IOLOCK_SHARED) {
		if (!down_read_trylock(&VFS_I(ip)->i_rwsem))
			goto out;
	}

	if (lock_flags & XFS_MMAPLOCK_EXCL) {
		if (!mrtryupdate(&ip->i_mmaplock))
			goto out_undo_iolock;
	} else if (lock_flags & XFS_MMAPLOCK_SHARED) {
		if (!mrtryaccess(&ip->i_mmaplock))
			goto out_undo_iolock;
	}

	if (lock_flags & XFS_ILOCK_EXCL) {
		if (!mrtryupdate(&ip->i_lock))
			goto out_undo_mmaplock;
	} else if (lock_flags & XFS_ILOCK_SHARED) {
		if (!mrtryaccess(&ip->i_lock))
			goto out_undo_mmaplock;
	}
	return 1;

out_undo_mmaplock:
	if (lock_flags & XFS_MMAPLOCK_EXCL)
		mrunlock_excl(&ip->i_mmaplock);
	else if (lock_flags & XFS_MMAPLOCK_SHARED)
		mrunlock_shared(&ip->i_mmaplock);
out_undo_iolock:
	if (lock_flags & XFS_IOLOCK_EXCL)
		up_write(&VFS_I(ip)->i_rwsem);
	else if (lock_flags & XFS_IOLOCK_SHARED)
		up_read(&VFS_I(ip)->i_rwsem);
out:
	return 0;
}