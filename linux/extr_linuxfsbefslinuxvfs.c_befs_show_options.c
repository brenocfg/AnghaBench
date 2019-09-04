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
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct befs_mount_options {scalar_t__ debug; scalar_t__ iocharset; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct befs_sb_info {struct befs_mount_options mount_opts; } ;

/* Variables and functions */
 struct befs_sb_info* BEFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 scalar_t__ from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int befs_show_options(struct seq_file *m, struct dentry *root)
{
	struct befs_sb_info *befs_sb = BEFS_SB(root->d_sb);
	struct befs_mount_options *opts = &befs_sb->mount_opts;

	if (!uid_eq(opts->uid, GLOBAL_ROOT_UID))
		seq_printf(m, ",uid=%u",
			   from_kuid_munged(&init_user_ns, opts->uid));
	if (!gid_eq(opts->gid, GLOBAL_ROOT_GID))
		seq_printf(m, ",gid=%u",
			   from_kgid_munged(&init_user_ns, opts->gid));
	if (opts->iocharset)
		seq_printf(m, ",charset=%s", opts->iocharset);
	if (opts->debug)
		seq_puts(m, ",debug");
	return 0;
}