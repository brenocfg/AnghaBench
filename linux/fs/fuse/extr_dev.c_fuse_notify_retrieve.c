#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct fuse_notify_retrieve_out {int /*<<< orphan*/  nodeid; } ;
struct fuse_copy_state {int dummy; } ;
struct fuse_conn {int /*<<< orphan*/  killsb; scalar_t__ sb; } ;
typedef  int /*<<< orphan*/  outarg ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_copy_finish (struct fuse_copy_state*) ; 
 int fuse_copy_one (struct fuse_copy_state*,struct fuse_notify_retrieve_out*,int) ; 
 int /*<<< orphan*/  fuse_inode_eq ; 
 int fuse_retrieve (struct fuse_conn*,struct inode*,struct fuse_notify_retrieve_out*) ; 
 struct inode* ilookup5 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fuse_notify_retrieve(struct fuse_conn *fc, unsigned int size,
				struct fuse_copy_state *cs)
{
	struct fuse_notify_retrieve_out outarg;
	struct inode *inode;
	int err;

	err = -EINVAL;
	if (size != sizeof(outarg))
		goto copy_finish;

	err = fuse_copy_one(cs, &outarg, sizeof(outarg));
	if (err)
		goto copy_finish;

	fuse_copy_finish(cs);

	down_read(&fc->killsb);
	err = -ENOENT;
	if (fc->sb) {
		u64 nodeid = outarg.nodeid;

		inode = ilookup5(fc->sb, nodeid, fuse_inode_eq, &nodeid);
		if (inode) {
			err = fuse_retrieve(fc, inode, &outarg);
			iput(inode);
		}
	}
	up_read(&fc->killsb);

	return err;

copy_finish:
	fuse_copy_finish(cs);
	return err;
}