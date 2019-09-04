#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sit_info {struct sit_info* sit_bitmap; TYPE_1__* dirty_sentries_bitmap; TYPE_1__* sec_entries; TYPE_1__* sentries; struct sit_info* tmp_map; } ;
struct f2fs_sb_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sit_info; } ;
struct TYPE_3__ {struct sit_info* discard_map; struct sit_info* ckpt_valid_map; struct sit_info* cur_valid_map; } ;

/* Variables and functions */
 unsigned int MAIN_SEGS (struct f2fs_sb_info*) ; 
 struct sit_info* SIT_I (struct f2fs_sb_info*) ; 
 TYPE_2__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  kfree (struct sit_info*) ; 
 int /*<<< orphan*/  kvfree (TYPE_1__*) ; 

__attribute__((used)) static void destroy_sit_info(struct f2fs_sb_info *sbi)
{
	struct sit_info *sit_i = SIT_I(sbi);
	unsigned int start;

	if (!sit_i)
		return;

	if (sit_i->sentries) {
		for (start = 0; start < MAIN_SEGS(sbi); start++) {
			kfree(sit_i->sentries[start].cur_valid_map);
#ifdef CONFIG_F2FS_CHECK_FS
			kfree(sit_i->sentries[start].cur_valid_map_mir);
#endif
			kfree(sit_i->sentries[start].ckpt_valid_map);
			kfree(sit_i->sentries[start].discard_map);
		}
	}
	kfree(sit_i->tmp_map);

	kvfree(sit_i->sentries);
	kvfree(sit_i->sec_entries);
	kvfree(sit_i->dirty_sentries_bitmap);

	SM_I(sbi)->sit_info = NULL;
	kfree(sit_i->sit_bitmap);
#ifdef CONFIG_F2FS_CHECK_FS
	kfree(sit_i->sit_bitmap_mir);
#endif
	kfree(sit_i);
}