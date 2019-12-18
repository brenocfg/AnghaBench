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
struct TYPE_2__ {scalar_t__ subdirs; } ;
struct kernfs_node {TYPE_1__ dir; int /*<<< orphan*/  mode; struct kernfs_iattrs* iattr; } ;
struct kernfs_iattrs {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 scalar_t__ KERNFS_DIR ; 
 scalar_t__ kernfs_type (struct kernfs_node*) ; 
 int /*<<< orphan*/  set_inode_attr (struct inode*,struct kernfs_iattrs*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,scalar_t__) ; 

__attribute__((used)) static void kernfs_refresh_inode(struct kernfs_node *kn, struct inode *inode)
{
	struct kernfs_iattrs *attrs = kn->iattr;

	inode->i_mode = kn->mode;
	if (attrs)
		/*
		 * kernfs_node has non-default attributes get them from
		 * persistent copy in kernfs_node.
		 */
		set_inode_attr(inode, attrs);

	if (kernfs_type(kn) == KERNFS_DIR)
		set_nlink(inode, kn->dir.subdirs + 2);
}