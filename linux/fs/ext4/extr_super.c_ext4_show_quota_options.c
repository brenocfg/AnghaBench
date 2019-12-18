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
struct ext4_sb_info {int s_jquota_fmt; int /*<<< orphan*/ * s_qf_names; } ;

/* Variables and functions */
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 size_t GRPQUOTA ; 
#define  QFMT_VFS_OLD 130 
#define  QFMT_VFS_V0 129 
#define  QFMT_VFS_V1 128 
 size_t USRQUOTA ; 
 char* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 
 int /*<<< orphan*/  seq_show_option (struct seq_file*,char*,char*) ; 

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