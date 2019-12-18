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
struct TYPE_2__ {struct dentry* dentry; int /*<<< orphan*/ * mnt; } ;
struct nameidata {int flags; scalar_t__ inode; TYPE_1__ path; int /*<<< orphan*/  seq; } ;
struct dentry {scalar_t__ d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ECHILD ; 
 int LOOKUP_RCU ; 
 int /*<<< orphan*/  legitimize_links (struct nameidata*) ; 
 int /*<<< orphan*/  legitimize_path (struct nameidata*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  legitimize_root (struct nameidata*) ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int unlazy_walk(struct nameidata *nd)
{
	struct dentry *parent = nd->path.dentry;

	BUG_ON(!(nd->flags & LOOKUP_RCU));

	nd->flags &= ~LOOKUP_RCU;
	if (unlikely(!legitimize_links(nd)))
		goto out1;
	if (unlikely(!legitimize_path(nd, &nd->path, nd->seq)))
		goto out;
	if (unlikely(!legitimize_root(nd)))
		goto out;
	rcu_read_unlock();
	BUG_ON(nd->inode != parent->d_inode);
	return 0;

out1:
	nd->path.mnt = NULL;
	nd->path.dentry = NULL;
out:
	rcu_read_unlock();
	return -ECHILD;
}