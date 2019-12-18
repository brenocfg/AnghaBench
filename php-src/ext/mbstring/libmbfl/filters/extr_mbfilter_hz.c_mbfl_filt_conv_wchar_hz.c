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
struct TYPE_4__ {int status; int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbfl_filt_conv_illegal_output (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ ) ; 
 int* ucs_a1_cp936_table ; 
 int ucs_a1_cp936_table_max ; 
 int ucs_a1_cp936_table_min ; 
 int* ucs_a2_cp936_table ; 
 int ucs_a2_cp936_table_max ; 
 int ucs_a2_cp936_table_min ; 
 int* ucs_a3_cp936_table ; 
 int ucs_a3_cp936_table_max ; 
 int ucs_a3_cp936_table_min ; 
 int ucs_hff_cp936_table_max ; 
 int ucs_hff_cp936_table_min ; 
 int* ucs_hff_s_cp936_table ; 
 int* ucs_i_cp936_table ; 
 int ucs_i_cp936_table_max ; 
 int ucs_i_cp936_table_min ; 

int
mbfl_filt_conv_wchar_hz(int c, mbfl_convert_filter *filter)
{
	int s;

	s = 0;
	if (c >= ucs_a1_cp936_table_min && c < ucs_a1_cp936_table_max) {
		s = ucs_a1_cp936_table[c - ucs_a1_cp936_table_min];
	} else if (c >= ucs_a2_cp936_table_min && c < ucs_a2_cp936_table_max) {
		s = ucs_a2_cp936_table[c - ucs_a2_cp936_table_min];
	} else if (c >= ucs_a3_cp936_table_min && c < ucs_a3_cp936_table_max) {
		s = ucs_a3_cp936_table[c - ucs_a3_cp936_table_min];
	} else if (c >= ucs_i_cp936_table_min && c < ucs_i_cp936_table_max) {
		s = ucs_i_cp936_table[c - ucs_i_cp936_table_min];
	} else if (c >= ucs_hff_cp936_table_min && c < ucs_hff_cp936_table_max) {
		if (c == 0xff04) {
			s = 0xa1e7;
		} else if (c == 0xff5e) {
			s = 0xa1ab;
		} else if (c >= 0xff01 && c <= 0xff5d) {
			s = c - 0xff01 + 0xa3a1;
		} else if (c >= 0xffe0 && c <= 0xffe5) {
			s = ucs_hff_s_cp936_table[c-0xffe0];
		}
	}
	if (s & 0x8000) {
		s -= 0x8080;
	}

	if (s <= 0) {
		if (c == 0) {
			s = 0;
		} else if (s <= 0) {
			s = -1;
		}
	} else if ((s >= 0x80 && s < 0x2121) || (s > 0x8080)) {
		s = -1;
	}
	if (s >= 0) {
		if (s < 0x80) { /* ASCII */
			if ((filter->status & 0xff00) != 0) {
				CK((*filter->output_function)(0x7e, filter->data));		/* '~' */
				CK((*filter->output_function)(0x7d, filter->data));		/* '}' */
			}
			filter->status = 0;
			if (s == 0x7e){
				CK((*filter->output_function)(0x7e, filter->data));
			}
			CK((*filter->output_function)(s, filter->data));
		} else { /* GB 2312-80 */
			if ((filter->status & 0xff00) != 0x200) {
				CK((*filter->output_function)(0x7e, filter->data));		/* '~' */
				CK((*filter->output_function)(0x7b, filter->data));		/* '{' */
			}
			filter->status = 0x200;
			CK((*filter->output_function)((s >> 8) & 0x7f, filter->data));
			CK((*filter->output_function)(s & 0x7f, filter->data));
		}
	} else {
		CK(mbfl_filt_conv_illegal_output(c, filter));
	}

	return c;
}