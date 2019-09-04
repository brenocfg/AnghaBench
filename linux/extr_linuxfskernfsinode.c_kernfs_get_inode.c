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
struct super_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ino; } ;
struct kernfs_node {TYPE_1__ id; } ;
struct inode {int i_state; } ;

/* Variables and functions */
 int I_NEW ; 
 struct inode* iget_locked (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernfs_init_inode (struct kernfs_node*,struct inode*) ; 

struct inode *kernfs_get_inode(struct super_block *sb, struct kernfs_node *kn)
{
	struct inode *inode;

	inode = iget_locked(sb, kn->id.ino);
	if (inode && (inode->i_state & I_NEW))
		kernfs_init_inode(kn, inode);

	return inode;
}