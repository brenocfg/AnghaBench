#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct fuse_flush_in {int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  fh; } ;
struct fuse_file {int /*<<< orphan*/  fh; } ;
struct fuse_conn {int no_flush; } ;
struct file {int /*<<< orphan*/  f_mapping; struct fuse_file* private_data; } ;
typedef  int /*<<< orphan*/  inarg ;
typedef  int /*<<< orphan*/  fl_owner_t ;
struct TYPE_6__ {int in_numargs; int force; TYPE_1__* in_args; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_5__ {int size; struct fuse_flush_in* value; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FUSE_ARGS (TYPE_2__) ; 
 int /*<<< orphan*/  FUSE_FLUSH ; 
 TYPE_2__ args ; 
 struct inode* file_inode (struct file*) ; 
 int filemap_check_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_lock_owner_id (struct fuse_conn*,int /*<<< orphan*/ ) ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_2__*) ; 
 int /*<<< orphan*/  fuse_sync_writes (struct inode*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_flush_in*,int /*<<< orphan*/ ,int) ; 
 int write_inode_now (struct inode*,int) ; 

__attribute__((used)) static int fuse_flush(struct file *file, fl_owner_t id)
{
	struct inode *inode = file_inode(file);
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_file *ff = file->private_data;
	struct fuse_flush_in inarg;
	FUSE_ARGS(args);
	int err;

	if (is_bad_inode(inode))
		return -EIO;

	if (fc->no_flush)
		return 0;

	err = write_inode_now(inode, 1);
	if (err)
		return err;

	inode_lock(inode);
	fuse_sync_writes(inode);
	inode_unlock(inode);

	err = filemap_check_errors(file->f_mapping);
	if (err)
		return err;

	memset(&inarg, 0, sizeof(inarg));
	inarg.fh = ff->fh;
	inarg.lock_owner = fuse_lock_owner_id(fc, id);
	args.opcode = FUSE_FLUSH;
	args.nodeid = get_node_id(inode);
	args.in_numargs = 1;
	args.in_args[0].size = sizeof(inarg);
	args.in_args[0].value = &inarg;
	args.force = true;

	err = fuse_simple_request(fc, &args);
	if (err == -ENOSYS) {
		fc->no_flush = 1;
		err = 0;
	}
	return err;
}