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
struct f2fs_super_block {int /*<<< orphan*/  log_blocks_per_seg; int /*<<< orphan*/  segment_count_nat; int /*<<< orphan*/  nat_blkaddr; } ;
struct f2fs_sb_info {int total_valid_node_count; TYPE_1__* ckpt; } ;
struct f2fs_nm_info {unsigned int nat_blkaddr; unsigned int nat_blocks; int max_nid; int available_nids; unsigned int next_scan_nid; void* nat_bitmap_mir; int /*<<< orphan*/  bitmap_size; void* nat_bitmap; int /*<<< orphan*/  nat_tree_lock; int /*<<< orphan*/  nid_list_lock; int /*<<< orphan*/  build_lock; int /*<<< orphan*/  nat_list_lock; int /*<<< orphan*/  nat_entries; int /*<<< orphan*/  nat_set_root; int /*<<< orphan*/  nat_root; int /*<<< orphan*/  free_nid_list; int /*<<< orphan*/  free_nid_root; int /*<<< orphan*/  dirty_nats_ratio; int /*<<< orphan*/  ra_nid_pages; int /*<<< orphan*/  ram_thresh; scalar_t__ nat_cnt; scalar_t__* nid_cnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  next_free_nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_DIRTY_NAT_RATIO_THRESHOLD ; 
 int /*<<< orphan*/  DEF_RAM_THRESHOLD ; 
 int /*<<< orphan*/  DEF_RA_NID_PAGES ; 
 int EFAULT ; 
 int ENOMEM ; 
 struct f2fs_super_block* F2FS_RAW_SUPER (struct f2fs_sb_info*) ; 
 int F2FS_RESERVED_NODE_NUM ; 
 size_t FREE_NID ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAT_BITMAP ; 
 int NAT_ENTRY_PER_BLOCK ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 size_t PREALLOC_NID ; 
 unsigned char* __bitmap_ptr (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __bitmap_size (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int __get_nat_bitmaps (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 void* kmemdup (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_node_manager(struct f2fs_sb_info *sbi)
{
	struct f2fs_super_block *sb_raw = F2FS_RAW_SUPER(sbi);
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	unsigned char *version_bitmap;
	unsigned int nat_segs;
	int err;

	nm_i->nat_blkaddr = le32_to_cpu(sb_raw->nat_blkaddr);

	/* segment_count_nat includes pair segment so divide to 2. */
	nat_segs = le32_to_cpu(sb_raw->segment_count_nat) >> 1;
	nm_i->nat_blocks = nat_segs << le32_to_cpu(sb_raw->log_blocks_per_seg);
	nm_i->max_nid = NAT_ENTRY_PER_BLOCK * nm_i->nat_blocks;

	/* not used nids: 0, node, meta, (and root counted as valid node) */
	nm_i->available_nids = nm_i->max_nid - sbi->total_valid_node_count -
						F2FS_RESERVED_NODE_NUM;
	nm_i->nid_cnt[FREE_NID] = 0;
	nm_i->nid_cnt[PREALLOC_NID] = 0;
	nm_i->nat_cnt = 0;
	nm_i->ram_thresh = DEF_RAM_THRESHOLD;
	nm_i->ra_nid_pages = DEF_RA_NID_PAGES;
	nm_i->dirty_nats_ratio = DEF_DIRTY_NAT_RATIO_THRESHOLD;

	INIT_RADIX_TREE(&nm_i->free_nid_root, GFP_ATOMIC);
	INIT_LIST_HEAD(&nm_i->free_nid_list);
	INIT_RADIX_TREE(&nm_i->nat_root, GFP_NOIO);
	INIT_RADIX_TREE(&nm_i->nat_set_root, GFP_NOIO);
	INIT_LIST_HEAD(&nm_i->nat_entries);
	spin_lock_init(&nm_i->nat_list_lock);

	mutex_init(&nm_i->build_lock);
	spin_lock_init(&nm_i->nid_list_lock);
	init_rwsem(&nm_i->nat_tree_lock);

	nm_i->next_scan_nid = le32_to_cpu(sbi->ckpt->next_free_nid);
	nm_i->bitmap_size = __bitmap_size(sbi, NAT_BITMAP);
	version_bitmap = __bitmap_ptr(sbi, NAT_BITMAP);
	if (!version_bitmap)
		return -EFAULT;

	nm_i->nat_bitmap = kmemdup(version_bitmap, nm_i->bitmap_size,
					GFP_KERNEL);
	if (!nm_i->nat_bitmap)
		return -ENOMEM;

	err = __get_nat_bitmaps(sbi);
	if (err)
		return err;

#ifdef CONFIG_F2FS_CHECK_FS
	nm_i->nat_bitmap_mir = kmemdup(version_bitmap, nm_i->bitmap_size,
					GFP_KERNEL);
	if (!nm_i->nat_bitmap_mir)
		return -ENOMEM;
#endif

	return 0;
}