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
struct proc_dir_entry {int /*<<< orphan*/  proc_dops; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_set_d_op (struct dentry*,int /*<<< orphan*/ ) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  pde_get (struct proc_dir_entry*) ; 
 struct proc_dir_entry* pde_subdir_find (struct proc_dir_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* proc_get_inode (int /*<<< orphan*/ ,struct proc_dir_entry*) ; 
 int /*<<< orphan*/  proc_subdir_lock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

struct dentry *proc_lookup_de(struct inode *dir, struct dentry *dentry,
			      struct proc_dir_entry *de)
{
	struct inode *inode;

	read_lock(&proc_subdir_lock);
	de = pde_subdir_find(de, dentry->d_name.name, dentry->d_name.len);
	if (de) {
		pde_get(de);
		read_unlock(&proc_subdir_lock);
		inode = proc_get_inode(dir->i_sb, de);
		if (!inode)
			return ERR_PTR(-ENOMEM);
		d_set_d_op(dentry, de->proc_dops);
		return d_splice_alias(inode, dentry);
	}
	read_unlock(&proc_subdir_lock);
	return ERR_PTR(-ENOENT);
}