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
struct seq_file {int dummy; } ;
struct hfsplus_sb_info {scalar_t__ creator; scalar_t__ type; scalar_t__ part; scalar_t__ session; int /*<<< orphan*/  flags; TYPE_1__* nls; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  umask; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct TYPE_2__ {scalar_t__ charset; } ;

/* Variables and functions */
 scalar_t__ HFSPLUS_DEF_CR_TYPE ; 
 struct hfsplus_sb_info* HFSPLUS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HFSPLUS_SB_NOBARRIER ; 
 int /*<<< orphan*/  HFSPLUS_SB_NODECOMPOSE ; 
 int /*<<< orphan*/  from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  seq_show_option_n (struct seq_file*,char*,char*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hfsplus_show_options(struct seq_file *seq, struct dentry *root)
{
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(root->d_sb);

	if (sbi->creator != HFSPLUS_DEF_CR_TYPE)
		seq_show_option_n(seq, "creator", (char *)&sbi->creator, 4);
	if (sbi->type != HFSPLUS_DEF_CR_TYPE)
		seq_show_option_n(seq, "type", (char *)&sbi->type, 4);
	seq_printf(seq, ",umask=%o,uid=%u,gid=%u", sbi->umask,
			from_kuid_munged(&init_user_ns, sbi->uid),
			from_kgid_munged(&init_user_ns, sbi->gid));
	if (sbi->part >= 0)
		seq_printf(seq, ",part=%u", sbi->part);
	if (sbi->session >= 0)
		seq_printf(seq, ",session=%u", sbi->session);
	if (sbi->nls)
		seq_printf(seq, ",nls=%s", sbi->nls->charset);
	if (test_bit(HFSPLUS_SB_NODECOMPOSE, &sbi->flags))
		seq_puts(seq, ",nodecompose");
	if (test_bit(HFSPLUS_SB_NOBARRIER, &sbi->flags))
		seq_puts(seq, ",nobarrier");
	return 0;
}