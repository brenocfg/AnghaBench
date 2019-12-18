#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XFS_ILOCK_EXCL ; 
 int XFS_ILOCK_MAX_SUBCLASS ; 
 int XFS_ILOCK_PARENT ; 
 int XFS_ILOCK_RTBITMAP ; 
 int XFS_ILOCK_RTSUM ; 
 int XFS_ILOCK_SHARED ; 
 int XFS_ILOCK_SHIFT ; 
 int XFS_IOLOCK_EXCL ; 
 int XFS_IOLOCK_MAX_SUBCLASS ; 
 int XFS_IOLOCK_SHARED ; 
 int XFS_IOLOCK_SHIFT ; 
 int XFS_LOCK_SUBCLASS_MASK ; 
 int XFS_MMAPLOCK_EXCL ; 
 int XFS_MMAPLOCK_MAX_SUBCLASS ; 
 int XFS_MMAPLOCK_SHARED ; 
 int XFS_MMAPLOCK_SHIFT ; 
 int xfs_lockdep_subclass_ok (int) ; 

__attribute__((used)) static inline int
xfs_lock_inumorder(int lock_mode, int subclass)
{
	int	class = 0;

	ASSERT(!(lock_mode & (XFS_ILOCK_PARENT | XFS_ILOCK_RTBITMAP |
			      XFS_ILOCK_RTSUM)));
	ASSERT(xfs_lockdep_subclass_ok(subclass));

	if (lock_mode & (XFS_IOLOCK_SHARED|XFS_IOLOCK_EXCL)) {
		ASSERT(subclass <= XFS_IOLOCK_MAX_SUBCLASS);
		class += subclass << XFS_IOLOCK_SHIFT;
	}

	if (lock_mode & (XFS_MMAPLOCK_SHARED|XFS_MMAPLOCK_EXCL)) {
		ASSERT(subclass <= XFS_MMAPLOCK_MAX_SUBCLASS);
		class += subclass << XFS_MMAPLOCK_SHIFT;
	}

	if (lock_mode & (XFS_ILOCK_SHARED|XFS_ILOCK_EXCL)) {
		ASSERT(subclass <= XFS_ILOCK_MAX_SUBCLASS);
		class += subclass << XFS_ILOCK_SHIFT;
	}

	return (lock_mode & ~XFS_LOCK_SUBCLASS_MASK) | class;
}