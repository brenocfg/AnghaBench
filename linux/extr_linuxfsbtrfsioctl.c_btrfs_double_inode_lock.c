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
 int /*<<< orphan*/  I_MUTEX_CHILD ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (struct inode*,struct inode*) ; 

__attribute__((used)) static void btrfs_double_inode_lock(struct inode *inode1, struct inode *inode2)
{
	if (inode1 < inode2)
		swap(inode1, inode2);

	inode_lock_nested(inode1, I_MUTEX_PARENT);
	inode_lock_nested(inode2, I_MUTEX_CHILD);
}