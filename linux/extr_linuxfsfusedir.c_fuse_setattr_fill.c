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
struct fuse_setattr_in {int dummy; } ;
struct fuse_conn {int dummy; } ;
struct fuse_attr_out {int dummy; } ;
struct TYPE_10__ {int numargs; TYPE_4__* args; } ;
struct TYPE_6__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_8__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct fuse_args {TYPE_5__ out; TYPE_3__ in; } ;
struct TYPE_9__ {int size; struct fuse_attr_out* value; } ;
struct TYPE_7__ {int size; struct fuse_setattr_in* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_SETATTR ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 

__attribute__((used)) static void fuse_setattr_fill(struct fuse_conn *fc, struct fuse_args *args,
			      struct inode *inode,
			      struct fuse_setattr_in *inarg_p,
			      struct fuse_attr_out *outarg_p)
{
	args->in.h.opcode = FUSE_SETATTR;
	args->in.h.nodeid = get_node_id(inode);
	args->in.numargs = 1;
	args->in.args[0].size = sizeof(*inarg_p);
	args->in.args[0].value = inarg_p;
	args->out.numargs = 1;
	args->out.args[0].size = sizeof(*outarg_p);
	args->out.args[0].value = outarg_p;
}