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
struct inode {int dummy; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  I_MUTEX_NONDIR2 ; 
 int break_layout (struct inode*,int) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock_shared (struct inode*) ; 
 int /*<<< orphan*/  inode_lock_shared_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock_shared (struct inode*) ; 

__attribute__((used)) static int
xfs_iolock_two_inodes_and_break_layout(
	struct inode		*src,
	struct inode		*dest)
{
	int			error;

retry:
	if (src < dest) {
		inode_lock_shared(src);
		inode_lock_nested(dest, I_MUTEX_NONDIR2);
	} else {
		/* src >= dest */
		inode_lock(dest);
	}

	error = break_layout(dest, false);
	if (error == -EWOULDBLOCK) {
		inode_unlock(dest);
		if (src < dest)
			inode_unlock_shared(src);
		error = break_layout(dest, true);
		if (error)
			return error;
		goto retry;
	}
	if (error) {
		inode_unlock(dest);
		if (src < dest)
			inode_unlock_shared(src);
		return error;
	}
	if (src > dest)
		inode_lock_shared_nested(src, I_MUTEX_NONDIR2);
	return 0;
}