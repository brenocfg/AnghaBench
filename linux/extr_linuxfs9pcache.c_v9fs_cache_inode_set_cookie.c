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
struct v9fs_inode {int /*<<< orphan*/  fscache_lock; int /*<<< orphan*/  fscache; } ;
struct inode {int dummy; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int O_ACCMODE ; 
 int O_RDONLY ; 
 struct v9fs_inode* V9FS_I (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v9fs_cache_inode_flush_cookie (struct inode*) ; 
 int /*<<< orphan*/  v9fs_cache_inode_get_cookie (struct inode*) ; 

void v9fs_cache_inode_set_cookie(struct inode *inode, struct file *filp)
{
	struct v9fs_inode *v9inode = V9FS_I(inode);

	if (!v9inode->fscache)
		return;

	mutex_lock(&v9inode->fscache_lock);

	if ((filp->f_flags & O_ACCMODE) != O_RDONLY)
		v9fs_cache_inode_flush_cookie(inode);
	else
		v9fs_cache_inode_get_cookie(inode);

	mutex_unlock(&v9inode->fscache_lock);
}