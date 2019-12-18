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
struct super_block {int dummy; } ;
struct seq_file {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct TYPE_2__ {int s_jquota_fmt; scalar_t__* s_qf_names; } ;

/* Variables and functions */
 TYPE_1__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 struct f2fs_sb_info* F2FS_SB (struct super_block*) ; 
 size_t GRPQUOTA ; 
 size_t PRJQUOTA ; 
#define  QFMT_VFS_OLD 130 
#define  QFMT_VFS_V0 129 
#define  QFMT_VFS_V1 128 
 size_t USRQUOTA ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 
 int /*<<< orphan*/  seq_show_option (struct seq_file*,char*,scalar_t__) ; 

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