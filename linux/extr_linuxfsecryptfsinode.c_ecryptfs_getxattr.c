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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ecryptfs_dentry_to_lower (struct dentry*) ; 
 int /*<<< orphan*/  ecryptfs_getxattr_lower (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,void*,size_t) ; 
 int /*<<< orphan*/  ecryptfs_inode_to_lower (struct inode*) ; 

__attribute__((used)) static ssize_t
ecryptfs_getxattr(struct dentry *dentry, struct inode *inode,
		  const char *name, void *value, size_t size)
{
	return ecryptfs_getxattr_lower(ecryptfs_dentry_to_lower(dentry),
				       ecryptfs_inode_to_lower(inode),
				       name, value, size);
}