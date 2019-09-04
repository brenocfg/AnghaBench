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
typedef  scalar_t__ umode_t ;
struct seq_file {int dummy; } ;
struct omfs_sb_info {scalar_t__ s_dmask; scalar_t__ s_fmask; int /*<<< orphan*/  s_gid; int /*<<< orphan*/  s_uid; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 struct omfs_sb_info* OMFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_gid () ; 
 int /*<<< orphan*/  current_uid () ; 
 scalar_t__ current_umask () ; 
 scalar_t__ from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omfs_show_options(struct seq_file *m, struct dentry *root)
{
	struct omfs_sb_info *sbi = OMFS_SB(root->d_sb);
	umode_t cur_umask = current_umask();

	if (!uid_eq(sbi->s_uid, current_uid()))
		seq_printf(m, ",uid=%u",
			   from_kuid_munged(&init_user_ns, sbi->s_uid));
	if (!gid_eq(sbi->s_gid, current_gid()))
		seq_printf(m, ",gid=%u",
			   from_kgid_munged(&init_user_ns, sbi->s_gid));

	if (sbi->s_dmask == sbi->s_fmask) {
		if (sbi->s_fmask != cur_umask)
			seq_printf(m, ",umask=%o", sbi->s_fmask);
	} else {
		if (sbi->s_dmask != cur_umask)
			seq_printf(m, ",dmask=%o", sbi->s_dmask);
		if (sbi->s_fmask != cur_umask)
			seq_printf(m, ",fmask=%o", sbi->s_fmask);
	}

	return 0;
}