#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int MBFL_WCSGROUP_MASK ; 
 int MBFL_WCSGROUP_THROUGH ; 
 int MBFL_WCSPLANE_CP1251 ; 
 int MBFL_WCSPLANE_MASK ; 
 int* cp1251_ucs_table ; 
 int cp1251_ucs_table_min ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

int
mbfl_filt_conv_cp1251_wchar(int c, mbfl_convert_filter *filter)
{
	int s;

	if (c >= 0 && c < cp1251_ucs_table_min) {
		s = c;
	} else if (c >= cp1251_ucs_table_min && c < 0x100) {
		s = cp1251_ucs_table[c - cp1251_ucs_table_min];
		if (s <= 0) {
			s = c;
			s &= MBFL_WCSPLANE_MASK;
			s |= MBFL_WCSPLANE_CP1251;
		}
	} else {
		s = c;
		s &= MBFL_WCSGROUP_MASK;
		s |= MBFL_WCSGROUP_THROUGH;
	}

	CK((*filter->output_function)(s, filter->data));

	return c;
}