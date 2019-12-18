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
struct path {scalar_t__ mnt; } ;
struct saved {unsigned int seq; int /*<<< orphan*/  done; struct path link; } ;
struct TYPE_2__ {scalar_t__ mnt; int /*<<< orphan*/ * dentry; } ;
struct nameidata {int flags; struct inode* link_inode; scalar_t__ depth; struct saved* stack; TYPE_1__ path; int /*<<< orphan*/  total_link_count; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ECHILD ; 
 int ELOOP ; 
 int LOOKUP_RCU ; 
 scalar_t__ MAXSYMLINKS ; 
 int /*<<< orphan*/  clear_delayed_call (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drop_links (struct nameidata*) ; 
 int /*<<< orphan*/  legitimize_path (struct nameidata*,struct path*,unsigned int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mntget (scalar_t__) ; 
 int nd_alloc_stack (struct nameidata*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  path_to_nameidata (struct path*,struct nameidata*) ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  unlazy_walk (struct nameidata*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pick_link(struct nameidata *nd, struct path *link,
		     struct inode *inode, unsigned seq)
{
	int error;
	struct saved *last;
	if (unlikely(nd->total_link_count++ >= MAXSYMLINKS)) {
		path_to_nameidata(link, nd);
		return -ELOOP;
	}
	if (!(nd->flags & LOOKUP_RCU)) {
		if (link->mnt == nd->path.mnt)
			mntget(link->mnt);
	}
	error = nd_alloc_stack(nd);
	if (unlikely(error)) {
		if (error == -ECHILD) {
			if (unlikely(!legitimize_path(nd, link, seq))) {
				drop_links(nd);
				nd->depth = 0;
				nd->flags &= ~LOOKUP_RCU;
				nd->path.mnt = NULL;
				nd->path.dentry = NULL;
				rcu_read_unlock();
			} else if (likely(unlazy_walk(nd)) == 0)
				error = nd_alloc_stack(nd);
		}
		if (error) {
			path_put(link);
			return error;
		}
	}

	last = nd->stack + nd->depth++;
	last->link = *link;
	clear_delayed_call(&last->done);
	nd->link_inode = inode;
	last->seq = seq;
	return 1;
}