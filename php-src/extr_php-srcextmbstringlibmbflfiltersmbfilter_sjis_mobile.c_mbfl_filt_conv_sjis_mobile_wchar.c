#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int status; int cache; int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;TYPE_1__* from; } ;
typedef  TYPE_2__ mbfl_convert_filter ;
struct TYPE_4__ {int /*<<< orphan*/  no_encoding; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int MBFL_WCSGROUP_MASK ; 
 int MBFL_WCSGROUP_THROUGH ; 
 int MBFL_WCSPLANE_MASK ; 
 int MBFL_WCSPLANE_WINCP932 ; 
 int /*<<< orphan*/  SJIS_DECODE (int,int,int,int) ; 
 int* cp932ext1_ucs_table ; 
 int cp932ext1_ucs_table_max ; 
 int cp932ext1_ucs_table_min ; 
 int* cp932ext2_ucs_table ; 
 int cp932ext2_ucs_table_max ; 
 int cp932ext2_ucs_table_min ; 
 int* cp932ext3_ucs_table ; 
 int cp932ext3_ucs_table_max ; 
 int cp932ext3_ucs_table_min ; 
 int* jisx0208_ucs_table ; 
 int jisx0208_ucs_table_size ; 
 int mbfilter_sjis_emoji_docomo2unicode (int,int*) ; 
 int mbfilter_sjis_emoji_kddi2unicode (int,int*) ; 
 int mbfilter_sjis_emoji_sb2unicode (int,int*) ; 
 int /*<<< orphan*/  mbfl_no_encoding_sjis_docomo ; 
 int /*<<< orphan*/  mbfl_no_encoding_sjis_kddi ; 
 int /*<<< orphan*/  mbfl_no_encoding_sjis_sb ; 
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
mbfl_filt_conv_sjis_mobile_wchar(int c, mbfl_convert_filter *filter)
{
	int c1, s, s1 = 0, s2 = 0, w;
	int snd = 0;

retry:
	switch (filter->status) {
	case 0:
		if (c >= 0 && c < 0x80) {	/* latin */
			if (filter->from->no_encoding == mbfl_no_encoding_sjis_sb && c == 0x1b) {
				filter->cache = c;
				filter->status = 2;
			} else {
				CK((*filter->output_function)(c, filter->data));
			}
		} else if (c > 0xa0 && c < 0xe0) {	/* kana */
			CK((*filter->output_function)(0xfec0 + c, filter->data));
		} else if (c > 0x80 && c < 0xfd && c != 0xa0) {	/* kanji first char */
			filter->status = 1;
			filter->cache = c;
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
			if (s <= 137) {
				if (s == 31) {
					w = 0xff3c;			/* FULLWIDTH REVERSE SOLIDUS */
				} else if (s == 32) {
					w = 0xff5e;			/* FULLWIDTH TILDE */
				} else if (s == 33) {
					w = 0x2225;			/* PARALLEL TO */
				} else if (s == 60) {
					w = 0xff0d;			/* FULLWIDTH HYPHEN-MINUS */
				} else if (s == 80) {
					w = 0xffe0;			/* FULLWIDTH CENT SIGN */
				} else if (s == 81) {
					w = 0xffe1;			/* FULLWIDTH POUND SIGN */
				} else if (s == 137) {
					w = 0xffe2;			/* FULLWIDTH NOT SIGN */
				}
			}
			if (w == 0) {
				if (s >= cp932ext1_ucs_table_min && s < cp932ext1_ucs_table_max) {		/* vendor ext1 (13ku) */
					w = cp932ext1_ucs_table[s - cp932ext1_ucs_table_min];
				} else if (s >= 0 && s < jisx0208_ucs_table_size) {		/* X 0208 */
					w = jisx0208_ucs_table[s];
				} else if (s >= cp932ext2_ucs_table_min && s < cp932ext2_ucs_table_max) {		/* vendor ext2 (89ku - 92ku) */
					w = cp932ext2_ucs_table[s - cp932ext2_ucs_table_min];
				} else if (s >= cp932ext3_ucs_table_min && s < cp932ext3_ucs_table_max) {		/* vendor ext3 (115ku - 119ku) */
					w = cp932ext3_ucs_table[s - cp932ext3_ucs_table_min];
				} else if (s >= (94*94) && s < (114*94)) {		/* user (95ku - 114ku) */
					w = s - (94*94) + 0xe000;
				}

 				if (s >= (94*94) && s < 119*94) {
					if (filter->from->no_encoding == mbfl_no_encoding_sjis_docomo) {
						w = mbfilter_sjis_emoji_docomo2unicode(s, &snd);
					} else if (filter->from->no_encoding == mbfl_no_encoding_sjis_kddi) {
						w = mbfilter_sjis_emoji_kddi2unicode(s, &snd);
					} else if (filter->from->no_encoding == mbfl_no_encoding_sjis_sb) {
						w = mbfilter_sjis_emoji_sb2unicode(s, &snd);
					}

					if (w > 0  && snd > 0) {
						CK((*filter->output_function)(snd, filter->data));
					}
				}
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
	/* ESC : Softbank Emoji */
	case 2:
		if (filter->from->no_encoding == mbfl_no_encoding_sjis_sb &&
			c == 0x24) {
				filter->cache = c;
				filter->status++;
		} else {
			filter->cache = 0;
			filter->status = 0;
			CK((*filter->output_function)(0x1b, filter->data));
			goto retry;
		}
		break;

	/* ESC $ : Softbank Emoji */
	case 3:
		if (filter->from->no_encoding == mbfl_no_encoding_sjis_sb &&
			((c >= 0x45 && c <= 0x47) || (c >= 0x4f && c <= 0x51))) {
				filter->cache = c;
				filter->status++;
		} else {
			filter->cache = 0;
			filter->status = 0;
			CK((*filter->output_function)(0x1b, filter->data));
			CK((*filter->output_function)(0x24, filter->data));
			goto retry;
		}
		break;

	/* ESC [GEFOPQ] : Softbank Emoji */
	case 4:
		w = 0;
		if (filter->from->no_encoding == mbfl_no_encoding_sjis_sb) {
			c1 = filter->cache;

			if (c == 0x0f) {
				w = c;
				filter->cache = 0;
				filter->status = 0;
			} else {
				if (c1 == 0x47 && c >= 0x21 && c <= 0x7a) {
					s1 = 0x91; s2 = c;
				} else if (c1 == 0x45 && c >= 0x21 && c <= 0x7a) {
					s1 = 0x8d; s2 = c;
				} else if (c1 == 0x46 && c >= 0x21 && c <= 0x7a) {
					s1 = 0x8e; s2 = c;
				} else if (c1 == 0x4f && c >= 0x21 && c <= 0x6d) {
					s1 = 0x92; s2 = c;
				} else if (c1 == 0x50 && c >= 0x21 && c <= 0x6c) {
					s1 = 0x95; s2 = c;
				} else if (c1 == 0x51 && c >= 0x21 && c <= 0x5e) {
					s1 = 0x96; s2 = c;
				}
				s  = (s1 - 0x21)*94 + s2 - 0x21;
				w = mbfilter_sjis_emoji_sb2unicode(s, &snd);
				if (w > 0) {
					if (snd > 0) {
						CK((*filter->output_function)(snd, filter->data));
					}
					CK((*filter->output_function)(w, filter->data));
				}
			}
		}

		if (w <= 0) {
			c1 = filter->cache;
			filter->cache = 0;
			filter->status = 0;
			CK((*filter->output_function)(0x1b, filter->data));
			CK((*filter->output_function)(0x24, filter->data));
			CK((*filter->output_function)(c1 & 0xff, filter->data));
			goto retry;
		}
		break;

	default:
		filter->status = 0;
		break;
	}

	return c;
}