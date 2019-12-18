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
struct fuse_setattr_in {int dummy; } ;
struct fuse_conn {int dummy; } ;
struct fuse_attr_out {int dummy; } ;
struct fuse_args {int in_numargs; int out_numargs; TYPE_2__* out_args; TYPE_1__* in_args; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {int size; struct fuse_attr_out* value; } ;
struct TYPE_3__ {int size; struct fuse_setattr_in* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_SETATTR ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 

__attribute__((used)) static void fuse_setattr_fill(struct fuse_conn *fc, struct fuse_args *args,
			      struct inode *inode,
			      struct fuse_setattr_in *inarg_p,
			      struct fuse_attr_out *outarg_p)
{
	args->opcode = FUSE_SETATTR;
	args->nodeid = get_node_id(inode);
	args->in_numargs = 1;
	args->in_args[0].size = sizeof(*inarg_p);
	args->in_args[0].value = inarg_p;
	args->out_numargs = 1;
	args->out_args[0].size = sizeof(*outarg_p);
	args->out_args[0].value = outarg_p;
}