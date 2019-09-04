#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int status; int cache; int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;TYPE_2__* to; TYPE_1__* from; } ;
typedef  TYPE_3__ mbfl_convert_filter ;
struct TYPE_6__ {int /*<<< orphan*/  no_encoding; } ;
struct TYPE_5__ {int /*<<< orphan*/  no_encoding; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int MBFL_WCSGROUP_MASK ; 
 int MBFL_WCSGROUP_THROUGH ; 
 int MBFL_WCSPLANE_JIS0208 ; 
 int MBFL_WCSPLANE_JIS0213 ; 
 int MBFL_WCSPLANE_MASK ; 
 int /*<<< orphan*/  SJIS_DECODE (int,int,int,int) ; 
 int* jisx0208_ucs_table ; 
 int jisx0208_ucs_table_size ; 
 int /*<<< orphan*/  jisx0213_jis_u5_key ; 
 int /*<<< orphan*/ * jisx0213_jis_u5_tbl ; 
 int /*<<< orphan*/ * jisx0213_p2_ofst ; 
 int jisx0213_p2_ofst_len ; 
 int /*<<< orphan*/  jisx0213_u2_key ; 
 int* jisx0213_u2_tbl ; 
 int /*<<< orphan*/  jisx0213_u2_tbl_len ; 
 int /*<<< orphan*/  jisx0213_u5_tbl_len ; 
 int* jisx0213_ucs_table ; 
 int jisx0213_ucs_table_size ; 
 int mbfl_bisec_srch2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbfl_no_encoding_eucjp2004 ; 
 int /*<<< orphan*/  mbfl_no_encoding_sjis2004 ; 
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
 int /*<<< orphan*/  stub26 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub27 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub28 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub29 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub30 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int,int /*<<< orphan*/ ) ; 

