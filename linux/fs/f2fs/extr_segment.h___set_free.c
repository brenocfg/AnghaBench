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
struct free_segmap_info {int /*<<< orphan*/  segmap_lock; int /*<<< orphan*/  free_sections; int /*<<< orphan*/  free_secmap; int /*<<< orphan*/  free_segmap; int /*<<< orphan*/  free_segments; } ;
struct f2fs_sb_info {unsigned int segs_per_sec; } ;

/* Variables and functions */
 struct free_segmap_info* FREE_I (struct f2fs_sb_info*) ; 
 unsigned int GET_SEC_FROM_SEG (struct f2fs_sb_info*,unsigned int) ; 
 unsigned int GET_SEG_FROM_SEC (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int find_next_bit (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __set_free(struct f2fs_sb_info *sbi, unsigned int segno)
{
	struct free_segmap_info *free_i = FREE_I(sbi);
	unsigned int secno = GET_SEC_FROM_SEG(sbi, segno);
	unsigned int start_segno = GET_SEG_FROM_SEC(sbi, secno);
	unsigned int next;

	spin_lock(&free_i->segmap_lock);
	clear_bit(segno, free_i->free_segmap);
	free_i->free_segments++;

	next = find_next_bit(free_i->free_segmap,
			start_segno + sbi->segs_per_sec, start_segno);
	if (next >= start_segno + sbi->segs_per_sec) {
		clear_bit(secno, free_i->free_secmap);
		free_i->free_sections++;
	}
	spin_unlock(&free_i->segmap_lock);
}