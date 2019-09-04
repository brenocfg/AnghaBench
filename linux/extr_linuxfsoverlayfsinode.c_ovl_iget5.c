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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct inode* iget5_locked (struct super_block*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*) ; 
 struct inode* inode_insert5 (struct inode*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  ovl_inode_set ; 
 int /*<<< orphan*/  ovl_inode_test ; 

__attribute__((used)) static struct inode *ovl_iget5(struct super_block *sb, struct inode *newinode,
			       struct inode *key)
{
	return newinode ? inode_insert5(newinode, (unsigned long) key,
					 ovl_inode_test, ovl_inode_set, key) :
			  iget5_locked(sb, (unsigned long) key,
				       ovl_inode_test, ovl_inode_set, key);
}