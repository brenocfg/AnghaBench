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
typedef  scalar_t__ u32 ;

/* Variables and functions */

__attribute__((used)) static void ocfs2_calc_extent_defrag_len(u32 *alloc_size, u32 *len_defraged,
					 u32 threshold, int *skip)
{
	if ((*alloc_size + *len_defraged) < threshold) {
		/*
		 * proceed defragmentation until we meet the thresh
		 */
		*len_defraged += *alloc_size;
	} else if (*len_defraged == 0) {
		/*
		 * XXX: skip a large extent.
		 */
		*skip = 1;
	} else {
		/*
		 * split this extent to coalesce with former pieces as
		 * to reach the threshold.
		 *
		 * we're done here with one cycle of defragmentation
		 * in a size of 'thresh', resetting 'len_defraged'
		 * forces a new defragmentation.
		 */
		*alloc_size = threshold - *len_defraged;
		*len_defraged = 0;
	}
}