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
typedef  int umode_t ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  inode_inc_link_count (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int minix_add_link (struct dentry*,struct inode*) ; 
 int minix_make_empty (struct inode*,struct inode*) ; 
 struct inode* minix_new_inode (struct inode*,int,int*) ; 
 int /*<<< orphan*/  minix_set_inode (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int minix_mkdir(struct inode * dir, struct dentry *dentry, umode_t mode)
{
	struct inode * inode;
	int err;

	inode_inc_link_count(dir);

	inode = minix_new_inode(dir, S_IFDIR | mode, &err);
	if (!inode)
		goto out_dir;

	minix_set_inode(inode, 0);

	inode_inc_link_count(inode);

	err = minix_make_empty(inode, dir);
	if (err)
		goto out_fail;

	err = minix_add_link(dentry, inode);
	if (err)
		goto out_fail;

	d_instantiate(dentry, inode);
out:
	return err;

out_fail:
	inode_dec_link_count(inode);
	inode_dec_link_count(inode);
	iput(inode);
out_dir:
	inode_dec_link_count(dir);
	goto out;
}