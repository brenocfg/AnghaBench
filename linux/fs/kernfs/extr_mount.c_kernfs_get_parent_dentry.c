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
struct kernfs_node {int /*<<< orphan*/  parent; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 struct kernfs_node* kernfs_dentry_node (struct dentry*) ; 
 int /*<<< orphan*/  kernfs_get_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *kernfs_get_parent_dentry(struct dentry *child)
{
	struct kernfs_node *kn = kernfs_dentry_node(child);

	return d_obtain_alias(kernfs_get_inode(child->d_sb, kn->parent));
}