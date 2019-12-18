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
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_DEADDIR (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 struct inode* ilookup5 (struct super_block*,unsigned long,int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  ovl_inode_lower (struct inode*) ; 
 int /*<<< orphan*/  ovl_inode_test ; 
 int /*<<< orphan*/  ovl_inode_upper (struct inode*) ; 

bool ovl_lookup_trap_inode(struct super_block *sb, struct dentry *dir)
{
	struct inode *key = d_inode(dir);
	struct inode *trap;
	bool res;

	trap = ilookup5(sb, (unsigned long) key, ovl_inode_test, key);
	if (!trap)
		return false;

	res = IS_DEADDIR(trap) && !ovl_inode_upper(trap) &&
				  !ovl_inode_lower(trap);

	iput(trap);
	return res;
}