#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct fuse_open_out {int dummy; } ;
struct fuse_open_in {int flags; } ;
struct fuse_conn {int /*<<< orphan*/  atomic_o_trunc; } ;
struct file {int f_flags; } ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_13__ {int numargs; TYPE_4__* args; } ;
struct TYPE_9__ {int opcode; int /*<<< orphan*/  nodeid; } ;
struct TYPE_11__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct TYPE_14__ {TYPE_5__ out; TYPE_3__ in; } ;
struct TYPE_12__ {int size; struct fuse_open_out* value; } ;
struct TYPE_10__ {int size; struct fuse_open_in* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_ARGS (TYPE_6__) ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_NOCTTY ; 
 int O_TRUNC ; 
 TYPE_6__ args ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_6__*) ; 
 int /*<<< orphan*/  memset (struct fuse_open_in*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fuse_send_open(struct fuse_conn *fc, u64 nodeid, struct file *file,
			  int opcode, struct fuse_open_out *outargp)
{
	struct fuse_open_in inarg;
	FUSE_ARGS(args);

	memset(&inarg, 0, sizeof(inarg));
	inarg.flags = file->f_flags & ~(O_CREAT | O_EXCL | O_NOCTTY);
	if (!fc->atomic_o_trunc)
		inarg.flags &= ~O_TRUNC;
	args.in.h.opcode = opcode;
	args.in.h.nodeid = nodeid;
	args.in.numargs = 1;
	args.in.args[0].size = sizeof(inarg);
	args.in.args[0].value = &inarg;
	args.out.numargs = 1;
	args.out.args[0].size = sizeof(*outargp);
	args.out.args[0].value = outargp;

	return fuse_simple_request(fc, &args);
}