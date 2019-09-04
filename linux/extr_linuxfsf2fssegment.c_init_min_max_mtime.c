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
struct sit_info {unsigned long long min_mtime; int /*<<< orphan*/  sentry_lock; int /*<<< orphan*/  max_mtime; } ;
struct f2fs_sb_info {unsigned int segs_per_sec; } ;
struct TYPE_2__ {scalar_t__ mtime; } ;

/* Variables and functions */
 unsigned int MAIN_SEGS (struct f2fs_sb_info*) ; 
 struct sit_info* SIT_I (struct f2fs_sb_info*) ; 
 unsigned long long ULLONG_MAX ; 
 unsigned long long div_u64 (unsigned long long,unsigned int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mtime (struct f2fs_sb_info*,int) ; 
 TYPE_1__* get_seg_entry (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_min_max_mtime(struct f2fs_sb_info *sbi)
{
	struct sit_info *sit_i = SIT_I(sbi);
	unsigned int segno;

	down_write(&sit_i->sentry_lock);

	sit_i->min_mtime = ULLONG_MAX;

	for (segno = 0; segno < MAIN_SEGS(sbi); segno += sbi->segs_per_sec) {
		unsigned int i;
		unsigned long long mtime = 0;

		for (i = 0; i < sbi->segs_per_sec; i++)
			mtime += get_seg_entry(sbi, segno + i)->mtime;

		mtime = div_u64(mtime, sbi->segs_per_sec);

		if (sit_i->min_mtime > mtime)
			sit_i->min_mtime = mtime;
	}
	sit_i->max_mtime = get_mtime(sbi, false);
	up_write(&sit_i->sentry_lock);
}