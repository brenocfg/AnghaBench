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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct fuse_forget_in {int nlookup; } ;
struct fuse_conn {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_6__ {int in_numargs; int force; int noreply; TYPE_1__* in_args; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_5__ {int size; struct fuse_forget_in* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_ARGS (TYPE_2__) ; 
 int /*<<< orphan*/  FUSE_FORGET ; 
 TYPE_2__ args ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  fuse_simple_request (struct fuse_conn*,TYPE_2__*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_forget_in*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fuse_force_forget(struct file *file, u64 nodeid)
{
	struct inode *inode = file_inode(file);
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_forget_in inarg;
	FUSE_ARGS(args);

	memset(&inarg, 0, sizeof(inarg));
	inarg.nlookup = 1;
	args.opcode = FUSE_FORGET;
	args.nodeid = nodeid;
	args.in_numargs = 1;
	args.in_args[0].size = sizeof(inarg);
	args.in_args[0].value = &inarg;
	args.force = true;
	args.noreply = true;

	fuse_simple_request(fc, &args);
	/* ignore errors */
}