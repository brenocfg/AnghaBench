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
struct seq_file {struct super_block* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_magic; } ;
struct reiserfs_super_block {TYPE_1__ s_v1; } ;
struct reiserfs_sb_info {struct reiserfs_super_block* s_rs; } ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DF (int /*<<< orphan*/ ) ; 
 int DFL (int /*<<< orphan*/ ) ; 
 int DJF (int /*<<< orphan*/ ) ; 
 int R5_HASH ; 
 struct reiserfs_sb_info* REISERFS_SB (struct super_block*) ; 
 int TEA_HASH ; 
 int UNSET_HASH ; 
 int YURA_HASH ; 
 int reiserfs_attrs_cleared ; 
 int /*<<< orphan*/  s_block_count ; 
 int /*<<< orphan*/  s_blocksize ; 
 int /*<<< orphan*/  s_bmap_nr ; 
 int /*<<< orphan*/  s_flags ; 
 int /*<<< orphan*/  s_free_blocks ; 
 int /*<<< orphan*/  s_fs_state ; 
 int /*<<< orphan*/  s_hash_function_code ; 
 int /*<<< orphan*/  s_oid_cursize ; 
 int /*<<< orphan*/  s_oid_maxsize ; 
 int /*<<< orphan*/  s_reserved_for_journal ; 
 int /*<<< orphan*/  s_root_block ; 
 int /*<<< orphan*/  s_tree_height ; 
 int /*<<< orphan*/  s_umount_state ; 
 int /*<<< orphan*/  s_version ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int show_on_disk_super(struct seq_file *m, void *unused)
{
	struct super_block *sb = m->private;
	struct reiserfs_sb_info *sb_info = REISERFS_SB(sb);
	struct reiserfs_super_block *rs = sb_info->s_rs;
	int hash_code = DFL(s_hash_function_code);
	__u32 flags = DJF(s_flags);

	seq_printf(m, "block_count: \t%i\n"
		   "free_blocks: \t%i\n"
		   "root_block: \t%i\n"
		   "blocksize: \t%i\n"
		   "oid_maxsize: \t%i\n"
		   "oid_cursize: \t%i\n"
		   "umount_state: \t%i\n"
		   "magic: \t%10.10s\n"
		   "fs_state: \t%i\n"
		   "hash: \t%s\n"
		   "tree_height: \t%i\n"
		   "bmap_nr: \t%i\n"
		   "version: \t%i\n"
		   "flags: \t%x[%s]\n"
		   "reserved_for_journal: \t%i\n",
		   DFL(s_block_count),
		   DFL(s_free_blocks),
		   DFL(s_root_block),
		   DF(s_blocksize),
		   DF(s_oid_maxsize),
		   DF(s_oid_cursize),
		   DF(s_umount_state),
		   rs->s_v1.s_magic,
		   DF(s_fs_state),
		   hash_code == TEA_HASH ? "tea" :
		   (hash_code == YURA_HASH) ? "rupasov" :
		   (hash_code == R5_HASH) ? "r5" :
		   (hash_code == UNSET_HASH) ? "unset" : "unknown",
		   DF(s_tree_height),
		   DF(s_bmap_nr),
		   DF(s_version), flags, (flags & reiserfs_attrs_cleared)
		   ? "attrs_cleared" : "", DF(s_reserved_for_journal));

	return 0;
}