#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct dentry* dentry; } ;
struct nameidata {int flags; TYPE_1__ path; int /*<<< orphan*/  inode; TYPE_1__ root; int /*<<< orphan*/  seq; int /*<<< orphan*/  root_seq; } ;
struct dentry {int /*<<< orphan*/  d_inode; int /*<<< orphan*/  d_seq; } ;

/* Variables and functions */
 int ECHILD ; 
 int LOOKUP_JUMPED ; 
 int LOOKUP_RCU ; 
 int /*<<< orphan*/  path_get (TYPE_1__*) ; 
 int /*<<< orphan*/  path_put (TYPE_1__*) ; 
 int /*<<< orphan*/  read_seqcount_retry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nd_jump_root(struct nameidata *nd)
{
	if (nd->flags & LOOKUP_RCU) {
		struct dentry *d;
		nd->path = nd->root;
		d = nd->path.dentry;
		nd->inode = d->d_inode;
		nd->seq = nd->root_seq;
		if (unlikely(read_seqcount_retry(&d->d_seq, nd->seq)))
			return -ECHILD;
	} else {
		path_put(&nd->path);
		nd->path = nd->root;
		path_get(&nd->path);
		nd->inode = nd->path.dentry->d_inode;
	}
	nd->flags |= LOOKUP_JUMPED;
	return 0;
}