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
struct ext4_buddy {TYPE_1__* bd_info; } ;
struct TYPE_2__ {int* bb_counters; } ;

/* Variables and functions */
 scalar_t__ mb_buddy_adjust_border (int*,void*,int) ; 
 int /*<<< orphan*/  mb_clear_bits (void*,int,int) ; 
 void* mb_find_buddy (struct ext4_buddy*,int,int*) ; 

__attribute__((used)) static void mb_buddy_mark_free(struct ext4_buddy *e4b, int first, int last)
{
	int max;
	int order = 1;
	void *buddy = mb_find_buddy(e4b, order, &max);

	while (buddy) {
		void *buddy2;

		/* Bits in range [first; last] are known to be set since
		 * corresponding blocks were allocated. Bits in range
		 * (first; last) will stay set because they form buddies on
		 * upper layer. We just deal with borders if they don't
		 * align with upper layer and then go up.
		 * Releasing entire group is all about clearing
		 * single bit of highest order buddy.
		 */

		/* Example:
		 * ---------------------------------
		 * |   1   |   1   |   1   |   1   |
		 * ---------------------------------
		 * | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
		 * ---------------------------------
		 *   0   1   2   3   4   5   6   7
		 *      \_____________________/
		 *
		 * Neither [1] nor [6] is aligned to above layer.
		 * Left neighbour [0] is free, so mark it busy,
		 * decrease bb_counters and extend range to
		 * [0; 6]
		 * Right neighbour [7] is busy. It can't be coaleasced with [6], so
		 * mark [6] free, increase bb_counters and shrink range to
		 * [0; 5].
		 * Then shift range to [0; 2], go up and do the same.
		 */


		if (first & 1)
			e4b->bd_info->bb_counters[order] += mb_buddy_adjust_border(&first, buddy, -1);
		if (!(last & 1))
			e4b->bd_info->bb_counters[order] += mb_buddy_adjust_border(&last, buddy, 1);
		if (first > last)
			break;
		order++;

		if (first == last || !(buddy2 = mb_find_buddy(e4b, order, &max))) {
			mb_clear_bits(buddy, first, last - first + 1);
			e4b->bd_info->bb_counters[order - 1] += last - first + 1;
			break;
		}
		first >>= 1;
		last >>= 1;
		buddy = buddy2;
	}
}