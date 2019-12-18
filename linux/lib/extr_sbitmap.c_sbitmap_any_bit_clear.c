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
struct sbitmap_word {unsigned long word; unsigned long cleared; unsigned long depth; } ;
struct sbitmap {unsigned int map_nr; struct sbitmap_word* map; } ;

/* Variables and functions */
 unsigned long find_first_zero_bit (unsigned long*,unsigned long) ; 

bool sbitmap_any_bit_clear(const struct sbitmap *sb)
{
	unsigned int i;

	for (i = 0; i < sb->map_nr; i++) {
		const struct sbitmap_word *word = &sb->map[i];
		unsigned long mask = word->word & ~word->cleared;
		unsigned long ret;

		ret = find_first_zero_bit(&mask, word->depth);
		if (ret < word->depth)
			return true;
	}
	return false;
}