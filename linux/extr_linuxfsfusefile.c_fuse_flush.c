#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_9__ {int error; } ;
struct TYPE_10__ {TYPE_4__ h; } ;
struct TYPE_6__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_8__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct fuse_req {TYPE_5__ out; int /*<<< orphan*/  flags; TYPE_3__ in; } ;
struct fuse_flush_in {int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  fh; } ;
struct fuse_file {int /*<<< orphan*/  fh; } ;
struct fuse_conn {int no_flush; } ;
struct file {int /*<<< orphan*/  f_mapping; struct fuse_file* private_data; } ;
typedef  int /*<<< orphan*/  inarg ;
typedef  int /*<<< orphan*/  fl_owner_t ;
struct TYPE_7__ {int size; struct fuse_flush_in* value; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FR_FORCE ; 
 int /*<<< orphan*/  FUSE_FLUSH ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct inode* file_inode (struct file*) ; 
 int filemap_check_errors (int /*<<< orphan*/ ) ; 
 struct fuse_req* fuse_get_req_nofail_nopages (struct fuse_conn*,struct file*) ; 
 int /*<<< orphan*/  fuse_lock_owner_id (struct fuse_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
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
	struct fuse_req *req;
	struct fuse_flush_in inarg;
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

	req = fuse_get_req_nofail_nopages(fc, file);
	memset(&inarg, 0, sizeof(inarg));
	inarg.fh = ff->fh;
	inarg.lock_owner = fuse_lock_owner_id(fc, id);
	req->in.h.opcode = FUSE_FLUSH;
	req->in.h.nodeid = get_node_id(inode);
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(inarg);
	req->in.args[0].value = &inarg;
	__set_bit(FR_FORCE, &req->flags);
	fuse_request_send(fc, req);
	err = req->out.h.error;
	fuse_put_request(fc, req);
	if (err == -ENOSYS) {
		fc->no_flush = 1;
		err = 0;
	}
	return err;
}