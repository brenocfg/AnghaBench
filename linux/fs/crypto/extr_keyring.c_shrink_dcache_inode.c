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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 struct dentry* d_find_any_alias (struct inode*) ; 
 int /*<<< orphan*/  d_prune_aliases (struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  shrink_dcache_parent (struct dentry*) ; 

__attribute__((used)) static void shrink_dcache_inode(struct inode *inode)
{
	struct dentry *dentry;

	if (S_ISDIR(inode->i_mode)) {
		dentry = d_find_any_alias(inode);
		if (dentry) {
			shrink_dcache_parent(dentry);
			dput(dentry);
		}
	}
	d_prune_aliases(inode);
}