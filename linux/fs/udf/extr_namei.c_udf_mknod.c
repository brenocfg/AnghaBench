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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_valid_dev (int /*<<< orphan*/ ) ; 
 int udf_add_nondir (struct dentry*,struct inode*) ; 
 struct inode* udf_new_inode (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udf_mknod(struct inode *dir, struct dentry *dentry, umode_t mode,
		     dev_t rdev)
{
	struct inode *inode;

	if (!old_valid_dev(rdev))
		return -EINVAL;

	inode = udf_new_inode(dir, mode);
	if (IS_ERR(inode))
		return PTR_ERR(inode);

	init_special_inode(inode, mode, rdev);
	return udf_add_nondir(dentry, inode);
}