int
mbfl_filt_conv_jis2004_wchar(int c, mbfl_convert_filter *filter)
{
	int k;
	int c1, c2, s, s1 = 0, s2 = 0, w = 0, w1;

retry:
	switch (filter->status & 0xf) {
	case 0:
		if (c >= 0 && c < 0x80) {	/* latin */
			if (filter->from->no_encoding == mbfl_no_encoding_eucjp2004) {
				CK((*filter->output_function)(c, filter->data));
			} else if (filter->from->no_encoding == mbfl_no_encoding_sjis2004) {
				if (c == 0x5c) {
					CK((*filter->output_function)(0x00a5, filter->data));
				} else if (c == 0x7e) {
					CK((*filter->output_function)(0x203e, filter->data));
				} else {
					CK((*filter->output_function)(c, filter->data));
				}
			} else { /* ISO-2022-JP-2004 */
				if (c == 0x1b) {
					filter->status += 6;
				} else if ((filter->status == 0x80 || filter->status == 0x90 || filter->status == 0xa0)
				   && c > 0x20 && c < 0x7f) {		/* kanji first char */
					filter->cache = c;
					if (filter->status == 0x90) {
						filter->status += 1; /* JIS X 0213 plane 1 */
					} else if (filter->status == 0xa0) {
						filter->status += 4; /* JIS X 0213 plane 2 */
					} else {
						filter->status += 5; /* JIS X 0208 */
					}
				} else {
					CK((*filter->output_function)(c, filter->data));
				}
			}
		} else {
			if (filter->from->no_encoding == mbfl_no_encoding_eucjp2004) {
				if (c > 0xa0 && c < 0xff) {	/* X 0213 plane 1 first char */
					filter->status = 1;
					filter->cache = c;
				} else if (c == 0x8e) {	/* kana first char */
					filter->status = 2;
				} else if (c == 0x8f) {	/* X 0213 plane 2 first char */
					filter->status = 3;
				} else {
					w = c & MBFL_WCSGROUP_MASK;
					w |= MBFL_WCSGROUP_THROUGH;
					CK((*filter->output_function)(w, filter->data));
				}
			} else if (filter->from->no_encoding == mbfl_no_encoding_sjis2004) {
				if (c > 0xa0 && c < 0xe0) {	/* kana */
					CK((*filter->output_function)(0xfec0 + c, filter->data));
				} else if (c > 0x80 && c < 0xfd && c != 0xa0) {	/* kanji first char */
					filter->status = 1;
					filter->cache = c;
				} else {
					w = c & MBFL_WCSGROUP_MASK;
					w |= MBFL_WCSGROUP_THROUGH;
					CK((*filter->output_function)(w, filter->data));
				}
			} else {
				w = c & MBFL_WCSGROUP_MASK;
				w |= MBFL_WCSGROUP_THROUGH;
				CK((*filter->output_function)(w, filter->data));
			}
		}
		break;

	case 1:		/* kanji second char */
		filter->status &= ~0xf;
		c1 = filter->cache;

		if (filter->from->no_encoding == mbfl_no_encoding_eucjp2004) {
			if (c > 0xa0 && c < 0xff) {
				s1 = c1 - 0x80;
				s2 = c - 0x80;
			}
		} else if (filter->from->no_encoding == mbfl_no_encoding_sjis2004) {
			if (c >= 0x40 && c <= 0xfc && c != 0x7f) {
				SJIS_DECODE(c1, c, s1, s2);
			}
		} else {
			s1 = c1;
			s2 = c;
		}
		w1 = (s1 << 8) | s2;

		if (w1 >= 0x2121) {
			/* conversion for combining characters */
			if ((w1 >= 0x2477 && w1 <= 0x2479) || (w1 >= 0x2479 && w1 <= 0x247B) ||
				(w1 >= 0x2577 && w1 <= 0x257E) || w1 == 0x2678 || w1 == 0x2B44 ||
				(w1 >= 0x2B48 && w1 <= 0x2B4F) || (w1 >= 0x2B65 && w1 <= 0x2B66)) {
				k = mbfl_bisec_srch2(w1, jisx0213_u2_key, jisx0213_u2_tbl_len);
				if (k >= 0) {
					w = jisx0213_u2_tbl[2*k];
					CK((*filter->output_function)(w, filter->data));
					w = jisx0213_u2_tbl[2*k+1];
				}
			}

			/* conversion for BMP  */
			if (w <= 0) {
				w1 = (s1 - 0x21)*94 + s2 - 0x21;
				if (w1 >= 0 && w1 < jisx0213_ucs_table_size) {
					w = jisx0213_ucs_table[w1];
				}
			}

			/* conversion for CJK Unified Ideographs ext.B (U+2XXXX) */
			if (w <= 0) {
				w1 = (s1 << 8) | s2;
				k = mbfl_bisec_srch2(w1, jisx0213_jis_u5_key, jisx0213_u5_tbl_len);
				if (k >= 0) {
					w = jisx0213_jis_u5_tbl[k] + 0x20000;
				}
			}

			if (w <= 0) {
				if (s1 < 0x7f && s2 < 0x7f) {
					w = (s1 << 8) | s2;
					w &= MBFL_WCSPLANE_MASK;
					w |= MBFL_WCSPLANE_JIS0213;
				} else {
					w = (c1 << 8) | c;
					w &= MBFL_WCSGROUP_MASK;
					w |= MBFL_WCSGROUP_THROUGH;
				}
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

	case 2:	/* got 0x8e : EUC-JP-2004 kana */
		filter->status = 0;
		if (c > 0xa0 && c < 0xe0) {
			w = 0xfec0 + c;
			CK((*filter->output_function)(w, filter->data));
		} else if ((c >= 0 && c < 0x21) || c == 0x7f) {		/* CTLs */
			CK((*filter->output_function)(c, filter->data));
		} else {
			w = 0x8e00 | c;
			w &= MBFL_WCSGROUP_MASK;
			w |= MBFL_WCSGROUP_THROUGH;
			CK((*filter->output_function)(w, filter->data));
		}
		break;

	case 3:	/* X 0213 plane 2 first char : EUC-JP-2004 (0x8f), ISO-2022-JP-2004 */
		if ((c >= 0 && c < 0x21) || c == 0x7f) {		/* CTLs */
			CK((*filter->output_function)(c, filter->data));
			filter->status = 0;
		} else {
			if (filter->from->no_encoding == mbfl_no_encoding_eucjp2004) {
				s1 = c - 0x80;
			} else {
				s1 = c;
			}
			if (s1 > 0x20 && s1 < 0x80) {
				filter->cache = s1;
				filter->status++;
			} else {
				if (filter->to->no_encoding == mbfl_no_encoding_eucjp2004) {
					w = c | 0x8f00;
					w &= MBFL_WCSGROUP_MASK;
					w |= MBFL_WCSGROUP_THROUGH;
				} else {
					w = c & 0x7f;
					w &= MBFL_WCSPLANE_MASK;
					w |= MBFL_WCSPLANE_JIS0213;
				}
				CK((*filter->output_function)(w, filter->data));
			}
		}
		break;

	case 4:	/* X 0213 plane 2 second char : EUC-JP-2004, ISO-2022-JP-2004 */

		filter->status &= ~0xf;
		c1 = filter->cache;
		if (filter->from->no_encoding == mbfl_no_encoding_eucjp2004) {
			c2 = c - 0x80;
		} else {
			c2 = c;
		}
		s1 = c1 - 0x21;
		s2 = c2 - 0x21;

		if (((s1 >= 0 && s1 <= 4 && s1 != 1) || s1 == 7 || (s1 >= 11 && s1 <= 14) ||
			(s1 >= 77 && s1 < 94)) && s2 >= 0 && s2 < 94) {
			/* calc offset from ku */
			for (k = 0; k < jisx0213_p2_ofst_len; k++) {
				if (s1 == jisx0213_p2_ofst[k]-1) {
					break;
				}
			}
			k = k - (jisx0213_p2_ofst[k]-1);

			/* check for japanese chars in BMP */
			s = (s1 + 94 + k)*94 + s2;
			if (s >= 0 && s < jisx0213_ucs_table_size) {
				w = jisx0213_ucs_table[s];
			} else {
				w = 0;
			}

			/* check for japanese chars in CJK Unified Ideographs ext.B (U+2XXXX) */
			if (w <= 0) {
				w1 = ((c1 + k + 94) << 8) | c2;
				k = mbfl_bisec_srch2(w1, jisx0213_jis_u5_key, jisx0213_u5_tbl_len);
				if (k >= 0) {
					w = jisx0213_jis_u5_tbl[k] + 0x20000;
				}
			}

			if (w <= 0) {
				w = ((c1 & 0x7f) << 8) | (c2 & 0x7f);
				w &= MBFL_WCSPLANE_MASK;
				w |= MBFL_WCSPLANE_JIS0213;
			}

			CK((*filter->output_function)(w, filter->data));
		} else if ((c >= 0 && c < 0x21) || c == 0x7f) {		/* CTLs */
			CK((*filter->output_function)(c, filter->data));
		} else {
			if (filter->to->no_encoding == mbfl_no_encoding_eucjp2004) {
				w = (c1 << 8) | c | 0x8f0000;
				w &= MBFL_WCSGROUP_MASK;
				w |= MBFL_WCSGROUP_THROUGH;
			} else {
				w = ((c1 & 0x7f) << 8) | (c2 & 0x7f);
				w &= MBFL_WCSPLANE_MASK;
				w |= MBFL_WCSPLANE_JIS0213;
			}
			CK((*filter->output_function)(w, filter->data));
		}

		break;

	case 5:	/* X 0208 : ISO-2022-JP-2004 */
		filter->status &= ~0xf;
		c1 = filter->cache;
		if (c > 0x20 && c < 0x7f) {
			s = (c1 - 0x21)*94 + c - 0x21;
			if (s >= 0 && s < jisx0208_ucs_table_size) {
				w = jisx0208_ucs_table[s];
			}
		}
		if (w <= 0) {
			w = (c1 << 8) | c;
			w &= MBFL_WCSPLANE_MASK;
			w |= MBFL_WCSPLANE_JIS0208;
		}
		CK((*filter->output_function)(w, filter->data));
		break;

	/* ESC : ISO-2022-JP-2004 */
/*	case 0x06:	*/
/*	case 0x16:	*/
/*	case 0x26:	*/
/*	case 0x86:	*/
/*	case 0x96:	*/
/*	case 0xa6:	*/
	case 6:
		if (c == 0x24) {		/* '$' */
			filter->status++;
		} else if (c == 0x28) {		/* '(' */
			filter->status += 3;
		} else {
			filter->status &= ~0xf;
			CK((*filter->output_function)(0x1b, filter->data));
			goto retry;
		}
		break;

	/* ESC $ : ISO-2022-JP-2004 */
/*	case 0x07:	*/
/*	case 0x17:	*/
/*	case 0x27:	*/
/*	case 0x87:	*/
/*	case 0x97:	*/
/*	case 0xa7:	*/
	case 7:
		if (c == 0x42) {	/* 'B' -> JIS X 0208-1983 */
			filter->status = 0x80;
		} else if (c == 0x28) {			/* '(' */
			filter->status++;
		} else {
			filter->status &= ~0xf;
			CK((*filter->output_function)(0x1b, filter->data));
			CK((*filter->output_function)(0x24, filter->data));
			goto retry;
		}
		break;

		break;

	/* ESC $ ( : ISO-2022-JP-2004 */
/*	case 0x08:	*/
/*	case 0x18:	*/
/*	case 0x28:	*/
/*	case 0x88:	*/
/*	case 0x98:	*/
/*	case 0xa8:	*/
	case 8:
		if (c == 0x51) {	/* JIS X 0213 plane 1 */
			filter->status = 0x90;
		} else if (c == 0x50) {			/* JIS X 0213 plane 2 */
			filter->status = 0xa0;
		} else {
			filter->status &= ~0xf;
			CK((*filter->output_function)(0x1b, filter->data));
			CK((*filter->output_function)(0x24, filter->data));
			CK((*filter->output_function)(0x28, filter->data));
			goto retry;
		}
		break;

	/* ESC ( : ISO-2022-JP-2004 */
/*	case 0x09:	*/
/*	case 0x19:	*/
/*	case 0x29:	*/
/*	case 0x89:	*/
/*	case 0x99:	*/
	case 9:
		if (c == 0x42) {		/* 'B' : ASCII */
			filter->status = 0;
		} else {
			filter->status &= ~0xf;
			CK((*filter->output_function)(0x1b, filter->data));
			CK((*filter->output_function)(0x28, filter->data));
			goto retry;
		}
		break;

	default:
		filter->status = 0;
		break;
	}

	return c;
}