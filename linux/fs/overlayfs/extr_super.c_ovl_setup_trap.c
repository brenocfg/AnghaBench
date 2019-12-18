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
 int ELOOP ; 
 int PTR_ERR_OR_ZERO (struct inode*) ; 
 struct inode* ovl_get_trap_inode (struct super_block*,struct dentry*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static int ovl_setup_trap(struct super_block *sb, struct dentry *dir,
			  struct inode **ptrap, const char *name)
{
	struct inode *trap;
	int err;

	trap = ovl_get_trap_inode(sb, dir);
	err = PTR_ERR_OR_ZERO(trap);
	if (err) {
		if (err == -ELOOP)
			pr_err("overlayfs: conflicting %s path\n", name);
		return err;
	}

	*ptrap = trap;
	return 0;
}