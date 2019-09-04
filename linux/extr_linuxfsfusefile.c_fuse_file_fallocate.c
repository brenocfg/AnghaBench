#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct fuse_inode {int /*<<< orphan*/  state; } ;
struct fuse_file {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  fh; struct fuse_conn* fc; } ;
struct fuse_fallocate_in {int mode; scalar_t__ length; scalar_t__ offset; int /*<<< orphan*/  fh; } ;
struct fuse_conn {int no_fallocate; scalar_t__ writeback_cache; } ;
struct file {struct fuse_file* private_data; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_7__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_9__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct TYPE_10__ {TYPE_3__ in; } ;
struct TYPE_8__ {int size; struct fuse_fallocate_in* value; } ;

/* Variables and functions */
 int ENOSYS ; 
 long EOPNOTSUPP ; 
 int FALLOC_FL_KEEP_SIZE ; 
 int FALLOC_FL_PUNCH_HOLE ; 
 int /*<<< orphan*/  FUSE_ARGS (TYPE_4__) ; 
 int /*<<< orphan*/  FUSE_FALLOCATE ; 
 int /*<<< orphan*/  FUSE_I_SIZE_UNSTABLE ; 
 TYPE_4__ args ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  file_update_time (struct file*) ; 
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_4__*) ; 
 int /*<<< orphan*/  fuse_sync_writes (struct inode*) ; 
 int fuse_write_update_size (struct inode*,scalar_t__) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache_range (struct inode*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static long fuse_file_fallocate(struct file *file, int mode, loff_t offset,
				loff_t length)
{
	struct fuse_file *ff = file->private_data;
	struct inode *inode = file_inode(file);
	struct fuse_inode *fi = get_fuse_inode(inode);
	struct fuse_conn *fc = ff->fc;
	FUSE_ARGS(args);
	struct fuse_fallocate_in inarg = {
		.fh = ff->fh,
		.offset = offset,
		.length = length,
		.mode = mode
	};
	int err;
	bool lock_inode = !(mode & FALLOC_FL_KEEP_SIZE) ||
			   (mode & FALLOC_FL_PUNCH_HOLE);

	if (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE))
		return -EOPNOTSUPP;

	if (fc->no_fallocate)
		return -EOPNOTSUPP;

	if (lock_inode) {
		inode_lock(inode);
		if (mode & FALLOC_FL_PUNCH_HOLE) {
			loff_t endbyte = offset + length - 1;
			err = filemap_write_and_wait_range(inode->i_mapping,
							   offset, endbyte);
			if (err)
				goto out;

			fuse_sync_writes(inode);
		}
	}

	if (!(mode & FALLOC_FL_KEEP_SIZE))
		set_bit(FUSE_I_SIZE_UNSTABLE, &fi->state);

	args.in.h.opcode = FUSE_FALLOCATE;
	args.in.h.nodeid = ff->nodeid;
	args.in.numargs = 1;
	args.in.args[0].size = sizeof(inarg);
	args.in.args[0].value = &inarg;
	err = fuse_simple_request(fc, &args);
	if (err == -ENOSYS) {
		fc->no_fallocate = 1;
		err = -EOPNOTSUPP;
	}
	if (err)
		goto out;

	/* we could have extended the file */
	if (!(mode & FALLOC_FL_KEEP_SIZE)) {
		bool changed = fuse_write_update_size(inode, offset + length);

		if (changed && fc->writeback_cache)
			file_update_time(file);
	}

	if (mode & FALLOC_FL_PUNCH_HOLE)
		truncate_pagecache_range(inode, offset, offset + length - 1);

	fuse_invalidate_attr(inode);

out:
	if (!(mode & FALLOC_FL_KEEP_SIZE))
		clear_bit(FUSE_I_SIZE_UNSTABLE, &fi->state);

	if (lock_inode)
		inode_unlock(inode);

	return err;
}