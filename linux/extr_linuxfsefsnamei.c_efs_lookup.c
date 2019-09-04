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
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  scalar_t__ efs_ino_t ;

/* Variables and functions */
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 scalar_t__ efs_find_entry (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* efs_iget (int /*<<< orphan*/ ,scalar_t__) ; 

struct dentry *efs_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
{
	efs_ino_t inodenum;
	struct inode *inode = NULL;

	inodenum = efs_find_entry(dir, dentry->d_name.name, dentry->d_name.len);
	if (inodenum)
		inode = efs_iget(dir->i_sb, inodenum);

	return d_splice_alias(inode, dentry);
}