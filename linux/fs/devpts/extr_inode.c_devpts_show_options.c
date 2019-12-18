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
struct seq_file {int dummy; } ;
struct pts_mount_opts {scalar_t__ mode; scalar_t__ ptmxmode; scalar_t__ max; int /*<<< orphan*/  gid; scalar_t__ setgid; int /*<<< orphan*/  uid; scalar_t__ setuid; } ;
struct pts_fs_info {struct pts_mount_opts mount_opts; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 struct pts_fs_info* DEVPTS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ NR_UNIX98_PTY_MAX ; 
 scalar_t__ from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 

__attribute__((used)) static int devpts_show_options(struct seq_file *seq, struct dentry *root)
{
	struct pts_fs_info *fsi = DEVPTS_SB(root->d_sb);
	struct pts_mount_opts *opts = &fsi->mount_opts;

	if (opts->setuid)
		seq_printf(seq, ",uid=%u",
			   from_kuid_munged(&init_user_ns, opts->uid));
	if (opts->setgid)
		seq_printf(seq, ",gid=%u",
			   from_kgid_munged(&init_user_ns, opts->gid));
	seq_printf(seq, ",mode=%03o", opts->mode);
	seq_printf(seq, ",ptmxmode=%03o", opts->ptmxmode);
	if (opts->max < NR_UNIX98_PTY_MAX)
		seq_printf(seq, ",max=%d", opts->max);

	return 0;
}