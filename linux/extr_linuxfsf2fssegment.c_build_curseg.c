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
struct f2fs_journal {int dummy; } ;
struct curseg_info {scalar_t__ next_blkoff; int /*<<< orphan*/  segno; void* journal; int /*<<< orphan*/  journal_rwsem; void* sum_blk; int /*<<< orphan*/  curseg_mutex; } ;
struct TYPE_2__ {struct curseg_info* curseg_array; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NR_CURSEG_TYPE ; 
 int /*<<< orphan*/  NULL_SEGNO ; 
 int PAGE_SIZE ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int array_size (int,int) ; 
 void* f2fs_kzalloc (struct f2fs_sb_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int restore_curseg_summaries (struct f2fs_sb_info*) ; 

__attribute__((used)) static int build_curseg(struct f2fs_sb_info *sbi)
{
	struct curseg_info *array;
	int i;

	array = f2fs_kzalloc(sbi, array_size(NR_CURSEG_TYPE, sizeof(*array)),
			     GFP_KERNEL);
	if (!array)
		return -ENOMEM;

	SM_I(sbi)->curseg_array = array;

	for (i = 0; i < NR_CURSEG_TYPE; i++) {
		mutex_init(&array[i].curseg_mutex);
		array[i].sum_blk = f2fs_kzalloc(sbi, PAGE_SIZE, GFP_KERNEL);
		if (!array[i].sum_blk)
			return -ENOMEM;
		init_rwsem(&array[i].journal_rwsem);
		array[i].journal = f2fs_kzalloc(sbi,
				sizeof(struct f2fs_journal), GFP_KERNEL);
		if (!array[i].journal)
			return -ENOMEM;
		array[i].segno = NULL_SEGNO;
		array[i].next_blkoff = 0;
	}
	return restore_curseg_summaries(sbi);
}