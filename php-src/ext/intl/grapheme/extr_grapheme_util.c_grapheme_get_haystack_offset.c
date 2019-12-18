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
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  UBreakIterator ;

/* Variables and functions */
 scalar_t__ UBRK_DONE ; 
 int /*<<< orphan*/  ubrk_last (int /*<<< orphan*/ *) ; 
 scalar_t__ ubrk_next (int /*<<< orphan*/ *) ; 
 scalar_t__ ubrk_previous (int /*<<< orphan*/ *) ; 

int32_t grapheme_get_haystack_offset(UBreakIterator* bi, int32_t offset)
{
	int32_t pos;
	int32_t (*iter_op)(UBreakIterator* bi);
	int iter_incr;

	if ( 0 == offset ) {
		return 0;
	}

	if ( offset < 0 ) {
		iter_op = ubrk_previous;
		ubrk_last(bi); /* one past the end */
		iter_incr = 1;
	}
	else {
		iter_op = ubrk_next;
		iter_incr = -1;
	}

	pos = 0;

	while ( pos != UBRK_DONE && offset != 0 ) {

		pos = iter_op(bi);

		if ( UBRK_DONE != pos ) {
			offset += iter_incr;
		}
	}

	if ( offset != 0 ) {
		return -1;
	}

	return pos;
}