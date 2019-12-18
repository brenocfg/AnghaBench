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
struct super_block {int /*<<< orphan*/  s_blocksize_bits; } ;
struct kmem_cache {int dummy; } ;
struct ext4_sb_info {int /*<<< orphan*/  s_locality_groups; int /*<<< orphan*/  s_mb_discarded; int /*<<< orphan*/  s_mb_preallocated; int /*<<< orphan*/  s_mb_generation_time; int /*<<< orphan*/  s_mb_buddies_generated; int /*<<< orphan*/  s_mb_lost_chunks; int /*<<< orphan*/  s_bal_breaks; int /*<<< orphan*/  s_bal_2orders; int /*<<< orphan*/  s_bal_goals; int /*<<< orphan*/  s_bal_ex_scanned; int /*<<< orphan*/  s_bal_success; int /*<<< orphan*/  s_bal_reqs; int /*<<< orphan*/  s_bal_allocated; scalar_t__ s_mb_stats; int /*<<< orphan*/  s_buddy_cache; int /*<<< orphan*/  s_mb_maxs; int /*<<< orphan*/  s_mb_offsets; int /*<<< orphan*/ * s_group_info; } ;
struct ext4_group_info {int /*<<< orphan*/  bb_bitmap; } ;
typedef  int ext4_group_t ;

/* Variables and functions */
 int EXT4_DESC_PER_BLOCK (struct super_block*) ; 
 int EXT4_DESC_PER_BLOCK_BITS (struct super_block*) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct ext4_group_info* ext4_get_group_info (struct super_block*,int) ; 
 int ext4_get_groups_count (struct super_block*) ; 
 int /*<<< orphan*/  ext4_lock_group (struct super_block*,int) ; 
 int /*<<< orphan*/  ext4_mb_cleanup_pa (struct ext4_group_info*) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ext4_unlock_group (struct super_block*,int) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 struct kmem_cache* get_groupinfo_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (struct kmem_cache*,struct ext4_group_info*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 

int ext4_mb_release(struct super_block *sb)
{
	ext4_group_t ngroups = ext4_get_groups_count(sb);
	ext4_group_t i;
	int num_meta_group_infos;
	struct ext4_group_info *grinfo;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct kmem_cache *cachep = get_groupinfo_cache(sb->s_blocksize_bits);

	if (sbi->s_group_info) {
		for (i = 0; i < ngroups; i++) {
			cond_resched();
			grinfo = ext4_get_group_info(sb, i);
#ifdef DOUBLE_CHECK
			kfree(grinfo->bb_bitmap);
#endif
			ext4_lock_group(sb, i);
			ext4_mb_cleanup_pa(grinfo);
			ext4_unlock_group(sb, i);
			kmem_cache_free(cachep, grinfo);
		}
		num_meta_group_infos = (ngroups +
				EXT4_DESC_PER_BLOCK(sb) - 1) >>
			EXT4_DESC_PER_BLOCK_BITS(sb);
		for (i = 0; i < num_meta_group_infos; i++)
			kfree(sbi->s_group_info[i]);
		kvfree(sbi->s_group_info);
	}
	kfree(sbi->s_mb_offsets);
	kfree(sbi->s_mb_maxs);
	iput(sbi->s_buddy_cache);
	if (sbi->s_mb_stats) {
		ext4_msg(sb, KERN_INFO,
		       "mballoc: %u blocks %u reqs (%u success)",
				atomic_read(&sbi->s_bal_allocated),
				atomic_read(&sbi->s_bal_reqs),
				atomic_read(&sbi->s_bal_success));
		ext4_msg(sb, KERN_INFO,
		      "mballoc: %u extents scanned, %u goal hits, "
				"%u 2^N hits, %u breaks, %u lost",
				atomic_read(&sbi->s_bal_ex_scanned),
				atomic_read(&sbi->s_bal_goals),
				atomic_read(&sbi->s_bal_2orders),
				atomic_read(&sbi->s_bal_breaks),
				atomic_read(&sbi->s_mb_lost_chunks));
		ext4_msg(sb, KERN_INFO,
		       "mballoc: %lu generated and it took %Lu",
				sbi->s_mb_buddies_generated,
				sbi->s_mb_generation_time);
		ext4_msg(sb, KERN_INFO,
		       "mballoc: %u preallocated, %u discarded",
				atomic_read(&sbi->s_mb_preallocated),
				atomic_read(&sbi->s_mb_discarded));
	}

	free_percpu(sbi->s_locality_groups);

	return 0;
}