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
struct fuse_conn {scalar_t__ writeback_cache; scalar_t__ atomic_o_trunc; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int O_TRUNC ; 
 int fuse_do_open (struct fuse_conn*,int /*<<< orphan*/ ,struct file*,int) ; 
 int /*<<< orphan*/  fuse_finish_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  fuse_release_nowrite (struct inode*) ; 
 int /*<<< orphan*/  fuse_set_nowrite (struct inode*) ; 
 int generic_file_open (struct inode*,struct file*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

int fuse_open_common(struct inode *inode, struct file *file, bool isdir)
{
	struct fuse_conn *fc = get_fuse_conn(inode);
	int err;
	bool is_wb_truncate = (file->f_flags & O_TRUNC) &&
			  fc->atomic_o_trunc &&
			  fc->writeback_cache;

	err = generic_file_open(inode, file);
	if (err)
		return err;

	if (is_wb_truncate) {
		inode_lock(inode);
		fuse_set_nowrite(inode);
	}

	err = fuse_do_open(fc, get_node_id(inode), file, isdir);

	if (!err)
		fuse_finish_open(inode, file);

	if (is_wb_truncate) {
		fuse_release_nowrite(inode);
		inode_unlock(inode);
	}

	return err;
}