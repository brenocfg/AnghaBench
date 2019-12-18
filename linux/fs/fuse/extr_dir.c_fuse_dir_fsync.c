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
struct fuse_conn {int no_fsyncdir; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FUSE_FSYNCDIR ; 
 int fuse_fsync_common (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 

__attribute__((used)) static int fuse_dir_fsync(struct file *file, loff_t start, loff_t end,
			  int datasync)
{
	struct inode *inode = file->f_mapping->host;
	struct fuse_conn *fc = get_fuse_conn(inode);
	int err;

	if (is_bad_inode(inode))
		return -EIO;

	if (fc->no_fsyncdir)
		return 0;

	inode_lock(inode);
	err = fuse_fsync_common(file, start, end, datasync, FUSE_FSYNCDIR);
	if (err == -ENOSYS) {
		fc->no_fsyncdir = 1;
		err = 0;
	}
	inode_unlock(inode);

	return err;
}