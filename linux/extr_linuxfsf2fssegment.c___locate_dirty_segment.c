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
struct seg_entry {int type; } ;
struct f2fs_sb_info {int dummy; } ;
struct dirty_seglist_info {int /*<<< orphan*/ * nr_dirty; int /*<<< orphan*/ * dirty_segmap; } ;
typedef  enum dirty_type { ____Placeholder_dirty_type } dirty_type ;

/* Variables and functions */
 int DIRTY ; 
 struct dirty_seglist_info* DIRTY_I (struct f2fs_sb_info*) ; 
 scalar_t__ IS_CURSEG (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 struct seg_entry* get_seg_entry (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  test_and_set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __locate_dirty_segment(struct f2fs_sb_info *sbi, unsigned int segno,
		enum dirty_type dirty_type)
{
	struct dirty_seglist_info *dirty_i = DIRTY_I(sbi);

	/* need not be added */
	if (IS_CURSEG(sbi, segno))
		return;

	if (!test_and_set_bit(segno, dirty_i->dirty_segmap[dirty_type]))
		dirty_i->nr_dirty[dirty_type]++;

	if (dirty_type == DIRTY) {
		struct seg_entry *sentry = get_seg_entry(sbi, segno);
		enum dirty_type t = sentry->type;

		if (unlikely(t >= DIRTY)) {
			f2fs_bug_on(sbi, 1);
			return;
		}
		if (!test_and_set_bit(segno, dirty_i->dirty_segmap[t]))
			dirty_i->nr_dirty[t]++;
	}
}