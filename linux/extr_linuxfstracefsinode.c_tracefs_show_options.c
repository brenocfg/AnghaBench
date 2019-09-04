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
struct tracefs_mount_opts {scalar_t__ mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct tracefs_fs_info {struct tracefs_mount_opts mount_opts; } ;
struct seq_file {int dummy; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {struct tracefs_fs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 scalar_t__ TRACEFS_DEFAULT_MODE ; 
 scalar_t__ from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tracefs_show_options(struct seq_file *m, struct dentry *root)
{
	struct tracefs_fs_info *fsi = root->d_sb->s_fs_info;
	struct tracefs_mount_opts *opts = &fsi->mount_opts;

	if (!uid_eq(opts->uid, GLOBAL_ROOT_UID))
		seq_printf(m, ",uid=%u",
			   from_kuid_munged(&init_user_ns, opts->uid));
	if (!gid_eq(opts->gid, GLOBAL_ROOT_GID))
		seq_printf(m, ",gid=%u",
			   from_kgid_munged(&init_user_ns, opts->gid));
	if (opts->mode != TRACEFS_DEFAULT_MODE)
		seq_printf(m, ",mode=%o", opts->mode);

	return 0;
}