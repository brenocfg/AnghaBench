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
typedef  int /*<<< orphan*/  u64 ;
struct qstr {int /*<<< orphan*/  name; scalar_t__ len; } ;
struct fuse_entry_out {int dummy; } ;
struct fuse_conn {int dummy; } ;
struct TYPE_10__ {int numargs; TYPE_4__* args; } ;
struct TYPE_6__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_8__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct fuse_args {TYPE_5__ out; TYPE_3__ in; } ;
struct TYPE_9__ {int size; struct fuse_entry_out* value; } ;
struct TYPE_7__ {int /*<<< orphan*/  value; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_LOOKUP ; 
 int /*<<< orphan*/  memset (struct fuse_entry_out*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fuse_lookup_init(struct fuse_conn *fc, struct fuse_args *args,
			     u64 nodeid, const struct qstr *name,
			     struct fuse_entry_out *outarg)
{
	memset(outarg, 0, sizeof(struct fuse_entry_out));
	args->in.h.opcode = FUSE_LOOKUP;
	args->in.h.nodeid = nodeid;
	args->in.numargs = 1;
	args->in.args[0].size = name->len + 1;
	args->in.args[0].value = name->name;
	args->out.numargs = 1;
	args->out.args[0].size = sizeof(struct fuse_entry_out);
	args->out.args[0].value = outarg;
}