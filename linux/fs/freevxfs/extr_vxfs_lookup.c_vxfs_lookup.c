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
 scalar_t__ VXFS_NAMELEN ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 struct inode* vxfs_iget (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vxfs_inode_by_name (struct inode*,struct dentry*) ; 

__attribute__((used)) static struct dentry *
vxfs_lookup(struct inode *dip, struct dentry *dp, unsigned int flags)
{
	struct inode		*ip = NULL;
	ino_t			ino;
			 
	if (dp->d_name.len > VXFS_NAMELEN)
		return ERR_PTR(-ENAMETOOLONG);
				 
	ino = vxfs_inode_by_name(dip, dp);
	if (ino)
		ip = vxfs_iget(dip->i_sb, ino);
	return d_splice_alias(ip, dp);
}