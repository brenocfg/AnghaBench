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
struct inode {int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  bpf_dentry_finalize (struct dentry*,struct inode*,struct inode*) ; 
 int /*<<< orphan*/  bpf_dir_iops ; 
 struct inode* bpf_get_inode (int /*<<< orphan*/ ,struct inode*,int) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  simple_dir_operations ; 

__attribute__((used)) static int bpf_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	struct inode *inode;

	inode = bpf_get_inode(dir->i_sb, dir, mode | S_IFDIR);
	if (IS_ERR(inode))
		return PTR_ERR(inode);

	inode->i_op = &bpf_dir_iops;
	inode->i_fop = &simple_dir_operations;

	inc_nlink(inode);
	inc_nlink(dir);

	bpf_dentry_finalize(dentry, inode, dir);
	return 0;
}