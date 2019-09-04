#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_1__* dentry; } ;
struct nameidata {int flags; unsigned int seq; struct inode* inode; scalar_t__ depth; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_seq; } ;

/* Variables and functions */
 int ECHILD ; 
 int LOOKUP_FOLLOW ; 
 int LOOKUP_RCU ; 
 int WALK_FOLLOW ; 
 int WALK_MORE ; 
 int /*<<< orphan*/  d_is_symlink (TYPE_1__*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  path_to_nameidata (struct path*,struct nameidata*) ; 
 int pick_link (struct nameidata*,struct path*,struct inode*,unsigned int) ; 
 int /*<<< orphan*/  put_link (struct nameidata*) ; 
 scalar_t__ read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline int step_into(struct nameidata *nd, struct path *path,
			    int flags, struct inode *inode, unsigned seq)
{
	if (!(flags & WALK_MORE) && nd->depth)
		put_link(nd);
	if (likely(!d_is_symlink(path->dentry)) ||
	   !(flags & WALK_FOLLOW || nd->flags & LOOKUP_FOLLOW)) {
		/* not a symlink or should not follow */
		path_to_nameidata(path, nd);
		nd->inode = inode;
		nd->seq = seq;
		return 0;
	}
	/* make sure that d_is_symlink above matches inode */
	if (nd->flags & LOOKUP_RCU) {
		if (read_seqcount_retry(&path->dentry->d_seq, seq))
			return -ECHILD;
	}
	return pick_link(nd, path, inode, seq);
}