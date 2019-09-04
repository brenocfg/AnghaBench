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
struct f2fs_stat_info {void* avg_vblocks; scalar_t__ dirty_count; int /*<<< orphan*/  bimodal; } ;
struct f2fs_sb_info {scalar_t__ segs_per_sec; } ;

/* Variables and functions */
 unsigned long long BLKS_PER_SEC (struct f2fs_sb_info*) ; 
 struct f2fs_stat_info* F2FS_STAT (struct f2fs_sb_info*) ; 
 unsigned long long MAIN_SECS (struct f2fs_sb_info*) ; 
 unsigned int MAIN_SEGS (struct f2fs_sb_info*) ; 
 unsigned long long abs (unsigned int) ; 
 int /*<<< orphan*/  div64_u64 (unsigned long long,unsigned long long) ; 
 void* div_u64 (unsigned long long,int) ; 
 unsigned int get_valid_blocks (struct f2fs_sb_info*,unsigned int,int) ; 

__attribute__((used)) static void update_sit_info(struct f2fs_sb_info *sbi)
{
	struct f2fs_stat_info *si = F2FS_STAT(sbi);
	unsigned long long blks_per_sec, hblks_per_sec, total_vblocks;
	unsigned long long bimodal, dist;
	unsigned int segno, vblocks;
	int ndirty = 0;

	bimodal = 0;
	total_vblocks = 0;
	blks_per_sec = BLKS_PER_SEC(sbi);
	hblks_per_sec = blks_per_sec / 2;
	for (segno = 0; segno < MAIN_SEGS(sbi); segno += sbi->segs_per_sec) {
		vblocks = get_valid_blocks(sbi, segno, true);
		dist = abs(vblocks - hblks_per_sec);
		bimodal += dist * dist;

		if (vblocks > 0 && vblocks < blks_per_sec) {
			total_vblocks += vblocks;
			ndirty++;
		}
	}
	dist = div_u64(MAIN_SECS(sbi) * hblks_per_sec * hblks_per_sec, 100);
	si->bimodal = div64_u64(bimodal, dist);
	if (si->dirty_count)
		si->avg_vblocks = div_u64(total_vblocks, ndirty);
	else
		si->avg_vblocks = 0;
}