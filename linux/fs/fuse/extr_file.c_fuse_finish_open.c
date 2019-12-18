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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct fuse_inode {int /*<<< orphan*/  lock; int /*<<< orphan*/  attr_version; } ;
struct fuse_file {int open_flags; } ;
struct fuse_conn {scalar_t__ writeback_cache; int /*<<< orphan*/  attr_version; scalar_t__ atomic_o_trunc; } ;
struct file {int f_flags; int f_mode; struct fuse_file* private_data; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int FOPEN_KEEP_CACHE ; 
 int FOPEN_NONSEEKABLE ; 
 int FOPEN_STREAM ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  atomic64_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_update_time (struct file*) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  fuse_link_write_file (struct file*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_inode_pages2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_open (struct inode*,struct file*) ; 

void fuse_finish_open(struct inode *inode, struct file *file)
{
	struct fuse_file *ff = file->private_data;
	struct fuse_conn *fc = get_fuse_conn(inode);

	if (!(ff->open_flags & FOPEN_KEEP_CACHE))
		invalidate_inode_pages2(inode->i_mapping);
	if (ff->open_flags & FOPEN_STREAM)
		stream_open(inode, file);
	else if (ff->open_flags & FOPEN_NONSEEKABLE)
		nonseekable_open(inode, file);
	if (fc->atomic_o_trunc && (file->f_flags & O_TRUNC)) {
		struct fuse_inode *fi = get_fuse_inode(inode);

		spin_lock(&fi->lock);
		fi->attr_version = atomic64_inc_return(&fc->attr_version);
		i_size_write(inode, 0);
		spin_unlock(&fi->lock);
		fuse_invalidate_attr(inode);
		if (fc->writeback_cache)
			file_update_time(file);
	}
	if ((file->f_mode & FMODE_WRITE) && fc->writeback_cache)
		fuse_link_write_file(file);
}