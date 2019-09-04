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
struct sit_info {unsigned long long min_mtime; unsigned long long max_mtime; } ;
struct f2fs_sb_info {unsigned int segs_per_sec; unsigned int log_blocks_per_seg; } ;
struct TYPE_2__ {scalar_t__ mtime; } ;

/* Variables and functions */
 unsigned int GET_SEC_FROM_SEG (struct f2fs_sb_info*,unsigned int) ; 
 unsigned int GET_SEG_FROM_SEC (struct f2fs_sb_info*,unsigned int) ; 
 struct sit_info* SIT_I (struct f2fs_sb_info*) ; 
 unsigned int UINT_MAX ; 
 int div64_u64 (int,unsigned long long) ; 
 void* div_u64 (unsigned int,unsigned int) ; 
 TYPE_1__* get_seg_entry (struct f2fs_sb_info*,unsigned int) ; 
 unsigned int get_valid_blocks (struct f2fs_sb_info*,unsigned int,int) ; 

__attribute__((used)) static unsigned int get_cb_cost(struct f2fs_sb_info *sbi, unsigned int segno)
{
	struct sit_info *sit_i = SIT_I(sbi);
	unsigned int secno = GET_SEC_FROM_SEG(sbi, segno);
	unsigned int start = GET_SEG_FROM_SEC(sbi, secno);
	unsigned long long mtime = 0;
	unsigned int vblocks;
	unsigned char age = 0;
	unsigned char u;
	unsigned int i;

	for (i = 0; i < sbi->segs_per_sec; i++)
		mtime += get_seg_entry(sbi, start + i)->mtime;
	vblocks = get_valid_blocks(sbi, segno, true);

	mtime = div_u64(mtime, sbi->segs_per_sec);
	vblocks = div_u64(vblocks, sbi->segs_per_sec);

	u = (vblocks * 100) >> sbi->log_blocks_per_seg;

	/* Handle if the system time has changed by the user */
	if (mtime < sit_i->min_mtime)
		sit_i->min_mtime = mtime;
	if (mtime > sit_i->max_mtime)
		sit_i->max_mtime = mtime;
	if (sit_i->max_mtime != sit_i->min_mtime)
		age = 100 - div64_u64(100 * (mtime - sit_i->min_mtime),
				sit_i->max_mtime - sit_i->min_mtime);

	return UINT_MAX - ((100 * (100 - u) * age) / (100 + u));
}