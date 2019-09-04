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
typedef  scalar_t__ sysv_zone_t ;
struct sysv_sb_info {scalar_t__ s_type; scalar_t__* s_free_blocks; int s_flc_size; unsigned int s_firstdatazone; unsigned int s_nzones; int /*<<< orphan*/  s_lock; scalar_t__ s_block_base; scalar_t__* s_bcache; int /*<<< orphan*/ * s_bcache_count; } ;
struct super_block {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  __fs16 ;

/* Variables and functions */
 scalar_t__ FSTYPE_AFS ; 
 struct sysv_sb_info* SYSV_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ cpu_to_fs32 (struct sysv_sb_info*,int) ; 
 int /*<<< orphan*/  dirty_sb (struct super_block*) ; 
 int fs16_to_cpu (struct sysv_sb_info*,int /*<<< orphan*/ ) ; 
 void* fs32_to_cpu (struct sysv_sb_info*,scalar_t__) ; 
 scalar_t__* get_chunk (struct super_block*,struct buffer_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 struct buffer_head* sb_bread (struct super_block*,unsigned int) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 

unsigned long sysv_count_free_blocks(struct super_block * sb)
{
	struct sysv_sb_info * sbi = SYSV_SB(sb);
	int sb_count;
	int count;
	struct buffer_head * bh = NULL;
	sysv_zone_t *blocks;
	unsigned block;
	int n;

	/*
	 * This code does not work at all for AFS (it has a bitmap
	 * free list).  As AFS is supposed to be read-only we just
	 * lie and say it has no free block at all.
	 */
	if (sbi->s_type == FSTYPE_AFS)
		return 0;

	mutex_lock(&sbi->s_lock);
	sb_count = fs32_to_cpu(sbi, *sbi->s_free_blocks);

	if (0)
		goto trust_sb;

	/* this causes a lot of disk traffic ... */
	count = 0;
	n = fs16_to_cpu(sbi, *sbi->s_bcache_count);
	blocks = sbi->s_bcache;
	while (1) {
		sysv_zone_t zone;
		if (n > sbi->s_flc_size)
			goto E2big;
		zone = 0;
		while (n && (zone = blocks[--n]) != 0)
			count++;
		if (zone == 0)
			break;

		block = fs32_to_cpu(sbi, zone);
		if (bh)
			brelse(bh);

		if (block < sbi->s_firstdatazone || block >= sbi->s_nzones)
			goto Einval;
		block += sbi->s_block_base;
		bh = sb_bread(sb, block);
		if (!bh)
			goto Eio;
		n = fs16_to_cpu(sbi, *(__fs16*)bh->b_data);
		blocks = get_chunk(sb, bh);
	}
	if (bh)
		brelse(bh);
	if (count != sb_count)
		goto Ecount;
done:
	mutex_unlock(&sbi->s_lock);
	return count;

Einval:
	printk("sysv_count_free_blocks: new block %d is not in data zone\n",
		block);
	goto trust_sb;
Eio:
	printk("sysv_count_free_blocks: cannot read free-list block\n");
	goto trust_sb;
E2big:
	printk("sysv_count_free_blocks: >flc_size entries in free-list block\n");
	if (bh)
		brelse(bh);
trust_sb:
	count = sb_count;
	goto done;
Ecount:
	printk("sysv_count_free_blocks: free block count was %d, "
		"correcting to %d\n", sb_count, count);
	if (!sb_rdonly(sb)) {
		*sbi->s_free_blocks = cpu_to_fs32(sbi, count);
		dirty_sb(sb);
	}
	goto done;
}