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
struct super_block {int dummy; } ;
struct proc_inode {int /*<<< orphan*/  sysctl_inodes; struct ctl_table* sysctl_entry; struct ctl_table_header* sysctl; } ;
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; } ;
struct ctl_table_root {int /*<<< orphan*/  (* set_ownership ) (struct ctl_table_header*,struct ctl_table*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct ctl_table_header {int /*<<< orphan*/  count; int /*<<< orphan*/  inodes; int /*<<< orphan*/  unregistering; struct ctl_table_root* root; } ;
struct ctl_table {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 struct proc_inode* PROC_I (struct inode*) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  get_next_ino () ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ is_empty_dir (struct ctl_table_header*) ; 
 int /*<<< orphan*/  make_empty_dir_inode (struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  proc_sys_dir_file_operations ; 
 int /*<<< orphan*/  proc_sys_dir_operations ; 
 int /*<<< orphan*/  proc_sys_file_operations ; 
 int /*<<< orphan*/  proc_sys_inode_operations ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ctl_table_header*,struct ctl_table*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_lock ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *proc_sys_make_inode(struct super_block *sb,
		struct ctl_table_header *head, struct ctl_table *table)
{
	struct ctl_table_root *root = head->root;
	struct inode *inode;
	struct proc_inode *ei;

	inode = new_inode(sb);
	if (!inode)
		return ERR_PTR(-ENOMEM);

	inode->i_ino = get_next_ino();

	ei = PROC_I(inode);

	spin_lock(&sysctl_lock);
	if (unlikely(head->unregistering)) {
		spin_unlock(&sysctl_lock);
		iput(inode);
		return ERR_PTR(-ENOENT);
	}
	ei->sysctl = head;
	ei->sysctl_entry = table;
	hlist_add_head_rcu(&ei->sysctl_inodes, &head->inodes);
	head->count++;
	spin_unlock(&sysctl_lock);

	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	inode->i_mode = table->mode;
	if (!S_ISDIR(table->mode)) {
		inode->i_mode |= S_IFREG;
		inode->i_op = &proc_sys_inode_operations;
		inode->i_fop = &proc_sys_file_operations;
	} else {
		inode->i_mode |= S_IFDIR;
		inode->i_op = &proc_sys_dir_operations;
		inode->i_fop = &proc_sys_dir_file_operations;
		if (is_empty_dir(head))
			make_empty_dir_inode(inode);
	}

	if (root->set_ownership)
		root->set_ownership(head, table, &inode->i_uid, &inode->i_gid);
	else {
		inode->i_uid = GLOBAL_ROOT_UID;
		inode->i_gid = GLOBAL_ROOT_GID;
	}

	return inode;
}