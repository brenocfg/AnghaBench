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
struct seq_file {int dummy; } ;
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct autofs_sb_info {int exp_timeout; int /*<<< orphan*/  type; int /*<<< orphan*/  max_proto; int /*<<< orphan*/  min_proto; int /*<<< orphan*/  oz_pgrp; int /*<<< orphan*/  pipefd; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int HZ ; 
 struct autofs_sb_info* autofs_sbi (TYPE_1__*) ; 
 scalar_t__ autofs_type_direct (int /*<<< orphan*/ ) ; 
 scalar_t__ autofs_type_offset (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  pid_vnr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int autofs_show_options(struct seq_file *m, struct dentry *root)
{
	struct autofs_sb_info *sbi = autofs_sbi(root->d_sb);
	struct inode *root_inode = d_inode(root->d_sb->s_root);

	if (!sbi)
		return 0;

	seq_printf(m, ",fd=%d", sbi->pipefd);
	if (!uid_eq(root_inode->i_uid, GLOBAL_ROOT_UID))
		seq_printf(m, ",uid=%u",
			from_kuid_munged(&init_user_ns, root_inode->i_uid));
	if (!gid_eq(root_inode->i_gid, GLOBAL_ROOT_GID))
		seq_printf(m, ",gid=%u",
			from_kgid_munged(&init_user_ns, root_inode->i_gid));
	seq_printf(m, ",pgrp=%d", pid_vnr(sbi->oz_pgrp));
	seq_printf(m, ",timeout=%lu", sbi->exp_timeout/HZ);
	seq_printf(m, ",minproto=%d", sbi->min_proto);
	seq_printf(m, ",maxproto=%d", sbi->max_proto);

	if (autofs_type_offset(sbi->type))
		seq_printf(m, ",offset");
	else if (autofs_type_direct(sbi->type))
		seq_printf(m, ",direct");
	else
		seq_printf(m, ",indirect");
#ifdef CONFIG_CHECKPOINT_RESTORE
	if (sbi->pipe)
		seq_printf(m, ",pipe_ino=%ld", file_inode(sbi->pipe)->i_ino);
	else
		seq_printf(m, ",pipe_ino=-1");
#endif
	return 0;
}