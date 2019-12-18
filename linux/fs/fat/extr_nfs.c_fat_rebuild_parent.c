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
struct msdos_sb_info {int dummy; } ;
struct msdos_dir_entry {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct fat_slot_info {int /*<<< orphan*/  i_pos; int /*<<< orphan*/  de; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int i_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 TYPE_1__* MSDOS_I (struct inode*) ; 
 int /*<<< orphan*/  MSDOS_ROOT_INO ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct inode* fat_build_inode (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fat_clus_to_blknr (struct msdos_sb_info*,int) ; 
 struct inode* fat_dget (struct super_block*,int) ; 
 int /*<<< orphan*/  fat_fill_inode (struct inode*,struct msdos_dir_entry*) ; 
 int fat_get_start (struct msdos_sb_info*,struct msdos_dir_entry*) ; 
 int /*<<< orphan*/  fat_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fat_scan_logstart (struct inode*,int,struct fat_slot_info*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  iunique (struct super_block*,int /*<<< orphan*/ ) ; 
 struct inode* new_inode (struct super_block*) ; 
 struct buffer_head* sb_bread (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
struct inode *fat_rebuild_parent(struct super_block *sb, int parent_logstart)
{
	int search_clus, clus_to_match;
	struct msdos_dir_entry *de;
	struct inode *parent = NULL;
	struct inode *dummy_grand_parent = NULL;
	struct fat_slot_info sinfo;
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	sector_t blknr = fat_clus_to_blknr(sbi, parent_logstart);
	struct buffer_head *parent_bh = sb_bread(sb, blknr);
	if (!parent_bh) {
		fat_msg(sb, KERN_ERR,
			"unable to read cluster of parent directory");
		return NULL;
	}

	de = (struct msdos_dir_entry *) parent_bh->b_data;
	clus_to_match = fat_get_start(sbi, &de[0]);
	search_clus = fat_get_start(sbi, &de[1]);

	dummy_grand_parent = fat_dget(sb, search_clus);
	if (!dummy_grand_parent) {
		dummy_grand_parent = new_inode(sb);
		if (!dummy_grand_parent) {
			brelse(parent_bh);
			return parent;
		}

		dummy_grand_parent->i_ino = iunique(sb, MSDOS_ROOT_INO);
		fat_fill_inode(dummy_grand_parent, &de[1]);
		MSDOS_I(dummy_grand_parent)->i_pos = -1;
	}

	if (!fat_scan_logstart(dummy_grand_parent, clus_to_match, &sinfo))
		parent = fat_build_inode(sb, sinfo.de, sinfo.i_pos);

	brelse(parent_bh);
	iput(dummy_grand_parent);

	return parent;
}