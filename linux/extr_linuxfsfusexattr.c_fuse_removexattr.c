#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct fuse_conn {int no_removexattr; } ;
struct TYPE_7__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_9__ {int numargs; TYPE_2__* args; TYPE_1__ h; } ;
struct TYPE_10__ {TYPE_3__ in; } ;
struct TYPE_8__ {char const* value; scalar_t__ size; } ;

/* Variables and functions */
 int ENOSYS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FUSE_ARGS (TYPE_4__) ; 
 int /*<<< orphan*/  FUSE_REMOVEXATTR ; 
 TYPE_4__ args ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_4__*) ; 
 int /*<<< orphan*/  fuse_update_ctime (struct inode*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 scalar_t__ strlen (char const*) ; 

int fuse_removexattr(struct inode *inode, const char *name)
{
	struct fuse_conn *fc = get_fuse_conn(inode);
	FUSE_ARGS(args);
	int err;

	if (fc->no_removexattr)
		return -EOPNOTSUPP;

	args.in.h.opcode = FUSE_REMOVEXATTR;
	args.in.h.nodeid = get_node_id(inode);
	args.in.numargs = 1;
	args.in.args[0].size = strlen(name) + 1;
	args.in.args[0].value = name;
	err = fuse_simple_request(fc, &args);
	if (err == -ENOSYS) {
		fc->no_removexattr = 1;
		err = -EOPNOTSUPP;
	}
	if (!err) {
		fuse_invalidate_attr(inode);
		fuse_update_ctime(inode);
	}
	return err;
}