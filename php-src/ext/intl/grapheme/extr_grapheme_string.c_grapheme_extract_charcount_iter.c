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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  UBreakIterator ;

/* Variables and functions */
 int /*<<< orphan*/  U8_FWD_1 (unsigned char*,int,int) ; 
 int UBRK_DONE ; 
 int ubrk_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int32_t
grapheme_extract_charcount_iter(UBreakIterator *bi, int32_t csize, unsigned char *pstr, int32_t str_len)
{
	int pos = 0;
	int ret_pos = 0;
	int break_pos, prev_break_pos;
	int count = 0;

	while ( 1 ) {
		pos = ubrk_next(bi);

		if ( UBRK_DONE == pos ) {
			break;
		}

		for ( break_pos = ret_pos; break_pos < pos; ) {
			count++;
			prev_break_pos = break_pos;
			U8_FWD_1(pstr, break_pos, str_len);

			if ( prev_break_pos == break_pos ) {
				/* something wrong - malformed utf8? */
				csize = 0;
				break;
			}
		}

		/* if we are beyond our limit, then the loop is done */
		if ( count > csize ) {
			break;
		}

		ret_pos = break_pos;
	}

	return ret_pos;
}