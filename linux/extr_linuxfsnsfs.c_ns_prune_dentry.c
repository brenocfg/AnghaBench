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
struct ns_common {int /*<<< orphan*/  stashed; } ;
struct inode {struct ns_common* i_private; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 

__attribute__((used)) static void ns_prune_dentry(struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);
	if (inode) {
		struct ns_common *ns = inode->i_private;
		atomic_long_set(&ns->stashed, 0);
	}
}