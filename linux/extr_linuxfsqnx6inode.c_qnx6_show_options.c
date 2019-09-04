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
struct qnx6_sb_info {int s_mount_opt; } ;
struct dentry {struct super_block* d_sb; } ;

/* Variables and functions */
 int QNX6_MOUNT_MMI_FS ; 
 struct qnx6_sb_info* QNX6_SB (struct super_block*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int qnx6_show_options(struct seq_file *seq, struct dentry *root)
{
	struct super_block *sb = root->d_sb;
	struct qnx6_sb_info *sbi = QNX6_SB(sb);

	if (sbi->s_mount_opt & QNX6_MOUNT_MMI_FS)
		seq_puts(seq, ",mmi_fs");
	return 0;
}