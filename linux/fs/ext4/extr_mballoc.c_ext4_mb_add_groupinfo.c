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
struct super_block {int s_blocksize; int /*<<< orphan*/  s_blocksize_bits; } ;
struct kmem_cache {int dummy; } ;
struct ext4_sb_info {struct ext4_group_info*** s_group_info; } ;
struct ext4_group_info {int bb_largest_free_order; int /*<<< orphan*/ * bb_bitmap; int /*<<< orphan*/  bb_free_root; int /*<<< orphan*/  alloc_sem; int /*<<< orphan*/  bb_prealloc_list; int /*<<< orphan*/  bb_free; int /*<<< orphan*/  bb_state; } ;
struct ext4_group_desc {int bg_flags; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  size_t ext4_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXT4_BG_BLOCK_UNINIT ; 
 size_t EXT4_DESC_PER_BLOCK (struct super_block*) ; 
 size_t EXT4_DESC_PER_BLOCK_BITS (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_GROUP_INFO_NEED_INIT_BIT ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct buffer_head*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_free_clusters_after_init (struct super_block*,size_t,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_free_group_clusters (struct super_block*,struct ext4_group_desc*) ; 
 scalar_t__ ext4_has_group_desc_csum (struct super_block*) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 struct buffer_head* ext4_read_block_bitmap (struct super_block*,size_t) ; 
 struct kmem_cache* get_groupinfo_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ext4_group_info**) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ext4_group_info* kmem_cache_zalloc (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ext4_mb_add_groupinfo(struct super_block *sb, ext4_group_t group,
			  struct ext4_group_desc *desc)
{
	int i;
	int metalen = 0;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct ext4_group_info **meta_group_info;
	struct kmem_cache *cachep = get_groupinfo_cache(sb->s_blocksize_bits);

	/*
	 * First check if this group is the first of a reserved block.
	 * If it's true, we have to allocate a new table of pointers
	 * to ext4_group_info structures
	 */
	if (group % EXT4_DESC_PER_BLOCK(sb) == 0) {
		metalen = sizeof(*meta_group_info) <<
			EXT4_DESC_PER_BLOCK_BITS(sb);
		meta_group_info = kmalloc(metalen, GFP_NOFS);
		if (meta_group_info == NULL) {
			ext4_msg(sb, KERN_ERR, "can't allocate mem "
				 "for a buddy group");
			goto exit_meta_group_info;
		}
		sbi->s_group_info[group >> EXT4_DESC_PER_BLOCK_BITS(sb)] =
			meta_group_info;
	}

	meta_group_info =
		sbi->s_group_info[group >> EXT4_DESC_PER_BLOCK_BITS(sb)];
	i = group & (EXT4_DESC_PER_BLOCK(sb) - 1);

	meta_group_info[i] = kmem_cache_zalloc(cachep, GFP_NOFS);
	if (meta_group_info[i] == NULL) {
		ext4_msg(sb, KERN_ERR, "can't allocate buddy mem");
		goto exit_group_info;
	}
	set_bit(EXT4_GROUP_INFO_NEED_INIT_BIT,
		&(meta_group_info[i]->bb_state));

	/*
	 * initialize bb_free to be able to skip
	 * empty groups without initialization
	 */
	if (ext4_has_group_desc_csum(sb) &&
	    (desc->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT))) {
		meta_group_info[i]->bb_free =
			ext4_free_clusters_after_init(sb, group, desc);
	} else {
		meta_group_info[i]->bb_free =
			ext4_free_group_clusters(sb, desc);
	}

	INIT_LIST_HEAD(&meta_group_info[i]->bb_prealloc_list);
	init_rwsem(&meta_group_info[i]->alloc_sem);
	meta_group_info[i]->bb_free_root = RB_ROOT;
	meta_group_info[i]->bb_largest_free_order = -1;  /* uninit */

#ifdef DOUBLE_CHECK
	{
		struct buffer_head *bh;
		meta_group_info[i]->bb_bitmap =
			kmalloc(sb->s_blocksize, GFP_NOFS);
		BUG_ON(meta_group_info[i]->bb_bitmap == NULL);
		bh = ext4_read_block_bitmap(sb, group);
		BUG_ON(IS_ERR_OR_NULL(bh));
		memcpy(meta_group_info[i]->bb_bitmap, bh->b_data,
			sb->s_blocksize);
		put_bh(bh);
	}
#endif

	return 0;

exit_group_info:
	/* If a meta_group_info table has been allocated, release it now */
	if (group % EXT4_DESC_PER_BLOCK(sb) == 0) {
		kfree(sbi->s_group_info[group >> EXT4_DESC_PER_BLOCK_BITS(sb)]);
		sbi->s_group_info[group >> EXT4_DESC_PER_BLOCK_BITS(sb)] = NULL;
	}
exit_meta_group_info:
	return -ENOMEM;
}