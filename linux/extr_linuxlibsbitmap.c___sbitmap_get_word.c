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

/* Variables and functions */
 int find_next_zero_bit (unsigned long*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  test_and_set_bit_lock (int,unsigned long*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __sbitmap_get_word(unsigned long *word, unsigned long depth,
			      unsigned int hint, bool wrap)
{
	unsigned int orig_hint = hint;
	int nr;

	while (1) {
		nr = find_next_zero_bit(word, depth, hint);
		if (unlikely(nr >= depth)) {
			/*
			 * We started with an offset, and we didn't reset the
			 * offset to 0 in a failure case, so start from 0 to
			 * exhaust the map.
			 */
			if (orig_hint && hint && wrap) {
				hint = orig_hint = 0;
				continue;
			}
			return -1;
		}

		if (!test_and_set_bit_lock(nr, word))
			break;

		hint = nr + 1;
		if (hint >= depth - 1)
			hint = 0;
	}

	return nr;
}