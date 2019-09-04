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
 int* cp1252_ucs_table ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

int mbfl_filt_conv_cp1252_wchar(int c, mbfl_convert_filter *filter)
{
	int s;

	if (c >= 0x80 && c < 0xa0) {
		s = cp1252_ucs_table[c - 0x80];
	} else {
		s = c;
	}

	CK((*filter->output_function)(s, filter->data));

	return c;
}