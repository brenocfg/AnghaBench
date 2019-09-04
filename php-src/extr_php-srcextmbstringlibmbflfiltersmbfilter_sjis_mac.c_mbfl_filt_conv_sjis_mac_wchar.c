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
struct TYPE_3__ {int status; int cache; int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int MBFL_WCSGROUP_MASK ; 
 int MBFL_WCSGROUP_THROUGH ; 
 int MBFL_WCSPLANE_MASK ; 
 int MBFL_WCSPLANE_WINCP932 ; 
 int /*<<< orphan*/  SJIS_DECODE (int,int,int,int) ; 
 int** code_map ; 
 int** code_ofst_tbl ; 
 int** code_tbl ; 
 int** code_tbl_m ; 
 int code_tbl_m_len ; 
 int* jisx0208_ucs_table ; 
 int jisx0208_ucs_table_size ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int,int /*<<< orphan*/ ) ; 

int
mbfl_filt_conv_sjis_mac_wchar(int c, mbfl_convert_filter *filter)
{
	int i, j, n;
	int c1, s, s1, s2, w;

	switch (filter->status) {
	case 0:
		if (c >= 0 && c < 0x80 && c != 0x5c) {	/* latin */
			CK((*filter->output_function)(c, filter->data));
		} else if (c > 0xa0 && c < 0xe0) {	/* kana */
			CK((*filter->output_function)(0xfec0 + c, filter->data));
		} else if (c > 0x80 && c < 0xfd && c != 0xa0) {	/* kanji first char */
			filter->status = 1;
			filter->cache = c;
		} else if (c == 0x5c) {
			CK((*filter->output_function)(0x00a5, filter->data));
		} else if (c == 0x80) {
			CK((*filter->output_function)(0x005c, filter->data));
		} else if (c == 0xa0) {
			CK((*filter->output_function)(0x00a0, filter->data));
		} else if (c == 0xfd) {
			CK((*filter->output_function)(0x00a9, filter->data));
		} else if (c == 0xfe) {
			CK((*filter->output_function)(0x2122, filter->data));
		} else if (c == 0xff) {
			CK((*filter->output_function)(0x2026, filter->data));
			CK((*filter->output_function)(0xf87f, filter->data));
		} else {
			w = c & MBFL_WCSGROUP_MASK;
			w |= MBFL_WCSGROUP_THROUGH;
			CK((*filter->output_function)(w, filter->data));
		}
		break;

	case 1:		/* kanji second char */
		filter->status = 0;
		c1 = filter->cache;
		if (c >= 0x40 && c <= 0xfc && c != 0x7f) {
			w = 0;
			SJIS_DECODE(c1, c, s1, s2);
			s = (s1 - 0x21)*94 + s2 - 0x21;
			if (s <= 0x89) {
				if (s == 0x1c) {
					w = 0x2014;		    /* EM DASH */
				} else if (s == 0x1f) {
					w = 0xff3c;			/* FULLWIDTH REVERSE SOLIDUS */
				} else if (s == 0x20) {
					w = 0x301c;			/* FULLWIDTH TILDE */
				} else if (s == 0x21) {
					w = 0x2016;			/* PARALLEL TO */
				} else if (s == 0x3c) {
					w = 0x2212;			/* FULLWIDTH HYPHEN-MINUS */
				} else if (s == 0x50) {
					w = 0x00a2;			/* FULLWIDTH CENT SIGN */
				} else if (s == 0x51) {
					w = 0x00a3;			/* FULLWIDTH POUND SIGN */
				} else if (s == 0x89) {
					w = 0x00ac;			/* FULLWIDTH NOT SIGN */
				}
			}

			/* apple gaiji area 0x8540 - 0x886d */
			if (w == 0) {
				for (i=0; i<7; i++) {
					if (s >= code_tbl[i][0] && s <= code_tbl[i][1]) {
						w = s - code_tbl[i][0] + code_tbl[i][2];
						break;
					}
				}
			}

			if (w == 0) {

				for (i=0; i<code_tbl_m_len; i++) {
					if (s == code_tbl_m[i][0]) {
						if (code_tbl_m[i][1] == 0xf860) {
							n = 4;
						} else if (code_tbl_m[i][1] == 0xf861) {
							n = 5;
						} else {
							n = 6;
						}
						for (j=1; j<n-1; j++) {
							CK((*filter->output_function)(code_tbl_m[i][j], filter->data));
						}
						w = code_tbl_m[i][n-1];
						break;
					}
				}
			}

			if (w == 0) {
				for (i=0; i<8; i++) {
					if (s >= code_ofst_tbl[i][0] && s <= code_ofst_tbl[i][1]) {
						w = code_map[i][s - code_ofst_tbl[i][0]];
						s2 = 0;
						if (s >= 0x043e && s <= 0x0441) {
							s2 = 0xf87a;
						} else if (s == 0x03b1 || s == 0x03b7) {
							s2 = 0xf87f;
						} else if (s == 0x04b8 || s == 0x04b9 || s == 0x04c4) {
							s2 = 0x20dd;
						} else if (s == 0x1ed9 || s == 0x1eda || s == 0x1ee8 || s == 0x1ef3 ||
								   (s >= 0x1ef5 && s <= 0x1efb) || s == 0x1f05 || s == 0x1f06 ||
								   s == 0x1f18 || (s >= 0x1ff2 && s <= 0x20a5)) {
							s2 = 0xf87e;
						}
						if (s2 > 0) {
							CK((*filter->output_function)(w, filter->data));
							w = s2;
						}
						break;
					}
				}
			}

			if (w == 0 && s >= 0 && s < jisx0208_ucs_table_size) {	/* X 0208 */
				w = jisx0208_ucs_table[s];
			}

			if (w <= 0) {
				w = (s1 << 8) | s2;
				w &= MBFL_WCSPLANE_MASK;
				w |= MBFL_WCSPLANE_WINCP932;
			}
			CK((*filter->output_function)(w, filter->data));
		} else if ((c >= 0 && c < 0x21) || c == 0x7f) {		/* CTLs */
			CK((*filter->output_function)(c, filter->data));
		} else {
			w = (c1 << 8) | c;
			w &= MBFL_WCSGROUP_MASK;
			w |= MBFL_WCSGROUP_THROUGH;
			CK((*filter->output_function)(w, filter->data));
		}
		break;

	default:
		filter->status = 0;
		break;
	}

	return c;
}