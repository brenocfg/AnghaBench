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
struct TYPE_4__ {int status; int cache; int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int MBFL_WCSPLANE_JIS0208 ; 
 int MBFL_WCSPLANE_JIS0212 ; 
 int MBFL_WCSPLANE_MASK ; 
 int MBFL_WCSPLANE_WINCP932 ; 
 int /*<<< orphan*/  SJIS_ENCODE (int,int,int,int) ; 
 int** code_tbl_m ; 
 int /*<<< orphan*/  mbfl_filt_conv_illegal_output (int,TYPE_1__*) ; 
 int* s_form_sjis_fallback_tbl ; 
 int* s_form_sjis_tbl ; 
 int* s_form_tbl ; 
 int s_form_tbl_len ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int,int /*<<< orphan*/ ) ; 
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
 int** wchar2sjis_mac_code_map ; 
 int** wchar2sjis_mac_r_map ; 
 int wchar2sjis_mac_r_map_len ; 
 int** wchar2sjis_mac_r_tbl ; 
 int wchar2sjis_mac_r_tbl_len ; 
 int** wchar2sjis_mac_wchar_tbl ; 
 int wchar2sjis_mac_wchar_tbl_len ; 

int
mbfl_filt_conv_wchar_sjis_mac(int c, mbfl_convert_filter *filter)
{
	int i;
	int c1, c2, s1, s2, mode;

	s1 = 0;
	s2 = 0;

	// a1: U+0000 -> U+046F
	// a2: U+2000 -> U+30FF
	//  i: U+4E00 -> U+9FFF
	//  r: U+FF00 -> U+FFFF

	switch (filter->status) {

	case 1:
		c1 = filter->cache;
		filter->cache = 0;
		filter->status = 0;

		s1 = 0;
		s2 = 0;

		if (c == 0xf87a) {
			for (i=0;i<4;i++) {
				if (c1 == s_form_tbl[i+34+3+3]) {
					s1 = s_form_sjis_tbl[i+34+3+3];
					break;
				}
			}
			if (s1 <= 0) {
				s2 = c1;
			}
		} else if (c == 0x20dd) {
			for (i=0;i<3;i++) {
				if (c1 == s_form_tbl[i+34+3]) {
					s1 = s_form_sjis_tbl[i+34+3];
					break;
				}
			}
			if (s1 <= 0) {
				s2 = c1;
			}
		} else if (c == 0xf87f) {
			for (i=0;i<3;i++) {
				if (c1 == s_form_tbl[i+34]) {
					s1 = s_form_sjis_tbl[i+34];
					break;
				}
			}
			if (s1 <= 0) {
				s2 = c1; s1 = -1;
			}
		} else if (c == 0xf87e) {
			for (i=0;i<34;i++) {
				if (c1 == s_form_tbl[i]) {
					s1 = s_form_sjis_tbl[i];
					break;
				}
			}
			if (s1 <= 0) {
				s2 = c1; s1 = -1;
			}
		} else {
			s2 = c1;
			s1 = c;
		}

		if (s2 > 0) {
			for (i=0;i<s_form_tbl_len;i++) {
				if (c1 == s_form_tbl[i]) {
					s1 = s_form_sjis_fallback_tbl[i];
					break;
				}
			}
		}

		if (s1 >= 0) {
			if (s1 < 0x100) {
				CK((*filter->output_function)(s1, filter->data));
			} else {
				CK((*filter->output_function)((s1 >> 8) & 0xff, filter->data));
				CK((*filter->output_function)(s1 & 0xff, filter->data));
			}
		} else {
			CK(mbfl_filt_conv_illegal_output(c, filter));
		}

		if (s2 <= 0 || s1 == -1) {
			break;
		}

	case 0:

		if (c >= ucs_a1_jis_table_min && c < ucs_a1_jis_table_max) {
			s1 = ucs_a1_jis_table[c - ucs_a1_jis_table_min];
			if (c == 0x5c) {
				s1 = 0x80;
			} else if (c == 0xa9) {
				s1 = 0xfd;
			}
		} else if (c >= ucs_a2_jis_table_min && c < ucs_a2_jis_table_max) {
			s1 = ucs_a2_jis_table[c - ucs_a2_jis_table_min];
			if (c == 0x2122) {
				s1 = 0xfe;
			} else if (c == 0x2014) {
				s1 = 0x213d;
			} else if (c == 0x2116) {
				s1 = 0x2c1d;
			}
		} else if (c >= ucs_i_jis_table_min && c < ucs_i_jis_table_max) {
			s1 = ucs_i_jis_table[c - ucs_i_jis_table_min];
		} else if (c >= ucs_r_jis_table_min && c < ucs_r_jis_table_max) {
			s1 = ucs_r_jis_table[c - ucs_r_jis_table_min];
		}

		if (c >= 0x2000) {
			for (i=0;i<s_form_tbl_len;i++) {
				if (c == s_form_tbl[i]) {
					filter->status = 1;
					filter->cache = c;
					return c;
				}
			}

			if (c == 0xf860 || c == 0xf861 || c == 0xf862) {
				filter->status = 2;
				filter->cache = c;
				return c;
			}
		}

		if (s1 <= 0) {
			c1 = c & ~MBFL_WCSPLANE_MASK;
			if (c1 == MBFL_WCSPLANE_WINCP932) {
				s1 = c & MBFL_WCSPLANE_MASK;
				s2 = 1;
			} else if (c1 == MBFL_WCSPLANE_JIS0208) {
				s1 = c & MBFL_WCSPLANE_MASK;
			} else if (c1 == MBFL_WCSPLANE_JIS0212) {
				s1 = c & MBFL_WCSPLANE_MASK;
				s1 |= 0x8080;
			} else if (c == 0xa0) {
				s1 = 0x00a0;
			} else if (c == 0xa5) {		/* YEN SIGN */
				s1 = 0x216f;	/* FULLWIDTH YEN SIGN */
			} else if (c == 0xff3c) {	/* FULLWIDTH REVERSE SOLIDUS */
				s1 = 0x2140;
			}
		}

		if (s1 <= 0) {
			for (i=0; i<wchar2sjis_mac_r_tbl_len; i++) {
				if (c >= wchar2sjis_mac_r_tbl[i][0] && c <= wchar2sjis_mac_r_tbl[i][1]) {
					s1 = c - wchar2sjis_mac_r_tbl[i][0] + wchar2sjis_mac_r_tbl[i][2];
					break;
				}
			}

			if (s1 <= 0) {
				for (i=0; i<wchar2sjis_mac_r_map_len; i++) {
					if (c >= wchar2sjis_mac_r_map[i][0] && c <= wchar2sjis_mac_r_map[i][1]) {
						s1 = wchar2sjis_mac_code_map[i][c-wchar2sjis_mac_r_map[i][0]];
						break;
					}
				}
			}

			if (s1 <= 0) {
				for (i=0; i<wchar2sjis_mac_wchar_tbl_len ; i++) {
					if ( c == wchar2sjis_mac_wchar_tbl[i][0]) {
						s1 = wchar2sjis_mac_wchar_tbl[i][1] & 0xffff;
						break;
					}
				}
			}

			if (s1 > 0) {
				c1 = s1/94+0x21;
				c2 = s1-94*(c1-0x21)+0x21;
				s1 = (c1 << 8) | c2;
				s2 = 1;
			}
		}

		if ((s1 <= 0) || (s1 >= 0x8080 && s2 == 0)) {	/* not found or X 0212 */
			s1 = -1;
			c1 = 0;

			if (c == 0) {
				s1 = 0;
			} else if (s1 <= 0) {
				s1 = -1;
			}
		}

		if (s1 >= 0) {
			if (s1 < 0x100) { /* latin or kana */
				CK((*filter->output_function)(s1, filter->data));
			} else { /* kanji */
				c1 = (s1 >> 8) & 0xff;
				c2 = s1 & 0xff;
				SJIS_ENCODE(c1, c2, s1, s2);
				CK((*filter->output_function)(s1, filter->data));
				CK((*filter->output_function)(s2, filter->data));
			}
		} else {
			CK(mbfl_filt_conv_illegal_output(c, filter));
		}
		break;


	case 2:
		c1 = filter->cache;
		filter->cache = 0;
		filter->status = 0;
		if (c1 == 0xf860) {
			for (i=0; i<5; i++) {
				if (c == code_tbl_m[i][2]) {
					filter->cache = c | 0x10000;
					filter->status = 3;
					break;
				}
			}
		} else if (c1 == 0xf861) {
			for (i=0; i<3; i++) {
				if (c == code_tbl_m[i+5][2]) {
					filter->cache = c | 0x20000;
					filter->status = 3;
					break;
				}
			}
		} else if (c1 == 0xf862) {
			for (i=0; i<4; i++) {
				if (c == code_tbl_m[i+5+3][2]) {
					filter->cache = c | 0x40000;
					filter->status = 3;
					break;
				}
			}
		}

		if (filter->status == 0) {
			CK(mbfl_filt_conv_illegal_output(c1, filter));
			CK(mbfl_filt_conv_illegal_output(c, filter));
		}

		break;

	case 3:
		s1 = 0;
		c1 = filter->cache & 0xffff;
		mode = (filter->cache & 0xf0000) >> 16;

		filter->cache = 0;
		filter->status = 0;

		if (mode == 0x1) {
			for (i=0; i<5; i++) {
				if (c1 == code_tbl_m[i][2] && c == code_tbl_m[i][3]) {
					s1 = code_tbl_m[i][0];
					break;
				}
			}

			if (s1 > 0) {
				c1 = s1/94+0x21;
				c2 = s1-94*(c1-0x21)+0x21;
				SJIS_ENCODE(c1, c2, s1, s2);
				CK((*filter->output_function)(s1, filter->data));
				CK((*filter->output_function)(s2, filter->data));
			}

			if (s1 <= 0) {
				CK(mbfl_filt_conv_illegal_output(0xf860, filter));
				CK(mbfl_filt_conv_illegal_output(c1, filter));
				CK(mbfl_filt_conv_illegal_output(c, filter));
			}

		} else if (mode == 0x2) {
			for (i=0; i<3; i++) {
				if (c1 == code_tbl_m[i+5][2] && c == code_tbl_m[i+5][3]) {
					filter->cache = c | 0x20000;
					filter->status = 4;
					break;
				}
			}
		} else if (mode == 0x4) {
			for (i=0; i<4; i++) {
				if (c1 == code_tbl_m[i+8][2] && c == code_tbl_m[i+8][3]) {
					filter->cache = c | 0x40000;
					filter->status = 4;
					break;
				}
			}
		}
		break;

	case 4:
		s1 = 0;
		c1 = filter->cache & 0xffff;
		mode = (filter->cache & 0xf0000) >> 16;

		filter->cache = 0;
		filter->status = 0;

		if (mode == 0x2) {
			for (i=0; i<3; i++) {
				if (c1 == code_tbl_m[i+5][3] && c == code_tbl_m[i+5][4]) {
					s1 = code_tbl_m[i+5][0];
					break;
				}
			}

			if (s1 > 0) {
				c1 = s1/94+0x21;
				c2 = s1-94*(c1-0x21)+0x21;
				SJIS_ENCODE(c1, c2, s1, s2);
				CK((*filter->output_function)(s1, filter->data));
				CK((*filter->output_function)(s2, filter->data));
			}

			if (s1 <= 0) {
				CK(mbfl_filt_conv_illegal_output(0xf861, filter));
				for (i=0; i<3; i++) {
					if (c1 == code_tbl_m[i+5][3]) {
						CK(mbfl_filt_conv_illegal_output(code_tbl_m[i+5][2], filter));
						break;
					}
				}
				CK(mbfl_filt_conv_illegal_output(c1, filter));
				CK(mbfl_filt_conv_illegal_output(c, filter));
			}
		} else if (mode == 0x4) {
			for (i=0; i<4; i++) {
				if (c1 == code_tbl_m[i+8][3] && c == code_tbl_m[i+8][4]) {
					filter->cache = c | 0x40000;
					filter->status = 5;
					break;
				}
			}
		}
		break;

	case 5:
		s1 = 0;
		c1 = filter->cache & 0xffff;
		mode = (filter->cache & 0xf0000) >> 16;

		filter->cache = 0;
		filter->status = 0;

		if (mode == 0x4) {
			for (i=0; i<4; i++) {
				if (c1 == code_tbl_m[i+8][4] && c == code_tbl_m[i+8][5]) {
					s1 = code_tbl_m[i+8][0];
					break;
				}
			}

			if (s1 > 0) {
				c1 = s1/94+0x21;
				c2 = s1-94*(c1-0x21)+0x21;
				SJIS_ENCODE(c1, c2, s1, s2);
				CK((*filter->output_function)(s1, filter->data));
				CK((*filter->output_function)(s2, filter->data));
			}

			if (s1 <= 0) {
				CK(mbfl_filt_conv_illegal_output(0xf862, filter));
				for (i=0; i<4; i++) {
					if (c1 == code_tbl_m[i+8][4]) {
						CK(mbfl_filt_conv_illegal_output( code_tbl_m[i+8][2], filter));
						CK(mbfl_filt_conv_illegal_output( code_tbl_m[i+8][3], filter));
						break;
					}
				}
				CK(mbfl_filt_conv_illegal_output(c1, filter));
				CK(mbfl_filt_conv_illegal_output(c, filter));
			}
		}
		break;

	default:
		filter->status = 0;
		break;
	}
	return c;
}