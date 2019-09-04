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
struct sit_info {int /*<<< orphan*/  dirty_sentries; int /*<<< orphan*/  dirty_sentries_bitmap; } ;
struct f2fs_sb_info {int dummy; } ;

/* Variables and functions */
 struct sit_info* SIT_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  __test_and_set_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __mark_sit_entry_dirty(struct f2fs_sb_info *sbi, unsigned int segno)
{
	struct sit_info *sit_i = SIT_I(sbi);

	if (!__test_and_set_bit(segno, sit_i->dirty_sentries_bitmap)) {
		sit_i->dirty_sentries++;
		return false;
	}

	return true;
}