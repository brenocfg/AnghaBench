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
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_INO_INVALID_ATIME ; 
 int /*<<< orphan*/  nfs_set_cache_invalid (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs_invalidate_atime(struct inode *inode)
{
	spin_lock(&inode->i_lock);
	nfs_set_cache_invalid(inode, NFS_INO_INVALID_ATIME);
	spin_unlock(&inode->i_lock);
}