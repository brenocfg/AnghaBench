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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {unsigned int parent; } ;

/* Variables and functions */
 struct inode* d_inode (struct dentry*) ; 
 struct dentry* squashfs_export_iget (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* squashfs_i (struct inode*) ; 

__attribute__((used)) static struct dentry *squashfs_get_parent(struct dentry *child)
{
	struct inode *inode = d_inode(child);
	unsigned int parent_ino = squashfs_i(inode)->parent;

	return squashfs_export_iget(inode->i_sb, parent_ino);
}