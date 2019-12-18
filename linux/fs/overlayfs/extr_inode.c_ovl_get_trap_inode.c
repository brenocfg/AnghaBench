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
struct inode {int i_state; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELOOP ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOTDIR ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int I_NEW ; 
 int /*<<< orphan*/  S_DEAD ; 
 int /*<<< orphan*/  S_IFDIR ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_is_dir (struct dentry*) ; 
 struct inode* iget5_locked (struct super_block*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  ovl_inode_set ; 
 int /*<<< orphan*/  ovl_inode_test ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *ovl_get_trap_inode(struct super_block *sb, struct dentry *dir)
{
	struct inode *key = d_inode(dir);
	struct inode *trap;

	if (!d_is_dir(dir))
		return ERR_PTR(-ENOTDIR);

	trap = iget5_locked(sb, (unsigned long) key, ovl_inode_test,
			    ovl_inode_set, key);
	if (!trap)
		return ERR_PTR(-ENOMEM);

	if (!(trap->i_state & I_NEW)) {
		/* Conflicting layer roots? */
		iput(trap);
		return ERR_PTR(-ELOOP);
	}

	trap->i_mode = S_IFDIR;
	trap->i_flags = S_DEAD;
	unlock_new_inode(trap);

	return trap;
}