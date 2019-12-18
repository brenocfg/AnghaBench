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
 int* cp932ext1_ucs_table ; 
 int cp932ext1_ucs_table_max ; 
 int cp932ext1_ucs_table_min ; 
 int* cp932ext2_ucs_table ; 
 int cp932ext2_ucs_table_max ; 
 int cp932ext2_ucs_table_min ; 
 int* cp932ext3_eucjp_table ; 
 int const cp932ext3_eucjp_table_size ; 
 int* cp932ext3_ucs_table ; 
 int cp932ext3_ucs_table_max ; 
 int cp932ext3_ucs_table_min ; 
 int /*<<< orphan*/  mbfl_filt_conv_illegal_output (int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub18 (int,int /*<<< orphan*/ ) ; 
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

int
mbfl_filt_conv_wchar_cp50222(int c, mbfl_convert_filter *filter)
{
	int s;

	s = 0;

	if (c >= ucs_a1_jis_table_min && c < ucs_a1_jis_table_max) {
		s = ucs_a1_jis_table[c - ucs_a1_jis_table_min];
	} else if (c >= ucs_a2_jis_table_min && c < ucs_a2_jis_table_max) {
		s = ucs_a2_jis_table[c - ucs_a2_jis_table_min];
	} else if (c >= ucs_i_jis_table_min && c < ucs_i_jis_table_max) {
		s = ucs_i_jis_table[c - ucs_i_jis_table_min];
	} else if (c >= ucs_r_jis_table_min && c < ucs_r_jis_table_max) {
		s = ucs_r_jis_table[c - ucs_r_jis_table_min];
	} else if (c >= 0xe000 && c < (0xe000 + 10 * 94)) {
		/* PUE => Microsoft extended */
		/* See http://www.opengroup.or.jp/jvc/cde/ucs-conv.html#ch4_2 */
		s = c - 0xe000;
		s = (s / 94 + 0x75) << 8 | (s % 94 + 0x21);
	} else if (c >= (0xe000 + 10 * 94) && c <= (0xe000 + 20 * 94)) {
		/* PUE => JISX0212 user-defined (G3 85ku - 94ku) */
		/* See http://www.opengroup.or.jp/jvc/cde/ucs-conv.html#ch4_2 */
		s = c - (0xe000 + 10 * 94);
		s = (s / 94 + 0xf5) << 8 | (s % 94 + 0xa1);
	}

	if (s <= 0) {
		if (c == 0xa5) {			/* YEN SIGN */
			s = 0x1005c;
		} else if (c == 0x203e) {	/* OVER LINE */
			s = 0x1007e;
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
	}
	if (s <= 0 || (s >= 0x8080 && s < 0x10000)) {
		int i;
		s = -1;

		for (i = 0;
				i < cp932ext1_ucs_table_max - cp932ext1_ucs_table_min; i++) {
			const int oh = cp932ext1_ucs_table_min / 94;

			if (c == cp932ext1_ucs_table[i]) {
				s = ((i / 94 + oh + 0x21) << 8) + (i % 94 + 0x21);
				break;
			}
		}

		if (s <= 0) {
			const int oh = cp932ext2_ucs_table_min / 94;
			const int cp932ext2_ucs_table_size =
					cp932ext2_ucs_table_max - cp932ext2_ucs_table_min;
			for (i = 0; i < cp932ext2_ucs_table_size; i++) {
				if (c == cp932ext2_ucs_table[i]) {
					s = ((i / 94 + oh + 0x21) << 8) + (i % 94 + 0x21);
					break;
				}
			}
		}

		if (s <= 0) {
			const int cp932ext3_ucs_table_size =
					cp932ext3_ucs_table_max - cp932ext3_ucs_table_min;
			const int limit = cp932ext3_ucs_table_size >
					cp932ext3_eucjp_table_size ?
						cp932ext3_eucjp_table_size:
						cp932ext3_ucs_table_size;
			for (i = 0; i < limit; i++) {
				if (c == cp932ext3_ucs_table[i]) {
					s = cp932ext3_eucjp_table[i];
					break;
				}
			}
		}

		if (c == 0) {
			s = 0;
		} else if (s <= 0) {
			s = -1;
		}
	}

	if (s >= 0) {
		if (s < 0x80) { /* ASCII */
			if ((filter->status & 0xff00) == 0x500) {
				CK((*filter->output_function)(0x0f, filter->data));		/* SO */
				filter->status = 0;
			} else if ((filter->status & 0xff00) != 0) {
				CK((*filter->output_function)(0x1b, filter->data));		/* ESC */
				CK((*filter->output_function)(0x28, filter->data));		/* '(' */
				CK((*filter->output_function)(0x42, filter->data));		/* 'B' */
				filter->status = 0;
			}
			CK((*filter->output_function)(s, filter->data));
		} else if (s >= 0xa0 && s < 0xe0) { /* X 0201 kana */
			if ((filter->status & 0xff00) != 0x500) {
				CK((*filter->output_function)(0x0e, filter->data));		/* SI */
				filter->status = 0x500;
			}
			CK((*filter->output_function)(s - 0x80, filter->data));
		} else if (s < 0x8080) { /* X 0208 */
			if ((filter->status & 0xff00) == 0x500) {
				CK((*filter->output_function)(0x0f, filter->data));		/* SO */
				filter->status = 0;
			}
			if ((filter->status & 0xff00) != 0x200) {
				CK((*filter->output_function)(0x1b, filter->data));		/* ESC */
				CK((*filter->output_function)(0x24, filter->data));		/* '$' */
				CK((*filter->output_function)(0x42, filter->data));		/* 'B' */
				filter->status = 0x200;
			}
			CK((*filter->output_function)((s >> 8) & 0x7f, filter->data));
			CK((*filter->output_function)(s & 0x7f, filter->data));
		} else if (s < 0x10000) { /* X0212 */
			CK(mbfl_filt_conv_illegal_output(c, filter));
		} else { /* X 0201 latin */
			if ((filter->status & 0xff00) == 0x500) {
				CK((*filter->output_function)(0x0f, filter->data));		/* SO */
				filter->status = 0;
			}
			if ((filter->status & 0xff00) != 0x400) {
				CK((*filter->output_function)(0x1b, filter->data));		/* ESC */
				CK((*filter->output_function)(0x28, filter->data));		/* '(' */
				CK((*filter->output_function)(0x4a, filter->data));		/* 'J' */
			}
			filter->status = 0x400;
			CK((*filter->output_function)(s & 0x7f, filter->data));
		}
	} else {
		CK(mbfl_filt_conv_illegal_output(c, filter));
	}

	return c;
}