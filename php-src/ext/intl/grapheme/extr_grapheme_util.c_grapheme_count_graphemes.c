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
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  int /*<<< orphan*/  UChar ;
typedef  int /*<<< orphan*/  UBreakIterator ;

/* Variables and functions */
 int UBRK_DONE ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int ubrk_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubrk_setText (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int32_t grapheme_count_graphemes(UBreakIterator *bi, UChar *string, int32_t string_len)
{
	int ret_len = 0;
	int pos = 0;
	UErrorCode		status = U_ZERO_ERROR;

	ubrk_setText(bi, string, string_len, &status);

	do {

		pos = ubrk_next(bi);

		if ( UBRK_DONE != pos ) {
			ret_len++;
		}

	} while ( UBRK_DONE != pos );

	return ret_len;
}