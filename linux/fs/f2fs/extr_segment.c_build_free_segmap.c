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
struct free_segmap_info {int /*<<< orphan*/  segmap_lock; scalar_t__ free_sections; scalar_t__ free_segments; int /*<<< orphan*/  start_segno; void* free_secmap; void* free_segmap; } ;
struct f2fs_sb_info {int dummy; } ;
struct TYPE_2__ {struct free_segmap_info* free_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GET_SEGNO_FROM_SEG0 (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAIN_BLKADDR (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  MAIN_SECS (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  MAIN_SEGS (struct f2fs_sb_info*) ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 unsigned int f2fs_bitmap_size (int /*<<< orphan*/ ) ; 
 void* f2fs_kvmalloc (struct f2fs_sb_info*,unsigned int,int /*<<< orphan*/ ) ; 
 struct free_segmap_info* f2fs_kzalloc (struct f2fs_sb_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int build_free_segmap(struct f2fs_sb_info *sbi)
{
	struct free_segmap_info *free_i;
	unsigned int bitmap_size, sec_bitmap_size;

	/* allocate memory for free segmap information */
	free_i = f2fs_kzalloc(sbi, sizeof(struct free_segmap_info), GFP_KERNEL);
	if (!free_i)
		return -ENOMEM;

	SM_I(sbi)->free_info = free_i;

	bitmap_size = f2fs_bitmap_size(MAIN_SEGS(sbi));
	free_i->free_segmap = f2fs_kvmalloc(sbi, bitmap_size, GFP_KERNEL);
	if (!free_i->free_segmap)
		return -ENOMEM;

	sec_bitmap_size = f2fs_bitmap_size(MAIN_SECS(sbi));
	free_i->free_secmap = f2fs_kvmalloc(sbi, sec_bitmap_size, GFP_KERNEL);
	if (!free_i->free_secmap)
		return -ENOMEM;

	/* set all segments as dirty temporarily */
	memset(free_i->free_segmap, 0xff, bitmap_size);
	memset(free_i->free_secmap, 0xff, sec_bitmap_size);

	/* init free segmap information */
	free_i->start_segno = GET_SEGNO_FROM_SEG0(sbi, MAIN_BLKADDR(sbi));
	free_i->free_segments = 0;
	free_i->free_sections = 0;
	spin_lock_init(&free_i->segmap_lock);
	return 0;
}