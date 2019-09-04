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
struct reiserfs_sb_info {int /*<<< orphan*/  s_generation_counter; } ;

/* Variables and functions */
 struct reiserfs_sb_info* REISERFS_SB (struct super_block*) ; 
 scalar_t__ REISERFS_VALID_FS ; 
 scalar_t__ SF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SFP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bread_miss ; 
 int /*<<< orphan*/  breads ; 
 scalar_t__ convert_reiserfs (struct super_block*) ; 
 int /*<<< orphan*/  cut_from_item_restarted ; 
 int /*<<< orphan*/  delete_item_restarted ; 
 int /*<<< orphan*/  delete_solid_item_restarted ; 
 scalar_t__ have_large_tails (struct super_block*) ; 
 scalar_t__ have_small_tails (struct super_block*) ; 
 int /*<<< orphan*/  insert_item_restarted ; 
 int /*<<< orphan*/  leaked_oid ; 
 int /*<<< orphan*/  leaves_removable ; 
 int /*<<< orphan*/  max_hash_collisions ; 
 int /*<<< orphan*/  paste_into_item_restarted ; 
 scalar_t__ reiserfs_hash_detect (struct super_block*) ; 
 scalar_t__ reiserfs_hashed_relocation (struct super_block*) ; 
 scalar_t__ reiserfs_no_border (struct super_block*) ; 
 scalar_t__ reiserfs_no_unhashed_relocation (struct super_block*) ; 
 scalar_t__ reiserfs_r5_hash (struct super_block*) ; 
 scalar_t__ reiserfs_rupasov_hash (struct super_block*) ; 
 scalar_t__ reiserfs_tea_hash (struct super_block*) ; 
 scalar_t__ reiserfs_test4 (struct super_block*) ; 
 scalar_t__ replay_only (struct super_block*) ; 
 int /*<<< orphan*/  s_bmaps ; 
 int /*<<< orphan*/  s_bmaps_without_search ; 
 int /*<<< orphan*/  s_direct2indirect ; 
 int /*<<< orphan*/  s_disk_reads ; 
 int /*<<< orphan*/  s_disk_writes ; 
 int /*<<< orphan*/  s_do_balance ; 
 int /*<<< orphan*/  s_fix_nodes ; 
 int /*<<< orphan*/  s_good_search_by_key_reada ; 
 int /*<<< orphan*/  s_indirect2direct ; 
 int /*<<< orphan*/  s_mount_state ; 
 int /*<<< orphan*/  s_unneeded_left_neighbor ; 
 int /*<<< orphan*/  search_by_key ; 
 int /*<<< orphan*/  search_by_key_fs_changed ; 
 int /*<<< orphan*/  search_by_key_restarted ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int show_super(struct seq_file *m, void *unused)
{
	struct super_block *sb = m->private;
	struct reiserfs_sb_info *r = REISERFS_SB(sb);

	seq_printf(m, "state: \t%s\n"
		   "mount options: \t%s%s%s%s%s%s%s%s%s%s%s\n"
		   "gen. counter: \t%i\n"
		   "s_disk_reads: \t%i\n"
		   "s_disk_writes: \t%i\n"
		   "s_fix_nodes: \t%i\n"
		   "s_do_balance: \t%i\n"
		   "s_unneeded_left_neighbor: \t%i\n"
		   "s_good_search_by_key_reada: \t%i\n"
		   "s_bmaps: \t%i\n"
		   "s_bmaps_without_search: \t%i\n"
		   "s_direct2indirect: \t%i\n"
		   "s_indirect2direct: \t%i\n"
		   "\n"
		   "max_hash_collisions: \t%i\n"
		   "breads: \t%lu\n"
		   "bread_misses: \t%lu\n"
		   "search_by_key: \t%lu\n"
		   "search_by_key_fs_changed: \t%lu\n"
		   "search_by_key_restarted: \t%lu\n"
		   "insert_item_restarted: \t%lu\n"
		   "paste_into_item_restarted: \t%lu\n"
		   "cut_from_item_restarted: \t%lu\n"
		   "delete_solid_item_restarted: \t%lu\n"
		   "delete_item_restarted: \t%lu\n"
		   "leaked_oid: \t%lu\n"
		   "leaves_removable: \t%lu\n",
		   SF(s_mount_state) == REISERFS_VALID_FS ?
		   "REISERFS_VALID_FS" : "REISERFS_ERROR_FS",
		   reiserfs_r5_hash(sb) ? "FORCE_R5 " : "",
		   reiserfs_rupasov_hash(sb) ? "FORCE_RUPASOV " : "",
		   reiserfs_tea_hash(sb) ? "FORCE_TEA " : "",
		   reiserfs_hash_detect(sb) ? "DETECT_HASH " : "",
		   reiserfs_no_border(sb) ? "NO_BORDER " : "BORDER ",
		   reiserfs_no_unhashed_relocation(sb) ?
		   "NO_UNHASHED_RELOCATION " : "",
		   reiserfs_hashed_relocation(sb) ? "UNHASHED_RELOCATION " : "",
		   reiserfs_test4(sb) ? "TEST4 " : "",
		   have_large_tails(sb) ? "TAILS " : have_small_tails(sb) ?
		   "SMALL_TAILS " : "NO_TAILS ",
		   replay_only(sb) ? "REPLAY_ONLY " : "",
		   convert_reiserfs(sb) ? "CONV " : "",
		   atomic_read(&r->s_generation_counter),
		   SF(s_disk_reads), SF(s_disk_writes), SF(s_fix_nodes),
		   SF(s_do_balance), SF(s_unneeded_left_neighbor),
		   SF(s_good_search_by_key_reada), SF(s_bmaps),
		   SF(s_bmaps_without_search), SF(s_direct2indirect),
		   SF(s_indirect2direct), SFP(max_hash_collisions), SFP(breads),
		   SFP(bread_miss), SFP(search_by_key),
		   SFP(search_by_key_fs_changed), SFP(search_by_key_restarted),
		   SFP(insert_item_restarted), SFP(paste_into_item_restarted),
		   SFP(cut_from_item_restarted),
		   SFP(delete_solid_item_restarted), SFP(delete_item_restarted),
		   SFP(leaked_oid), SFP(leaves_removable));

	return 0;
}