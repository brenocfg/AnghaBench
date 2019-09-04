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
struct hfs_sb_info {scalar_t__ s_creator; scalar_t__ s_type; int s_file_umask; int s_dir_umask; scalar_t__ s_quiet; TYPE_2__* nls_io; TYPE_1__* nls_disk; int /*<<< orphan*/  session; int /*<<< orphan*/  part; int /*<<< orphan*/  s_gid; int /*<<< orphan*/  s_uid; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  charset; } ;
struct TYPE_3__ {int /*<<< orphan*/  charset; } ;

/* Variables and functions */
 struct hfs_sb_info* HFS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 int /*<<< orphan*/  from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_show_option_n (struct seq_file*,char*,char*,int) ; 

__attribute__((used)) static int hfs_show_options(struct seq_file *seq, struct dentry *root)
{
	struct hfs_sb_info *sbi = HFS_SB(root->d_sb);

	if (sbi->s_creator != cpu_to_be32(0x3f3f3f3f))
		seq_show_option_n(seq, "creator", (char *)&sbi->s_creator, 4);
	if (sbi->s_type != cpu_to_be32(0x3f3f3f3f))
		seq_show_option_n(seq, "type", (char *)&sbi->s_type, 4);
	seq_printf(seq, ",uid=%u,gid=%u",
			from_kuid_munged(&init_user_ns, sbi->s_uid),
			from_kgid_munged(&init_user_ns, sbi->s_gid));
	if (sbi->s_file_umask != 0133)
		seq_printf(seq, ",file_umask=%o", sbi->s_file_umask);
	if (sbi->s_dir_umask != 0022)
		seq_printf(seq, ",dir_umask=%o", sbi->s_dir_umask);
	if (sbi->part >= 0)
		seq_printf(seq, ",part=%u", sbi->part);
	if (sbi->session >= 0)
		seq_printf(seq, ",session=%u", sbi->session);
	if (sbi->nls_disk)
		seq_printf(seq, ",codepage=%s", sbi->nls_disk->charset);
	if (sbi->nls_io)
		seq_printf(seq, ",iocharset=%s", sbi->nls_io->charset);
	if (sbi->s_quiet)
		seq_printf(seq, ",quiet");
	return 0;
}