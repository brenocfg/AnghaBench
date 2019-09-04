#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_6__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct fuse_req {int /*<<< orphan*/  flags; TYPE_3__ in; } ;
struct fuse_forget_in {int nlookup; } ;
struct fuse_conn {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_5__ {int size; struct fuse_forget_in* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FR_ISREPLY ; 
 int /*<<< orphan*/  FUSE_FORGET ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
 struct inode* file_inode (struct file*) ; 
 struct fuse_req* fuse_get_req_nofail_nopages (struct fuse_conn*,struct file*) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_forget_in*,int /*<<< orphan*/ ,int) ; 

void fuse_force_forget(struct file *file, u64 nodeid)
{
	struct inode *inode = file_inode(file);
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_req *req;
	struct fuse_forget_in inarg;

	memset(&inarg, 0, sizeof(inarg));
	inarg.nlookup = 1;
	req = fuse_get_req_nofail_nopages(fc, file);
	req->in.h.opcode = FUSE_FORGET;
	req->in.h.nodeid = nodeid;
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(inarg);
	req->in.args[0].value = &inarg;
	__clear_bit(FR_ISREPLY, &req->flags);
	__fuse_request_send(fc, req);
	/* ignore errors */
	fuse_put_request(fc, req);
}