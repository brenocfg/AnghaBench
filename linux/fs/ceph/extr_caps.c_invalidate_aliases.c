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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* d_find_alias (struct inode*) ; 
 int /*<<< orphan*/  d_invalidate (struct dentry*) ; 
 int /*<<< orphan*/  d_prune_aliases (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 

__attribute__((used)) static void invalidate_aliases(struct inode *inode)
{
	struct dentry *dn, *prev = NULL;

	dout("invalidate_aliases inode %p\n", inode);
	d_prune_aliases(inode);
	/*
	 * For non-directory inode, d_find_alias() only returns
	 * hashed dentry. After calling d_invalidate(), the
	 * dentry becomes unhashed.
	 *
	 * For directory inode, d_find_alias() can return
	 * unhashed dentry. But directory inode should have
	 * one alias at most.
	 */
	while ((dn = d_find_alias(inode))) {
		if (dn == prev) {
			dput(dn);
			break;
		}
		d_invalidate(dn);
		if (prev)
			dput(prev);
		prev = dn;
	}
	if (prev)
		dput(prev);
}