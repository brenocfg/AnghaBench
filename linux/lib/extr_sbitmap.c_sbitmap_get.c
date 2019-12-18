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
struct sbitmap {unsigned int map_nr; unsigned int shift; } ;

/* Variables and functions */
 unsigned int SB_NR_TO_BIT (struct sbitmap*,unsigned int) ; 
 unsigned int SB_NR_TO_INDEX (struct sbitmap*,unsigned int) ; 
 int sbitmap_find_bit_in_index (struct sbitmap*,unsigned int,unsigned int,int) ; 

int sbitmap_get(struct sbitmap *sb, unsigned int alloc_hint, bool round_robin)
{
	unsigned int i, index;
	int nr = -1;

	index = SB_NR_TO_INDEX(sb, alloc_hint);

	/*
	 * Unless we're doing round robin tag allocation, just use the
	 * alloc_hint to find the right word index. No point in looping
	 * twice in find_next_zero_bit() for that case.
	 */
	if (round_robin)
		alloc_hint = SB_NR_TO_BIT(sb, alloc_hint);
	else
		alloc_hint = 0;

	for (i = 0; i < sb->map_nr; i++) {
		nr = sbitmap_find_bit_in_index(sb, index, alloc_hint,
						round_robin);
		if (nr != -1) {
			nr += index << sb->shift;
			break;
		}

		/* Jump to next index. */
		alloc_hint = 0;
		if (++index >= sb->map_nr)
			index = 0;
	}

	return nr;
}