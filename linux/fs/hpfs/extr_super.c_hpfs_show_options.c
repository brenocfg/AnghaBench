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
struct hpfs_sb_info {int sb_mode; int sb_chk; int sb_err; int sb_chkdsk; int sb_eas; int sb_timeshift; scalar_t__ sb_lowercase; int /*<<< orphan*/  sb_gid; int /*<<< orphan*/  sb_uid; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hpfs_sb_info* hpfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int hpfs_show_options(struct seq_file *seq, struct dentry *root)
{
	struct hpfs_sb_info *sbi = hpfs_sb(root->d_sb);

	seq_printf(seq, ",uid=%u", from_kuid_munged(&init_user_ns, sbi->sb_uid));
	seq_printf(seq, ",gid=%u", from_kgid_munged(&init_user_ns, sbi->sb_gid));
	seq_printf(seq, ",umask=%03o", (~sbi->sb_mode & 0777));
	if (sbi->sb_lowercase)
		seq_printf(seq, ",case=lower");
	if (!sbi->sb_chk)
		seq_printf(seq, ",check=none");
	if (sbi->sb_chk == 2)
		seq_printf(seq, ",check=strict");
	if (!sbi->sb_err)
		seq_printf(seq, ",errors=continue");
	if (sbi->sb_err == 2)
		seq_printf(seq, ",errors=panic");
	if (!sbi->sb_chkdsk)
		seq_printf(seq, ",chkdsk=no");
	if (sbi->sb_chkdsk == 2)
		seq_printf(seq, ",chkdsk=always");
	if (!sbi->sb_eas)
		seq_printf(seq, ",eas=no");
	if (sbi->sb_eas == 1)
		seq_printf(seq, ",eas=ro");
	if (sbi->sb_timeshift)
		seq_printf(seq, ",timeshift=%d", sbi->sb_timeshift);
	return 0;
}