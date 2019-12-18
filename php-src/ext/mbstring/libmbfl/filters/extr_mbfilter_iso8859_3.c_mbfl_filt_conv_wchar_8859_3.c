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
 int MBFL_WCSPLANE_8859_3 ; 
 int MBFL_WCSPLANE_MASK ; 
 int* iso8859_3_ucs_table ; 
 int /*<<< orphan*/  mbfl_filt_conv_illegal_output (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

int mbfl_filt_conv_wchar_8859_3(int c, mbfl_convert_filter *filter)
{
	int s, n;

	if (c >= 0 && c < 0xa0) {
		s = c;
	} else {
		s = -1;
		n = 95;
		while (n >= 0) {
			if (c == iso8859_3_ucs_table[n]) {
				s = 0xa0 + n;
				break;
			}
			n--;
		}
		if (s <= 0 && (c & ~MBFL_WCSPLANE_MASK) == MBFL_WCSPLANE_8859_3) {
			s = c & MBFL_WCSPLANE_MASK;
		}
	}

	if (s >= 0) {
		CK((*filter->output_function)(s, filter->data));
	} else {
		CK(mbfl_filt_conv_illegal_output(c, filter));
	}

	return c;
}