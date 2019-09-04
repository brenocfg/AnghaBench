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
struct TYPE_4__ {int /*<<< orphan*/  i_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_2__* NILFS_I (struct inode*) ; 
 scalar_t__ NILFS_NAME_LEN ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 struct inode* nilfs_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nilfs_inode_by_name (struct inode*,TYPE_1__*) ; 

__attribute__((used)) static struct dentry *
nilfs_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
{
	struct inode *inode;
	ino_t ino;

	if (dentry->d_name.len > NILFS_NAME_LEN)
		return ERR_PTR(-ENAMETOOLONG);

	ino = nilfs_inode_by_name(dir, &dentry->d_name);
	inode = ino ? nilfs_iget(dir->i_sb, NILFS_I(dir)->i_root, ino) : NULL;
	return d_splice_alias(inode, dentry);
}