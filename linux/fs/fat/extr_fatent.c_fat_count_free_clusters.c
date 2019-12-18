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
struct super_block {unsigned long s_blocksize_bits; } ;
struct msdos_sb_info {int free_clusters; int free_clus_valid; scalar_t__ max_cluster; unsigned long fat_length; struct fatent_operations* fatent_ops; } ;
struct fatent_operations {scalar_t__ (* ent_get ) (struct fat_entry*) ;} ;
struct fat_entry {scalar_t__ entry; } ;

/* Variables and functions */
 scalar_t__ FAT_ENT_FREE ; 
 unsigned long FAT_READA_SIZE ; 
 int /*<<< orphan*/  FAT_START_ENT ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ fat_ent_next (struct msdos_sb_info*,struct fat_entry*) ; 
 int fat_ent_read_block (struct super_block*,struct fat_entry*) ; 
 int /*<<< orphan*/  fat_ent_reada (struct super_block*,struct fat_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatent_brelse (struct fat_entry*) ; 
 int /*<<< orphan*/  fatent_init (struct fat_entry*) ; 
 int /*<<< orphan*/  fatent_set_entry (struct fat_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_fat (struct msdos_sb_info*) ; 
 int /*<<< orphan*/  mark_fsinfo_dirty (struct super_block*) ; 
 int /*<<< orphan*/  min (unsigned long,unsigned long) ; 
 scalar_t__ stub1 (struct fat_entry*) ; 
 int /*<<< orphan*/  unlock_fat (struct msdos_sb_info*) ; 

int fat_count_free_clusters(struct super_block *sb)
{
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	const struct fatent_operations *ops = sbi->fatent_ops;
	struct fat_entry fatent;
	unsigned long reada_blocks, reada_mask, cur_block;
	int err = 0, free;

	lock_fat(sbi);
	if (sbi->free_clusters != -1 && sbi->free_clus_valid)
		goto out;

	reada_blocks = FAT_READA_SIZE >> sb->s_blocksize_bits;
	reada_mask = reada_blocks - 1;
	cur_block = 0;

	free = 0;
	fatent_init(&fatent);
	fatent_set_entry(&fatent, FAT_START_ENT);
	while (fatent.entry < sbi->max_cluster) {
		/* readahead of fat blocks */
		if ((cur_block & reada_mask) == 0) {
			unsigned long rest = sbi->fat_length - cur_block;
			fat_ent_reada(sb, &fatent, min(reada_blocks, rest));
		}
		cur_block++;

		err = fat_ent_read_block(sb, &fatent);
		if (err)
			goto out;

		do {
			if (ops->ent_get(&fatent) == FAT_ENT_FREE)
				free++;
		} while (fat_ent_next(sbi, &fatent));
		cond_resched();
	}
	sbi->free_clusters = free;
	sbi->free_clus_valid = 1;
	mark_fsinfo_dirty(sb);
	fatent_brelse(&fatent);
out:
	unlock_fat(sbi);
	return err;
}