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
struct super_block {int /*<<< orphan*/  s_root; } ;
struct pid_namespace {struct dentry* proc_thread_self; } ;
struct inode {int i_mode; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (int /*<<< orphan*/ ,char*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 struct inode* new_inode_pseudo (struct super_block*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct pid_namespace* proc_pid_ns (struct inode*) ; 
 int /*<<< orphan*/  proc_thread_self_inode_operations ; 
 int /*<<< orphan*/  thread_self_inum ; 

int proc_setup_thread_self(struct super_block *s)
{
	struct inode *root_inode = d_inode(s->s_root);
	struct pid_namespace *ns = proc_pid_ns(root_inode);
	struct dentry *thread_self;
	int ret = -ENOMEM;

	inode_lock(root_inode);
	thread_self = d_alloc_name(s->s_root, "thread-self");
	if (thread_self) {
		struct inode *inode = new_inode_pseudo(s);
		if (inode) {
			inode->i_ino = thread_self_inum;
			inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
			inode->i_mode = S_IFLNK | S_IRWXUGO;
			inode->i_uid = GLOBAL_ROOT_UID;
			inode->i_gid = GLOBAL_ROOT_GID;
			inode->i_op = &proc_thread_self_inode_operations;
			d_add(thread_self, inode);
			ret = 0;
		} else {
			dput(thread_self);
		}
	}
	inode_unlock(root_inode);

	if (ret)
		pr_err("proc_fill_super: can't allocate /proc/thread_self\n");
	else
		ns->proc_thread_self = thread_self;

	return ret;
}