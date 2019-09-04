#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct fuse_fsync_in {int fsync_flags; int /*<<< orphan*/  fh; } ;
struct fuse_file {int /*<<< orphan*/  fh; } ;
struct fuse_conn {int no_fsync; int no_fsyncdir; } ;
struct file {struct fuse_file* private_data; TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_9__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_11__ {int numargs; TYPE_3__* args; TYPE_2__ h; } ;
struct TYPE_12__ {TYPE_4__ in; } ;
struct TYPE_10__ {int size; struct fuse_fsync_in* value; } ;
struct TYPE_8__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FUSE_ARGS (TYPE_5__) ; 
 int /*<<< orphan*/  FUSE_FSYNC ; 
 int /*<<< orphan*/  FUSE_FSYNCDIR ; 
 TYPE_5__ args ; 
 int file_check_and_advance_wb_err (struct file*) ; 
 int file_write_and_wait_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_5__*) ; 
 int /*<<< orphan*/  fuse_sync_writes (struct inode*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_fsync_in*,int /*<<< orphan*/ ,int) ; 
 int sync_inode_metadata (struct inode*,int) ; 

int fuse_fsync_common(struct file *file, loff_t start, loff_t end,
		      int datasync, int isdir)
{
	struct inode *inode = file->f_mapping->host;
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_file *ff = file->private_data;
	FUSE_ARGS(args);
	struct fuse_fsync_in inarg;
	int err;

	if (is_bad_inode(inode))
		return -EIO;

	inode_lock(inode);

	/*
	 * Start writeback against all dirty pages of the inode, then
	 * wait for all outstanding writes, before sending the FSYNC
	 * request.
	 */
	err = file_write_and_wait_range(file, start, end);
	if (err)
		goto out;

	fuse_sync_writes(inode);

	/*
	 * Due to implementation of fuse writeback
	 * file_write_and_wait_range() does not catch errors.
	 * We have to do this directly after fuse_sync_writes()
	 */
	err = file_check_and_advance_wb_err(file);
	if (err)
		goto out;

	err = sync_inode_metadata(inode, 1);
	if (err)
		goto out;

	if ((!isdir && fc->no_fsync) || (isdir && fc->no_fsyncdir))
		goto out;

	memset(&inarg, 0, sizeof(inarg));
	inarg.fh = ff->fh;
	inarg.fsync_flags = datasync ? 1 : 0;
	args.in.h.opcode = isdir ? FUSE_FSYNCDIR : FUSE_FSYNC;
	args.in.h.nodeid = get_node_id(inode);
	args.in.numargs = 1;
	args.in.args[0].size = sizeof(inarg);
	args.in.args[0].value = &inarg;
	err = fuse_simple_request(fc, &args);
	if (err == -ENOSYS) {
		if (isdir)
			fc->no_fsyncdir = 1;
		else
			fc->no_fsync = 1;
		err = 0;
	}
out:
	inode_unlock(inode);
	return err;
}