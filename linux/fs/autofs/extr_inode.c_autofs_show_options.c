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
struct seq_file {int dummy; } ;
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct dentry {TYPE_2__* d_sb; } ;
struct autofs_sb_info {int pipefd; int exp_timeout; int min_proto; int max_proto; int flags; scalar_t__ pipe; int /*<<< orphan*/  type; int /*<<< orphan*/  oz_pgrp; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_root; } ;
struct TYPE_3__ {int i_ino; } ;

/* Variables and functions */
 int AUTOFS_SBI_IGNORE ; 
 int AUTOFS_SBI_STRICTEXPIRE ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int HZ ; 
 struct autofs_sb_info* autofs_sbi (TYPE_2__*) ; 
 scalar_t__ autofs_type_direct (int /*<<< orphan*/ ) ; 
 scalar_t__ autofs_type_offset (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 TYPE_1__* file_inode (scalar_t__) ; 
 int from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int pid_vnr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
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
		seq_puts(m, ",offset");
	else if (autofs_type_direct(sbi->type))
		seq_puts(m, ",direct");
	else
		seq_puts(m, ",indirect");
	if (sbi->flags & AUTOFS_SBI_STRICTEXPIRE)
		seq_puts(m, ",strictexpire");
	if (sbi->flags & AUTOFS_SBI_IGNORE)
		seq_puts(m, ",ignore");
#ifdef CONFIG_CHECKPOINT_RESTORE
	if (sbi->pipe)
		seq_printf(m, ",pipe_ino=%ld", file_inode(sbi->pipe)->i_ino);
	else
		seq_puts(m, ",pipe_ino=-1");
#endif
	return 0;
}