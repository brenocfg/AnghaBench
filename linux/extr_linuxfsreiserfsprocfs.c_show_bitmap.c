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
struct seq_file {struct super_block* private; } ;
struct reiserfs_sb_info {int dummy; } ;

/* Variables and functions */
 struct reiserfs_sb_info* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  SFP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SFPF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bmap ; 
 int /*<<< orphan*/  call ; 
 int /*<<< orphan*/  free_block ; 
 int /*<<< orphan*/  in_journal_hint ; 
 int /*<<< orphan*/  in_journal_nohint ; 
 int /*<<< orphan*/  retry ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stolen ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int show_bitmap(struct seq_file *m, void *unused)
{
	struct super_block *sb = m->private;
	struct reiserfs_sb_info *r = REISERFS_SB(sb);

	seq_printf(m, "free_block: %lu\n"
		   "  scan_bitmap:"
		   "          wait"
		   "          bmap"
		   "         retry"
		   "        stolen"
		   "  journal_hint"
		   "journal_nohint"
		   "\n"
		   " %14lu"
		   " %14lu"
		   " %14lu"
		   " %14lu"
		   " %14lu"
		   " %14lu"
		   " %14lu"
		   "\n",
		   SFP(free_block),
		   SFPF(call),
		   SFPF(wait),
		   SFPF(bmap),
		   SFPF(retry),
		   SFPF(stolen),
		   SFPF(in_journal_hint), SFPF(in_journal_nohint));

	return 0;
}