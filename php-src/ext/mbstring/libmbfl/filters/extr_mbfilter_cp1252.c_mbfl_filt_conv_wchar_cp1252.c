#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int MBFL_WCSPLANE_8859_1 ; 
 int MBFL_WCSPLANE_MASK ; 
 int* cp1252_ucs_table ; 
 int /*<<< orphan*/  mbfl_filt_conv_illegal_output (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

int mbfl_filt_conv_wchar_cp1252(int c, mbfl_convert_filter *filter)
{
	int s=-1, n;

	if (c >= 0x100)	{
		/* look it up from the cp1252 table */
		s = -1;
		n = 31;
		while (n >= 0) {
			if (c == cp1252_ucs_table[n] && c != 0xfffe) {
				s = 0x80 + n;
				break;
			}
			n--;
		}
		if (s <= 0 && (c & ~MBFL_WCSPLANE_MASK) == MBFL_WCSPLANE_8859_1)
		{
			s = c & MBFL_WCSPLANE_MASK;
		}
	}
	else if (c >= 0 && c < 0x100) {
		s = c;
	}
	if (s >= 0) {
		CK((*filter->output_function)(s, filter->data));
	} else {
		CK(mbfl_filt_conv_illegal_output(c, filter));
	}
	return c;
}