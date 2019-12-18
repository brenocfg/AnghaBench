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
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct fuse_file {int open_flags; TYPE_1__ readdir; } ;
struct file {struct fuse_file* private_data; } ;
struct dir_context {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int FOPEN_CACHE_DIR ; 
 int UNCACHED ; 
 struct inode* file_inode (struct file*) ; 
 int fuse_readdir_cached (struct file*,struct dir_context*) ; 
 int fuse_readdir_uncached (struct file*,struct dir_context*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int fuse_readdir(struct file *file, struct dir_context *ctx)
{
	struct fuse_file *ff = file->private_data;
	struct inode *inode = file_inode(file);
	int err;

	if (is_bad_inode(inode))
		return -EIO;

	mutex_lock(&ff->readdir.lock);

	err = UNCACHED;
	if (ff->open_flags & FOPEN_CACHE_DIR)
		err = fuse_readdir_cached(file, ctx);
	if (err == UNCACHED)
		err = fuse_readdir_uncached(file, ctx);

	mutex_unlock(&ff->readdir.lock);

	return err;
}