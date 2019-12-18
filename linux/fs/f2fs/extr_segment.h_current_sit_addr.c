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
struct sit_info {scalar_t__ sit_blocks; int /*<<< orphan*/  sit_bitmap; int /*<<< orphan*/  sit_bitmap_mir; scalar_t__ sit_base_addr; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  scalar_t__ pgoff_t ;
typedef  scalar_t__ block_t ;

/* Variables and functions */
 unsigned int SIT_BLOCK_OFFSET (unsigned int) ; 
 struct sit_info* SIT_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  check_seg_range (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 scalar_t__ f2fs_test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline pgoff_t current_sit_addr(struct f2fs_sb_info *sbi,
						unsigned int start)
{
	struct sit_info *sit_i = SIT_I(sbi);
	unsigned int offset = SIT_BLOCK_OFFSET(start);
	block_t blk_addr = sit_i->sit_base_addr + offset;

	check_seg_range(sbi, start);

#ifdef CONFIG_F2FS_CHECK_FS
	if (f2fs_test_bit(offset, sit_i->sit_bitmap) !=
			f2fs_test_bit(offset, sit_i->sit_bitmap_mir))
		f2fs_bug_on(sbi, 1);
#endif

	/* calculate sit block address */
	if (f2fs_test_bit(offset, sit_i->sit_bitmap))
		blk_addr += sit_i->sit_blocks;

	return blk_addr;
}