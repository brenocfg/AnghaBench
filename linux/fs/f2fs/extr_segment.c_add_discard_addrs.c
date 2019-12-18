#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seg_entry {int valid_blocks; scalar_t__ discard_map; scalar_t__ ckpt_valid_map; scalar_t__ cur_valid_map; } ;
struct list_head {int dummy; } ;
struct f2fs_sb_info {int blocks_per_seg; } ;
struct discard_entry {scalar_t__ discard_map; int /*<<< orphan*/  list; int /*<<< orphan*/  start_blkaddr; } ;
struct cp_control {int reason; unsigned int trim_minlen; int /*<<< orphan*/  trim_start; } ;
struct TYPE_6__ {unsigned long* tmp_map; } ;
struct TYPE_5__ {TYPE_1__* dcc_info; } ;
struct TYPE_4__ {scalar_t__ nr_discards; scalar_t__ max_discards; struct list_head entry_list; } ;

/* Variables and functions */
 int CP_DISCARD ; 
 int /*<<< orphan*/  GFP_F2FS_ZERO ; 
 TYPE_3__* SIT_I (struct f2fs_sb_info*) ; 
 int SIT_VBLOCK_MAP_SIZE ; 
 TYPE_2__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  START_BLOCK (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 unsigned int __find_rev_next_bit (unsigned long*,int,unsigned int) ; 
 unsigned int __find_rev_next_zero_bit (unsigned long*,int,unsigned int) ; 
 int /*<<< orphan*/  __set_bit_le (int,void*) ; 
 int /*<<< orphan*/  discard_entry_slab ; 
 int /*<<< orphan*/  f2fs_hw_support_discard (struct f2fs_sb_info*) ; 
 struct discard_entry* f2fs_kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_realtime_discard_enable (struct f2fs_sb_info*) ; 
 struct seg_entry* get_seg_entry (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static bool add_discard_addrs(struct f2fs_sb_info *sbi, struct cp_control *cpc,
							bool check_only)
{
	int entries = SIT_VBLOCK_MAP_SIZE / sizeof(unsigned long);
	int max_blocks = sbi->blocks_per_seg;
	struct seg_entry *se = get_seg_entry(sbi, cpc->trim_start);
	unsigned long *cur_map = (unsigned long *)se->cur_valid_map;
	unsigned long *ckpt_map = (unsigned long *)se->ckpt_valid_map;
	unsigned long *discard_map = (unsigned long *)se->discard_map;
	unsigned long *dmap = SIT_I(sbi)->tmp_map;
	unsigned int start = 0, end = -1;
	bool force = (cpc->reason & CP_DISCARD);
	struct discard_entry *de = NULL;
	struct list_head *head = &SM_I(sbi)->dcc_info->entry_list;
	int i;

	if (se->valid_blocks == max_blocks || !f2fs_hw_support_discard(sbi))
		return false;

	if (!force) {
		if (!f2fs_realtime_discard_enable(sbi) || !se->valid_blocks ||
			SM_I(sbi)->dcc_info->nr_discards >=
				SM_I(sbi)->dcc_info->max_discards)
			return false;
	}

	/* SIT_VBLOCK_MAP_SIZE should be multiple of sizeof(unsigned long) */
	for (i = 0; i < entries; i++)
		dmap[i] = force ? ~ckpt_map[i] & ~discard_map[i] :
				(cur_map[i] ^ ckpt_map[i]) & ckpt_map[i];

	while (force || SM_I(sbi)->dcc_info->nr_discards <=
				SM_I(sbi)->dcc_info->max_discards) {
		start = __find_rev_next_bit(dmap, max_blocks, end + 1);
		if (start >= max_blocks)
			break;

		end = __find_rev_next_zero_bit(dmap, max_blocks, start + 1);
		if (force && start && end != max_blocks
					&& (end - start) < cpc->trim_minlen)
			continue;

		if (check_only)
			return true;

		if (!de) {
			de = f2fs_kmem_cache_alloc(discard_entry_slab,
								GFP_F2FS_ZERO);
			de->start_blkaddr = START_BLOCK(sbi, cpc->trim_start);
			list_add_tail(&de->list, head);
		}

		for (i = start; i < end; i++)
			__set_bit_le(i, (void *)de->discard_map);

		SM_I(sbi)->dcc_info->nr_discards += end - start;
	}
	return false;
}