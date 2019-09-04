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
struct super_block {int s_blocksize_bits; } ;
struct msdos_sb_info {int sec_per_clus; } ;
struct inode {int i_blocks; struct super_block* i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int sector_t ;
struct TYPE_2__ {int mmu_private; int /*<<< orphan*/  i_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 TYPE_1__* MSDOS_I (struct inode*) ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int fat_add_cluster (struct inode*) ; 
 int fat_bmap (struct inode*,int,int*,unsigned long*,int,int) ; 
 int /*<<< orphan*/  fat_fs_error (struct super_block*,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,struct super_block*,int) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 

__attribute__((used)) static inline int __fat_get_block(struct inode *inode, sector_t iblock,
				  unsigned long *max_blocks,
				  struct buffer_head *bh_result, int create)
{
	struct super_block *sb = inode->i_sb;
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	unsigned long mapped_blocks;
	sector_t phys, last_block;
	int err, offset;

	err = fat_bmap(inode, iblock, &phys, &mapped_blocks, create, false);
	if (err)
		return err;
	if (phys) {
		map_bh(bh_result, sb, phys);
		*max_blocks = min(mapped_blocks, *max_blocks);
		return 0;
	}
	if (!create)
		return 0;

	if (iblock != MSDOS_I(inode)->mmu_private >> sb->s_blocksize_bits) {
		fat_fs_error(sb, "corrupted file size (i_pos %lld, %lld)",
			MSDOS_I(inode)->i_pos, MSDOS_I(inode)->mmu_private);
		return -EIO;
	}

	last_block = inode->i_blocks >> (sb->s_blocksize_bits - 9);
	offset = (unsigned long)iblock & (sbi->sec_per_clus - 1);
	/*
	 * allocate a cluster according to the following.
	 * 1) no more available blocks
	 * 2) not part of fallocate region
	 */
	if (!offset && !(iblock < last_block)) {
		/* TODO: multiple cluster allocation would be desirable. */
		err = fat_add_cluster(inode);
		if (err)
			return err;
	}
	/* available blocks on this cluster */
	mapped_blocks = sbi->sec_per_clus - offset;

	*max_blocks = min(mapped_blocks, *max_blocks);
	MSDOS_I(inode)->mmu_private += *max_blocks << sb->s_blocksize_bits;

	err = fat_bmap(inode, iblock, &phys, &mapped_blocks, create, false);
	if (err)
		return err;
	if (!phys) {
		fat_fs_error(sb,
			     "invalid FAT chain (i_pos %lld, last_block %llu)",
			     MSDOS_I(inode)->i_pos,
			     (unsigned long long)last_block);
		return -EIO;
	}

	BUG_ON(*max_blocks != mapped_blocks);
	set_buffer_new(bh_result);
	map_bh(bh_result, sb, phys);

	return 0;
}