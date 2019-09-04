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
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 struct inode* d_inode (struct dentry*) ; 
 struct inode* ilookup5 (struct super_block*,unsigned long,int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  ovl_inode_test ; 
 int /*<<< orphan*/  ovl_verify_inode (struct inode*,struct dentry*,struct dentry*,int) ; 

struct inode *ovl_lookup_inode(struct super_block *sb, struct dentry *real,
			       bool is_upper)
{
	struct inode *inode, *key = d_inode(real);

	inode = ilookup5(sb, (unsigned long) key, ovl_inode_test, key);
	if (!inode)
		return NULL;

	if (!ovl_verify_inode(inode, is_upper ? NULL : real,
			      is_upper ? real : NULL, false)) {
		iput(inode);
		return ERR_PTR(-ESTALE);
	}

	return inode;
}