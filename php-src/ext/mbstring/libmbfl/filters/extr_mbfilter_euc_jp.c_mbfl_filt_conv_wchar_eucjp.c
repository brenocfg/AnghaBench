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
 int MBFL_WCSPLANE_JIS0208 ; 
 int MBFL_WCSPLANE_JIS0212 ; 
 int MBFL_WCSPLANE_MASK ; 
 int /*<<< orphan*/  mbfl_filt_conv_illegal_output (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ ) ; 
 int* ucs_a1_jis_table ; 
 int ucs_a1_jis_table_max ; 
 int ucs_a1_jis_table_min ; 
 int* ucs_a2_jis_table ; 
 int ucs_a2_jis_table_max ; 
 int ucs_a2_jis_table_min ; 
 int* ucs_i_jis_table ; 
 int ucs_i_jis_table_max ; 
 int ucs_i_jis_table_min ; 
 int* ucs_r_jis_table ; 
 int ucs_r_jis_table_max ; 
 int ucs_r_jis_table_min ; 

int
mbfl_filt_conv_wchar_eucjp(int c, mbfl_convert_filter *filter)
{
	int c1, s;

	s = 0;
	if (c >= ucs_a1_jis_table_min && c < ucs_a1_jis_table_max) {
		s = ucs_a1_jis_table[c - ucs_a1_jis_table_min];
	} else if (c >= ucs_a2_jis_table_min && c < ucs_a2_jis_table_max) {
		s = ucs_a2_jis_table[c - ucs_a2_jis_table_min];
	} else if (c >= ucs_i_jis_table_min && c < ucs_i_jis_table_max) {
		s = ucs_i_jis_table[c - ucs_i_jis_table_min];
	} else if (c >= ucs_r_jis_table_min && c < ucs_r_jis_table_max) {
		s = ucs_r_jis_table[c - ucs_r_jis_table_min];
	}
	if (s <= 0) {
		c1 = c & ~MBFL_WCSPLANE_MASK;
		if (c1 == MBFL_WCSPLANE_JIS0208) {
			s = c & MBFL_WCSPLANE_MASK;
		} else if (c1 == MBFL_WCSPLANE_JIS0212) {
			s = c & MBFL_WCSPLANE_MASK;
			s |= 0x8080;
		} else if (c == 0xff3c) {	/* FULLWIDTH REVERSE SOLIDUS */
			s = 0x2140;
		} else if (c == 0xff5e) {	/* FULLWIDTH TILDE */
			s = 0x2141;
		} else if (c == 0x2225) {	/* PARALLEL TO */
			s = 0x2142;
		} else if (c == 0xff0d) {	/* FULLWIDTH HYPHEN-MINUS */
			s = 0x215d;
		} else if (c == 0xffe0) {	/* FULLWIDTH CENT SIGN */
			s = 0x2171;
		} else if (c == 0xffe1) {	/* FULLWIDTH POUND SIGN */
			s = 0x2172;
		} else if (c == 0xffe2) {	/* FULLWIDTH NOT SIGN */
			s = 0x224c;
		}
		if (c == 0) {
			s = 0;
		} else if (s <= 0) {
			s = -1;
		}
	}
	if (s >= 0) {
		if (s < 0x80) {	/* latin */
			CK((*filter->output_function)(s, filter->data));
		} else if (s < 0x100) {	/* kana */
			CK((*filter->output_function)(0x8e, filter->data));
			CK((*filter->output_function)(s, filter->data));
		} else if (s < 0x8080)  {	/* X 0208 */
			CK((*filter->output_function)(((s >> 8) & 0xff) | 0x80, filter->data));
			CK((*filter->output_function)((s & 0xff) | 0x80, filter->data));
		} else {	/* X 0212 */
			CK((*filter->output_function)(0x8f, filter->data));
			CK((*filter->output_function)(((s >> 8) & 0xff) | 0x80, filter->data));
			CK((*filter->output_function)((s & 0xff) | 0x80, filter->data));
		}
	} else {
		CK(mbfl_filt_conv_illegal_output(c, filter));
	}

	return c;
}