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
struct TYPE_4__ {int status; int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int const,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int MBFL_WCSPLANE_JIS0208 ; 
 int MBFL_WCSPLANE_MASK ; 
 int mbfl_filt_conv_wchar_cp50221 (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int const,int /*<<< orphan*/ ) ; 

int
mbfl_filt_conv_wchar_cp50220raw(int c, mbfl_convert_filter *filter)
{
	if (c & MBFL_WCSPLANE_JIS0208) {
		const int s = c & MBFL_WCSPLANE_MASK;

		if ((filter->status & 0xff00) != 0x200) {
			CK((*filter->output_function)(0x1b, filter->data));		/* ESC */
			CK((*filter->output_function)(0x24, filter->data));		/* '$' */
			CK((*filter->output_function)(0x42, filter->data));		/* 'B' */
			filter->status = 0x200;
		}
		CK((*filter->output_function)((s >> 8) & 0x7f, filter->data));
		CK((*filter->output_function)(s & 0x7f, filter->data));
		return c;
	} else {
		return mbfl_filt_conv_wchar_cp50221(c, filter);
	}
}