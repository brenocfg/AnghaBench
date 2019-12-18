#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct efivar_entry {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {struct efivar_entry* i_private; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  drop_nlink (TYPE_1__*) ; 
 scalar_t__ efivar_entry_delete (struct efivar_entry*) ; 

__attribute__((used)) static int efivarfs_unlink(struct inode *dir, struct dentry *dentry)
{
	struct efivar_entry *var = d_inode(dentry)->i_private;

	if (efivar_entry_delete(var))
		return -EINVAL;

	drop_nlink(d_inode(dentry));
	dput(dentry);
	return 0;
}