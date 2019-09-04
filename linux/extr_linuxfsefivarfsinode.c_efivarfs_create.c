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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {struct efivar_entry* i_private; int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {char* VariableName; int /*<<< orphan*/  VendorGuid; } ;
struct efivar_entry {TYPE_2__ var; } ;
struct TYPE_3__ {char* name; int len; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int EFI_VARIABLE_GUID_LEN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int efivar_entry_add (struct efivar_entry*,int /*<<< orphan*/ *) ; 
 scalar_t__ efivar_variable_is_removable (int /*<<< orphan*/ ,char*,int) ; 
 struct inode* efivarfs_get_inode (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  efivarfs_list ; 
 int /*<<< orphan*/  efivarfs_valid_name (char*,int) ; 
 int guid_parse (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct efivar_entry*) ; 
 struct efivar_entry* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efivarfs_create(struct inode *dir, struct dentry *dentry,
			  umode_t mode, bool excl)
{
	struct inode *inode = NULL;
	struct efivar_entry *var;
	int namelen, i = 0, err = 0;
	bool is_removable = false;

	if (!efivarfs_valid_name(dentry->d_name.name, dentry->d_name.len))
		return -EINVAL;

	var = kzalloc(sizeof(struct efivar_entry), GFP_KERNEL);
	if (!var)
		return -ENOMEM;

	/* length of the variable name itself: remove GUID and separator */
	namelen = dentry->d_name.len - EFI_VARIABLE_GUID_LEN - 1;

	err = guid_parse(dentry->d_name.name + namelen + 1, &var->var.VendorGuid);
	if (err)
		goto out;

	if (efivar_variable_is_removable(var->var.VendorGuid,
					 dentry->d_name.name, namelen))
		is_removable = true;

	inode = efivarfs_get_inode(dir->i_sb, dir, mode, 0, is_removable);
	if (!inode) {
		err = -ENOMEM;
		goto out;
	}

	for (i = 0; i < namelen; i++)
		var->var.VariableName[i] = dentry->d_name.name[i];

	var->var.VariableName[i] = '\0';

	inode->i_private = var;

	err = efivar_entry_add(var, &efivarfs_list);
	if (err)
		goto out;

	d_instantiate(dentry, inode);
	dget(dentry);
out:
	if (err) {
		kfree(var);
		if (inode)
			iput(inode);
	}
	return err;
}