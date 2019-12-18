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
 int MAX_HEIGHT ; 
 struct reiserfs_sb_info* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  SFPL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  balance_at ; 
 int /*<<< orphan*/  can_node_be_removed ; 
 int /*<<< orphan*/  free_at ; 
 int /*<<< orphan*/  get_neighbors ; 
 int /*<<< orphan*/  get_neighbors_restart ; 
 int /*<<< orphan*/  items_at ; 
 int /*<<< orphan*/  lbytes ; 
 int /*<<< orphan*/  lnum ; 
 int /*<<< orphan*/  need_l_neighbor ; 
 int /*<<< orphan*/  need_r_neighbor ; 
 int /*<<< orphan*/  rbytes ; 
 int /*<<< orphan*/  rnum ; 
 int /*<<< orphan*/  sbk_fs_changed ; 
 int /*<<< orphan*/  sbk_read_at ; 
 int /*<<< orphan*/  sbk_restarted ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int show_per_level(struct seq_file *m, void *unused)
{
	struct super_block *sb = m->private;
	struct reiserfs_sb_info *r = REISERFS_SB(sb);
	int level;

	seq_printf(m, "level\t"
		   "     balances"
		   " [sbk:  reads"
		   "   fs_changed"
		   "   restarted]"
		   "   free space"
		   "        items"
		   "   can_remove"
		   "         lnum"
		   "         rnum"
		   "       lbytes"
		   "       rbytes"
		   "     get_neig"
		   " get_neig_res" "  need_l_neig" "  need_r_neig" "\n");

	for (level = 0; level < MAX_HEIGHT; ++level) {
		seq_printf(m, "%i\t"
			   " %12lu"
			   " %12lu"
			   " %12lu"
			   " %12lu"
			   " %12lu"
			   " %12lu"
			   " %12lu"
			   " %12li"
			   " %12li"
			   " %12li"
			   " %12li"
			   " %12lu"
			   " %12lu"
			   " %12lu"
			   " %12lu"
			   "\n",
			   level,
			   SFPL(balance_at),
			   SFPL(sbk_read_at),
			   SFPL(sbk_fs_changed),
			   SFPL(sbk_restarted),
			   SFPL(free_at),
			   SFPL(items_at),
			   SFPL(can_node_be_removed),
			   SFPL(lnum),
			   SFPL(rnum),
			   SFPL(lbytes),
			   SFPL(rbytes),
			   SFPL(get_neighbors),
			   SFPL(get_neighbors_restart),
			   SFPL(need_l_neighbor), SFPL(need_r_neighbor)
		    );
	}
	return 0;
}