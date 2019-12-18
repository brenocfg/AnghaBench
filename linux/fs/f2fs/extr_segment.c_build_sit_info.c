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
struct sit_info {char* bitmap; int sit_base_addr; unsigned int sit_blocks; unsigned int bitmap_size; int /*<<< orphan*/  sentry_lock; int /*<<< orphan*/  mounted_time; int /*<<< orphan*/  elapsed_time; int /*<<< orphan*/  sents_per_block; scalar_t__ dirty_sentries; scalar_t__ written_valid_blocks; int /*<<< orphan*/ * s_ops; void* invalid_segmap; void* sit_bitmap_mir; void* sit_bitmap; void* sec_entries; void* tmp_map; TYPE_1__* sentries; void* dirty_sentries_bitmap; } ;
struct seg_entry {int dummy; } ;
struct sec_entry {int dummy; } ;
struct f2fs_super_block {int /*<<< orphan*/  sit_blkaddr; int /*<<< orphan*/  segment_count_sit; } ;
struct f2fs_sb_info {unsigned int log_blocks_per_seg; TYPE_2__* ckpt; } ;
struct TYPE_6__ {struct sit_info* sit_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  elapsed_time; } ;
struct TYPE_4__ {char* cur_valid_map; char* ckpt_valid_map; char* cur_valid_map_mir; char* discard_map; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct f2fs_super_block* F2FS_RAW_SUPER (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int MAIN_SECS (struct f2fs_sb_info*) ; 
 unsigned int MAIN_SEGS (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  SIT_BITMAP ; 
 int /*<<< orphan*/  SIT_ENTRY_PER_BLOCK ; 
 int SIT_VBLOCK_MAP_SIZE ; 
 TYPE_3__* SM_I (struct f2fs_sb_info*) ; 
 char* __bitmap_ptr (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 unsigned int __bitmap_size (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ __is_large_section (struct f2fs_sb_info*) ; 
 unsigned int array_size (int,unsigned int) ; 
 int /*<<< orphan*/  default_salloc_ops ; 
 unsigned int f2fs_bitmap_size (unsigned int) ; 
 void* f2fs_kvzalloc (struct f2fs_sb_info*,unsigned int,int /*<<< orphan*/ ) ; 
 void* f2fs_kzalloc (struct f2fs_sb_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 void* kmemdup (char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_sit_info(struct f2fs_sb_info *sbi)
{
	struct f2fs_super_block *raw_super = F2FS_RAW_SUPER(sbi);
	struct sit_info *sit_i;
	unsigned int sit_segs, start;
	char *src_bitmap, *bitmap;
	unsigned int bitmap_size, main_bitmap_size, sit_bitmap_size;

	/* allocate memory for SIT information */
	sit_i = f2fs_kzalloc(sbi, sizeof(struct sit_info), GFP_KERNEL);
	if (!sit_i)
		return -ENOMEM;

	SM_I(sbi)->sit_info = sit_i;

	sit_i->sentries =
		f2fs_kvzalloc(sbi, array_size(sizeof(struct seg_entry),
					      MAIN_SEGS(sbi)),
			      GFP_KERNEL);
	if (!sit_i->sentries)
		return -ENOMEM;

	main_bitmap_size = f2fs_bitmap_size(MAIN_SEGS(sbi));
	sit_i->dirty_sentries_bitmap = f2fs_kvzalloc(sbi, main_bitmap_size,
								GFP_KERNEL);
	if (!sit_i->dirty_sentries_bitmap)
		return -ENOMEM;

#ifdef CONFIG_F2FS_CHECK_FS
	bitmap_size = MAIN_SEGS(sbi) * SIT_VBLOCK_MAP_SIZE * 4;
#else
	bitmap_size = MAIN_SEGS(sbi) * SIT_VBLOCK_MAP_SIZE * 3;
#endif
	sit_i->bitmap = f2fs_kvzalloc(sbi, bitmap_size, GFP_KERNEL);
	if (!sit_i->bitmap)
		return -ENOMEM;

	bitmap = sit_i->bitmap;

	for (start = 0; start < MAIN_SEGS(sbi); start++) {
		sit_i->sentries[start].cur_valid_map = bitmap;
		bitmap += SIT_VBLOCK_MAP_SIZE;

		sit_i->sentries[start].ckpt_valid_map = bitmap;
		bitmap += SIT_VBLOCK_MAP_SIZE;

#ifdef CONFIG_F2FS_CHECK_FS
		sit_i->sentries[start].cur_valid_map_mir = bitmap;
		bitmap += SIT_VBLOCK_MAP_SIZE;
#endif

		sit_i->sentries[start].discard_map = bitmap;
		bitmap += SIT_VBLOCK_MAP_SIZE;
	}

	sit_i->tmp_map = f2fs_kzalloc(sbi, SIT_VBLOCK_MAP_SIZE, GFP_KERNEL);
	if (!sit_i->tmp_map)
		return -ENOMEM;

	if (__is_large_section(sbi)) {
		sit_i->sec_entries =
			f2fs_kvzalloc(sbi, array_size(sizeof(struct sec_entry),
						      MAIN_SECS(sbi)),
				      GFP_KERNEL);
		if (!sit_i->sec_entries)
			return -ENOMEM;
	}

	/* get information related with SIT */
	sit_segs = le32_to_cpu(raw_super->segment_count_sit) >> 1;

	/* setup SIT bitmap from ckeckpoint pack */
	sit_bitmap_size = __bitmap_size(sbi, SIT_BITMAP);
	src_bitmap = __bitmap_ptr(sbi, SIT_BITMAP);

	sit_i->sit_bitmap = kmemdup(src_bitmap, sit_bitmap_size, GFP_KERNEL);
	if (!sit_i->sit_bitmap)
		return -ENOMEM;

#ifdef CONFIG_F2FS_CHECK_FS
	sit_i->sit_bitmap_mir = kmemdup(src_bitmap,
					sit_bitmap_size, GFP_KERNEL);
	if (!sit_i->sit_bitmap_mir)
		return -ENOMEM;

	sit_i->invalid_segmap = f2fs_kvzalloc(sbi,
					main_bitmap_size, GFP_KERNEL);
	if (!sit_i->invalid_segmap)
		return -ENOMEM;
#endif

	/* init SIT information */
	sit_i->s_ops = &default_salloc_ops;

	sit_i->sit_base_addr = le32_to_cpu(raw_super->sit_blkaddr);
	sit_i->sit_blocks = sit_segs << sbi->log_blocks_per_seg;
	sit_i->written_valid_blocks = 0;
	sit_i->bitmap_size = sit_bitmap_size;
	sit_i->dirty_sentries = 0;
	sit_i->sents_per_block = SIT_ENTRY_PER_BLOCK;
	sit_i->elapsed_time = le64_to_cpu(sbi->ckpt->elapsed_time);
	sit_i->mounted_time = ktime_get_real_seconds();
	init_rwsem(&sit_i->sentry_lock);
	return 0;
}