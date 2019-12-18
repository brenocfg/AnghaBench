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
struct super_block {int /*<<< orphan*/  s_inode_list_lock; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  inode_sb_list_add (struct inode*) ; 
 struct inode* new_inode_pseudo (struct super_block*) ; 
 int /*<<< orphan*/  spin_lock_prefetch (int /*<<< orphan*/ *) ; 

struct inode *new_inode(struct super_block *sb)
{
	struct inode *inode;

	spin_lock_prefetch(&sb->s_inode_list_lock);

	inode = new_inode_pseudo(sb);
	if (inode)
		inode_sb_list_add(inode);
	return inode;
}