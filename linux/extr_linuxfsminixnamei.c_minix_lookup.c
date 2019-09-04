#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {scalar_t__ len; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  scalar_t__ ino_t ;
struct TYPE_4__ {scalar_t__ s_namelen; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 struct inode* minix_iget (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ minix_inode_by_name (struct dentry*) ; 
 TYPE_2__* minix_sb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *minix_lookup(struct inode * dir, struct dentry *dentry, unsigned int flags)
{
	struct inode * inode = NULL;
	ino_t ino;

	if (dentry->d_name.len > minix_sb(dir->i_sb)->s_namelen)
		return ERR_PTR(-ENAMETOOLONG);

	ino = minix_inode_by_name(dentry);
	if (ino)
		inode = minix_iget(dir->i_sb, ino);
	return d_splice_alias(inode, dentry);
}