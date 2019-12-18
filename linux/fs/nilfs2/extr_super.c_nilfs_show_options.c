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
struct the_nilfs {int dummy; } ;
struct super_block {struct the_nilfs* s_fs_info; } ;
struct seq_file {int dummy; } ;
struct nilfs_root {scalar_t__ cno; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_2__ {struct nilfs_root* i_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BARRIER ; 
 int /*<<< orphan*/  DISCARD ; 
 int /*<<< orphan*/  ERRORS_CONT ; 
 int /*<<< orphan*/  ERRORS_PANIC ; 
 scalar_t__ NILFS_CPTREE_CURRENT_CNO ; 
 TYPE_1__* NILFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NORECOVERY ; 
 int /*<<< orphan*/  STRICT_ORDER ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ nilfs_test_opt (struct the_nilfs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long long) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int nilfs_show_options(struct seq_file *seq, struct dentry *dentry)
{
	struct super_block *sb = dentry->d_sb;
	struct the_nilfs *nilfs = sb->s_fs_info;
	struct nilfs_root *root = NILFS_I(d_inode(dentry))->i_root;

	if (!nilfs_test_opt(nilfs, BARRIER))
		seq_puts(seq, ",nobarrier");
	if (root->cno != NILFS_CPTREE_CURRENT_CNO)
		seq_printf(seq, ",cp=%llu", (unsigned long long)root->cno);
	if (nilfs_test_opt(nilfs, ERRORS_PANIC))
		seq_puts(seq, ",errors=panic");
	if (nilfs_test_opt(nilfs, ERRORS_CONT))
		seq_puts(seq, ",errors=continue");
	if (nilfs_test_opt(nilfs, STRICT_ORDER))
		seq_puts(seq, ",order=strict");
	if (nilfs_test_opt(nilfs, NORECOVERY))
		seq_puts(seq, ",norecovery");
	if (nilfs_test_opt(nilfs, DISCARD))
		seq_puts(seq, ",discard");

	return 0;
}