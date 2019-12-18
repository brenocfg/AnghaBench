#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int status; int cache; int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;TYPE_1__* to; } ;
typedef  TYPE_2__ mbfl_convert_filter ;
struct TYPE_5__ {scalar_t__ no_encoding; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int MBFL_WCSPLANE_JIS0213 ; 
 int MBFL_WCSPLANE_MASK ; 
 int /*<<< orphan*/  SJIS_ENCODE (int,int,int,int) ; 
 int* jisx0213_p2_ofst ; 
 int jisx0213_p2_ofst_len ; 
 int* jisx0213_u2_fb_tbl ; 
 int* jisx0213_u2_key ; 
 int* jisx0213_u2_tbl ; 
 int jisx0213_u2_tbl_len ; 
 int /*<<< orphan*/  jisx0213_u5_jis_key ; 
 int* jisx0213_u5_jis_tbl ; 
 int /*<<< orphan*/  jisx0213_u5_tbl_len ; 
 int jisx0213_u5_tbl_max ; 
 int jisx0213_u5_tbl_min ; 
 int mbfl_bisec_srch (int,int*,int /*<<< orphan*/ ) ; 
 int mbfl_bisec_srch2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbfl_filt_conv_illegal_output (int,TYPE_2__*) ; 
 scalar_t__ mbfl_no_encoding_2022jp_2004 ; 
 scalar_t__ mbfl_no_encoding_eucjp2004 ; 
 scalar_t__ mbfl_no_encoding_sjis2004 ; 
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
 int /*<<< orphan*/  stub19 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub20 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub21 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub22 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub23 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub24 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub25 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int,int /*<<< orphan*/ ) ; 
 int ucs_c1_jisx0213_max ; 
 int ucs_c1_jisx0213_min ; 
 int* ucs_c1_jisx0213_ofst ; 
 int* ucs_c1_jisx0213_tbl ; 
 int /*<<< orphan*/  ucs_c1_jisx0213_tbl_len ; 
 int /*<<< orphan*/  ucs_r2b_jisx0213_cmap_key ; 
 int /*<<< orphan*/  ucs_r2b_jisx0213_cmap_len ; 
 int* ucs_r2b_jisx0213_cmap_val ; 
 int** uni2jis_tbl ; 
 int uni2jis_tbl_len ; 
 int** uni2jis_tbl_range ; 

