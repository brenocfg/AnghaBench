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

__attribute__((used)) static inline void f2fs_show_quota_options(struct seq_file *seq,
					   struct super_block *sb)
{
#ifdef CONFIG_QUOTA
	struct f2fs_sb_info *sbi = F2FS_SB(sb);

	if (F2FS_OPTION(sbi).s_jquota_fmt) {
		char *fmtname = "";

		switch (F2FS_OPTION(sbi).s_jquota_fmt) {
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

	if (F2FS_OPTION(sbi).s_qf_names[USRQUOTA])
		seq_show_option(seq, "usrjquota",
			F2FS_OPTION(sbi).s_qf_names[USRQUOTA]);

	if (F2FS_OPTION(sbi).s_qf_names[GRPQUOTA])
		seq_show_option(seq, "grpjquota",
			F2FS_OPTION(sbi).s_qf_names[GRPQUOTA]);

	if (F2FS_OPTION(sbi).s_qf_names[PRJQUOTA])
		seq_show_option(seq, "prjjquota",
			F2FS_OPTION(sbi).s_qf_names[PRJQUOTA]);
#endif
}