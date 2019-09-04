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
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 struct inode* ecryptfs_get_inode (int /*<<< orphan*/ ,struct super_block*) ; 

__attribute__((used)) static int ecryptfs_interpose(struct dentry *lower_dentry,
			      struct dentry *dentry, struct super_block *sb)
{
	struct inode *inode = ecryptfs_get_inode(d_inode(lower_dentry), sb);

	if (IS_ERR(inode))
		return PTR_ERR(inode);
	d_instantiate(dentry, inode);

	return 0;
}