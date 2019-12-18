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
 int MBFL_WCSPLANE_CNS11643 ; 
 int MBFL_WCSPLANE_MASK ; 
 int /*<<< orphan*/  mbfl_filt_conv_illegal_output (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ) ; 
 int* ucs_a1_cns11643_table ; 
 int ucs_a1_cns11643_table_max ; 
 int ucs_a1_cns11643_table_min ; 
 int* ucs_a2_cns11643_table ; 
 int ucs_a2_cns11643_table_max ; 
 int ucs_a2_cns11643_table_min ; 
 int* ucs_a3_cns11643_table ; 
 int ucs_a3_cns11643_table_max ; 
 int ucs_a3_cns11643_table_min ; 
 int* ucs_i_cns11643_table ; 
 int ucs_i_cns11643_table_max ; 
 int ucs_i_cns11643_table_min ; 
 int* ucs_r_cns11643_table ; 
 int ucs_r_cns11643_table_max ; 
 int ucs_r_cns11643_table_min ; 

int
mbfl_filt_conv_wchar_euctw(int c, mbfl_convert_filter *filter)
{
	int c1, s, plane;

	s = 0;
	if (c >= ucs_a1_cns11643_table_min && c < ucs_a1_cns11643_table_max) {
		s = ucs_a1_cns11643_table[c - ucs_a1_cns11643_table_min];
	} else if (c >= ucs_a2_cns11643_table_min && c < ucs_a2_cns11643_table_max) {
		s = ucs_a2_cns11643_table[c - ucs_a2_cns11643_table_min];
	} else if (c >= ucs_a3_cns11643_table_min && c < ucs_a3_cns11643_table_max) {
		s = ucs_a3_cns11643_table[c - ucs_a3_cns11643_table_min];
	} else if (c >= ucs_i_cns11643_table_min && c < ucs_i_cns11643_table_max) {
		s = ucs_i_cns11643_table[c - ucs_i_cns11643_table_min];
	} else if (c >= ucs_r_cns11643_table_min && c < ucs_r_cns11643_table_max) {
		s = ucs_r_cns11643_table[c - ucs_r_cns11643_table_min];
	}
	if (s <= 0) {
		c1 = c & ~MBFL_WCSPLANE_MASK;
		if (c1 == MBFL_WCSPLANE_CNS11643) {
			s = c & MBFL_WCSPLANE_MASK;
		}
		if (c == 0) {
			s = 0;
		} else if (s <= 0) {
			s = -1;
		}
	}
	if (s >= 0) {
		plane = (s & 0x1f0000) >> 16;
		if (plane <= 1){
			if (s < 0x80) {	/* latin */
				CK((*filter->output_function)(s, filter->data));
			} else {
				s = (s & 0xffff) | 0x8080;
				CK((*filter->output_function)((s >> 8) & 0xff, filter->data));
				CK((*filter->output_function)(s & 0xff, filter->data));
			}
		} else {
			s = (0x8ea00000 + (plane << 16)) | ((s & 0xffff) | 0x8080);
			CK((*filter->output_function)(0x8e , filter->data));
			CK((*filter->output_function)((s >> 16) & 0xff, filter->data));
			CK((*filter->output_function)((s >> 8) & 0xff, filter->data));
			CK((*filter->output_function)(s & 0xff, filter->data));
		}
	} else {
		CK(mbfl_filt_conv_illegal_output(c, filter));
	}
	return c;
}