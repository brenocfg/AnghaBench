#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {scalar_t__ len; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ UFS_MAXNAMLEN ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 struct inode* ufs_iget (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ufs_inode_by_name (struct inode*,TYPE_1__*) ; 

__attribute__((used)) static struct dentry *ufs_lookup(struct inode * dir, struct dentry *dentry, unsigned int flags)
{
	struct inode * inode = NULL;
	ino_t ino;
	
	if (dentry->d_name.len > UFS_MAXNAMLEN)
		return ERR_PTR(-ENAMETOOLONG);

	ino = ufs_inode_by_name(dir, &dentry->d_name);
	if (ino)
		inode = ufs_iget(dir->i_sb, ino);
	return d_splice_alias(inode, dentry);
}