#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  type; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct fuse_lk_in {int /*<<< orphan*/  lk_flags; TYPE_1__ lk; int /*<<< orphan*/  owner; int /*<<< orphan*/  fh; } ;
struct fuse_file {int /*<<< orphan*/  fh; } ;
struct fuse_conn {int dummy; } ;
struct fuse_args {int opcode; int in_numargs; TYPE_2__* in_args; int /*<<< orphan*/  nodeid; } ;
struct file_lock {int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; int /*<<< orphan*/  fl_owner; } ;
struct file {struct fuse_file* private_data; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_4__ {int size; struct fuse_lk_in* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_LK_FLOCK ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  fuse_lock_owner_id (struct fuse_conn*,int /*<<< orphan*/ ) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_lk_in*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fuse_lk_fill(struct fuse_args *args, struct file *file,
			 const struct file_lock *fl, int opcode, pid_t pid,
			 int flock, struct fuse_lk_in *inarg)
{
	struct inode *inode = file_inode(file);
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_file *ff = file->private_data;

	memset(inarg, 0, sizeof(*inarg));
	inarg->fh = ff->fh;
	inarg->owner = fuse_lock_owner_id(fc, fl->fl_owner);
	inarg->lk.start = fl->fl_start;
	inarg->lk.end = fl->fl_end;
	inarg->lk.type = fl->fl_type;
	inarg->lk.pid = pid;
	if (flock)
		inarg->lk_flags |= FUSE_LK_FLOCK;
	args->opcode = opcode;
	args->nodeid = get_node_id(inode);
	args->in_numargs = 1;
	args->in_args[0].size = sizeof(*inarg);
	args->in_args[0].value = inarg;
}