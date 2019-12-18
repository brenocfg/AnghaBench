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
struct inode {int dummy; } ;
struct fuse_conn {int no_removexattr; } ;
struct TYPE_6__ {int in_numargs; TYPE_1__* in_args; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_5__ {char const* value; scalar_t__ size; } ;

/* Variables and functions */
 int ENOSYS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FUSE_ARGS (TYPE_2__) ; 
 int /*<<< orphan*/  FUSE_REMOVEXATTR ; 
 TYPE_2__ args ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_2__*) ; 
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

	args.opcode = FUSE_REMOVEXATTR;
	args.nodeid = get_node_id(inode);
	args.in_numargs = 1;
	args.in_args[0].size = strlen(name) + 1;
	args.in_args[0].value = name;
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