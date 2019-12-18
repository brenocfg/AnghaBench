#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct fuse_fsync_in {int /*<<< orphan*/  fsync_flags; int /*<<< orphan*/  fh; } ;
struct fuse_file {int /*<<< orphan*/  fh; } ;
struct fuse_conn {int dummy; } ;
struct file {struct fuse_file* private_data; TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_8__ {int opcode; int in_numargs; TYPE_2__* in_args; int /*<<< orphan*/  nodeid; } ;
struct TYPE_7__ {int size; struct fuse_fsync_in* value; } ;
struct TYPE_6__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_ARGS (TYPE_3__) ; 
 int /*<<< orphan*/  FUSE_FSYNC_FDATASYNC ; 
 TYPE_3__ args ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_3__*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_fsync_in*,int /*<<< orphan*/ ,int) ; 

int fuse_fsync_common(struct file *file, loff_t start, loff_t end,
		      int datasync, int opcode)
{
	struct inode *inode = file->f_mapping->host;
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_file *ff = file->private_data;
	FUSE_ARGS(args);
	struct fuse_fsync_in inarg;

	memset(&inarg, 0, sizeof(inarg));
	inarg.fh = ff->fh;
	inarg.fsync_flags = datasync ? FUSE_FSYNC_FDATASYNC : 0;
	args.opcode = opcode;
	args.nodeid = get_node_id(inode);
	args.in_numargs = 1;
	args.in_args[0].size = sizeof(inarg);
	args.in_args[0].value = &inarg;
	return fuse_simple_request(fc, &args);
}