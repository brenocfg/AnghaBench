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
struct f2fs_sb_info {int dummy; } ;
struct dirty_seglist_info {int /*<<< orphan*/ * dirty_segmap; int /*<<< orphan*/  seglist_lock; } ;
struct TYPE_2__ {struct dirty_seglist_info* dirty_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAIN_SEGS (struct f2fs_sb_info*) ; 
 unsigned int NR_DIRTY_TYPE ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 unsigned int f2fs_bitmap_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_kvzalloc (struct f2fs_sb_info*,unsigned int,int /*<<< orphan*/ ) ; 
 struct dirty_seglist_info* f2fs_kzalloc (struct f2fs_sb_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_dirty_segmap (struct f2fs_sb_info*) ; 
 int init_victim_secmap (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int build_dirty_segmap(struct f2fs_sb_info *sbi)
{
	struct dirty_seglist_info *dirty_i;
	unsigned int bitmap_size, i;

	/* allocate memory for dirty segments list information */
	dirty_i = f2fs_kzalloc(sbi, sizeof(struct dirty_seglist_info),
								GFP_KERNEL);
	if (!dirty_i)
		return -ENOMEM;

	SM_I(sbi)->dirty_info = dirty_i;
	mutex_init(&dirty_i->seglist_lock);

	bitmap_size = f2fs_bitmap_size(MAIN_SEGS(sbi));

	for (i = 0; i < NR_DIRTY_TYPE; i++) {
		dirty_i->dirty_segmap[i] = f2fs_kvzalloc(sbi, bitmap_size,
								GFP_KERNEL);
		if (!dirty_i->dirty_segmap[i])
			return -ENOMEM;
	}

	init_dirty_segmap(sbi);
	return init_victim_secmap(sbi);
}