int
mbfl_filt_conv_wchar_jis2004(int c, mbfl_convert_filter *filter) {
	int k;
	int c1, c2, s1 = 0, s2;

retry:

	/* check for 1st char of combining characters */
	if ((filter->status & 0xf)== 0 && (
			c == 0x00E6 ||
			(c >= 0x0254 && c <= 0x02E9) ||
			(c >= 0x304B && c <= 0x3053) ||
			(c >= 0x30AB && c <= 0x30C8) ||
			c == 0x31F7)) {
		for (k=0;k<jisx0213_u2_tbl_len;k++) {
			if (c == jisx0213_u2_tbl[2*k]) {
				filter->status++;
				filter->cache = k;
				return c;
			}
		}
	}

	/* check for 2nd char of combining characters */
	if ((filter->status & 0xf) == 1 &&
		filter->cache >= 0 && filter->cache <= jisx0213_u2_tbl_len) {
		k = filter->cache;
		filter->status &= ~0xf;
		filter->cache = 0;

		c1 = jisx0213_u2_tbl[2*k];
		if ((c1 == 0x0254 || c1 == 0x028C || c1 == 0x0259 || c1 == 0x025A)
			&& c == 0x0301) {
			k++;
		}
		if (c == jisx0213_u2_tbl[2*k+1]) {
			s1 = jisx0213_u2_key[k];
		} else { /* fallback */
			s1 = jisx0213_u2_fb_tbl[k];

			if (filter->to->no_encoding == mbfl_no_encoding_sjis2004) {
				c1 = (s1 >> 8) & 0xff;
				c2 = s1 & 0xff;
				SJIS_ENCODE(c1, c2, s1, s2);
			} else if (filter->to->no_encoding == mbfl_no_encoding_eucjp2004) {
				s2 = (s1 & 0xff) + 0x80;
				s1 = ((s1 >> 8) & 0xff) + 0x80;
			} else {
				if (filter->status != 0x200) {
					CK((*filter->output_function)(0x1b, filter->data));
					CK((*filter->output_function)(0x24, filter->data));
					CK((*filter->output_function)(0x28, filter->data));
					CK((*filter->output_function)(0x51, filter->data));
				}
				filter->status = 0x200;

				s2 = s1 & 0x7f;
				s1 = (s1 >> 8) & 0x7f;
			}

			CK((*filter->output_function)(s1, filter->data));
			CK((*filter->output_function)(s2, filter->data));
			goto retry;
		}
	}

	/* check for major japanese chars: U+4E00 - U+9FFF */
	if (s1 <= 0) {
		for (k=0; k < uni2jis_tbl_len ;k++) {
			if (c >= uni2jis_tbl_range[k][0] && c <= uni2jis_tbl_range[k][1]) {
				s1 = uni2jis_tbl[k][c-uni2jis_tbl_range[k][0]];
				break;
			}
		}
	}

	/* check for japanese chars in compressed mapping area: U+1E00 - U+4DBF */
	if (s1 <= 0 && c >= ucs_c1_jisx0213_min && c <= ucs_c1_jisx0213_max) {
		k = mbfl_bisec_srch(c, ucs_c1_jisx0213_tbl, ucs_c1_jisx0213_tbl_len);
		if (k >= 0) {
			s1 = ucs_c1_jisx0213_ofst[k] + c - ucs_c1_jisx0213_tbl[2*k];
		}
	}

	/* check for japanese chars in CJK Unified Ideographs ext.B (U+2XXXX) */
	if (s1 <= 0 && c >= jisx0213_u5_tbl_min && c <= jisx0213_u5_tbl_max) {
		k = mbfl_bisec_srch2(c - 0x20000, jisx0213_u5_jis_key, jisx0213_u5_tbl_len);
		if (k >= 0) {
			s1 = jisx0213_u5_jis_tbl[k];
		}
	}

	if (s1 <= 0) {
		/* CJK Compatibility Forms: U+FE30 - U+FE4F */
		if (c == 0xfe45) {
			s1 = 0x233e;
		} else if (c == 0xfe46) {
			s1 = 0x233d;
		} else if (c >= 0xf91d && c <= 0xf9dc) {
			/* CJK Compatibility Ideographs: U+F900 - U+F92A */
			k = mbfl_bisec_srch2(c, ucs_r2b_jisx0213_cmap_key, ucs_r2b_jisx0213_cmap_len);
			if (k >= 0) {
				s1 = ucs_r2b_jisx0213_cmap_val[k];
			}
		}
	}

	if (s1 <= 0) {
		c1 = c & ~MBFL_WCSPLANE_MASK;
		if (c1 == MBFL_WCSPLANE_JIS0213) {
			s1 = c & MBFL_WCSPLANE_MASK;
		}
		if (c == 0) {
			s1 = 0;
		} else if (s1 <= 0) {
			s1 = -1;
		}
	} else if (s1 >= 0x9980) {
		s1 = -1;
	}

	if (s1 >= 0) {
		if (s1 < 0x80) { /* ASCII */
			if (filter->to->no_encoding == mbfl_no_encoding_2022jp_2004 &&
				(filter->status & 0xff00) != 0) {
				CK((*filter->output_function)(0x1b, filter->data));		/* ESC */
				CK((*filter->output_function)(0x28, filter->data));		/* '(' */
				CK((*filter->output_function)(0x42, filter->data));		/* 'B' */
			}
			filter->status = 0;
			CK((*filter->output_function)(s1, filter->data));
		} else if (s1 < 0x100) { /* latin or kana */
			if  (filter->to->no_encoding == mbfl_no_encoding_eucjp2004) {
				CK((*filter->output_function)(0x8e, filter->data));
			}
			CK((*filter->output_function)(s1, filter->data));
		} else if (s1 < 0x7f00) { /* X 0213 plane 1 */
			if (filter->to->no_encoding == mbfl_no_encoding_sjis2004) {
				c1 = (s1 >> 8) & 0xff;
				c2 = s1 & 0xff;
				SJIS_ENCODE(c1, c2, s1, s2);
			} else if  (filter->to->no_encoding == mbfl_no_encoding_eucjp2004) {
				s2 = (s1 & 0xff) + 0x80;
				s1 = ((s1 >> 8) & 0xff) + 0x80;
			} else {
				if ((filter->status & 0xff00) != 0x200) {
					CK((*filter->output_function)(0x1b, filter->data));		/* ESC */
					CK((*filter->output_function)(0x24, filter->data));		/* '$' */
					CK((*filter->output_function)(0x28, filter->data));		/* '(' */
					CK((*filter->output_function)(0x51, filter->data));		/* 'Q' */
				}
				filter->status = 0x200;
				s2 = s1 & 0xff;
				s1 = (s1 >> 8) & 0xff;
			}
			CK((*filter->output_function)(s1, filter->data));
			CK((*filter->output_function)(s2, filter->data));
		} else { /* X 0213 plane 2 */
			if (filter->to->no_encoding == mbfl_no_encoding_sjis2004) {
				c1 = (s1 >> 8) & 0xff;
				c2 = s1 & 0xff;
				SJIS_ENCODE(c1, c2, s1, s2);
			} else {
				s2 = s1 & 0xff;
				k = ((s1 >> 8) & 0xff) - 0x7f;
				if (k >= 0 && k < jisx0213_p2_ofst_len) {
					s1  = jisx0213_p2_ofst[k] - 1 + 0x21;
				}
				if  (filter->to->no_encoding == mbfl_no_encoding_eucjp2004) {
					s2 |= 0x80;
					s1 |= 0x80;
					CK((*filter->output_function)(0x8f, filter->data));
				} else {
					if ((filter->status & 0xff00) != 0x200) {
						CK((*filter->output_function)(0x1b, filter->data));		/* ESC */
						CK((*filter->output_function)(0x24, filter->data));		/* '$' */
						CK((*filter->output_function)(0x28, filter->data));		/* '(' */
						CK((*filter->output_function)(0x50, filter->data));		/* 'P' */
					}
					filter->status = 0x200;
				}
			}

			CK((*filter->output_function)(s1, filter->data));
			CK((*filter->output_function)(s2, filter->data));
		}
	} else {
		CK(mbfl_filt_conv_illegal_output(c, filter));
	}

	return c;
}