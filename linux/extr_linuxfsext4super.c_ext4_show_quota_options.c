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
struct seq_file {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void ext4_show_quota_options(struct seq_file *seq,
					   struct super_block *sb)
{
#if defined(CONFIG_QUOTA)
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	char *usr_qf_name, *grp_qf_name;

	if (sbi->s_jquota_fmt) {
		char *fmtname = "";

		switch (sbi->s_jquota_fmt) {
		case QFMT_VFS_OLD:
			fmtname = "vfsold";
			break;
		case QFMT_VFS_V0:
			fmtname = "vfsv0";
			break;
		case QFMT_VFS_V1:
			fmtname = "vfsv1";
			break;
		}
		seq_printf(seq, ",jqfmt=%s", fmtname);
	}

	rcu_read_lock();
	usr_qf_name = rcu_dereference(sbi->s_qf_names[USRQUOTA]);
	grp_qf_name = rcu_dereference(sbi->s_qf_names[GRPQUOTA]);
	if (usr_qf_name)
		seq_show_option(seq, "usrjquota", usr_qf_name);
	if (grp_qf_name)
		seq_show_option(seq, "grpjquota", grp_qf_name);
	rcu_read_unlock();
#endif
}