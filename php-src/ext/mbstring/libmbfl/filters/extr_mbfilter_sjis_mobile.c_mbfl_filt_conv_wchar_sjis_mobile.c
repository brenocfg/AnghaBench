#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int status; scalar_t__ cache; int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;TYPE_1__* to; } ;
typedef  TYPE_2__ mbfl_convert_filter ;
struct TYPE_8__ {scalar_t__ no_encoding; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CODE2JIS (int,int,int,int) ; 
 int MBFL_WCSPLANE_JIS0208 ; 
 int MBFL_WCSPLANE_JIS0212 ; 
 int MBFL_WCSPLANE_MASK ; 
 int MBFL_WCSPLANE_WINCP932 ; 
 int /*<<< orphan*/  SJIS_ENCODE (int,int,int,int) ; 
 int* cp932ext1_ucs_table ; 
 int cp932ext1_ucs_table_max ; 
 int cp932ext1_ucs_table_min ; 
 int* cp932ext2_ucs_table ; 
 int cp932ext2_ucs_table_max ; 
 int cp932ext2_ucs_table_min ; 
 int* cp932ext3_ucs_table ; 
 int cp932ext3_ucs_table_max ; 
 int cp932ext3_ucs_table_min ; 
 scalar_t__ mbfilter_unicode2sjis_emoji_docomo (int,int*,TYPE_2__*) ; 
 scalar_t__ mbfilter_unicode2sjis_emoji_kddi (int,int*,TYPE_2__*) ; 
 scalar_t__ mbfilter_unicode2sjis_emoji_sb (int,int*,TYPE_2__*) ; 
 int /*<<< orphan*/  mbfl_filt_conv_illegal_output (int,TYPE_2__*) ; 
 scalar_t__ mbfl_no_encoding_sjis_docomo ; 
 scalar_t__ mbfl_no_encoding_sjis_kddi ; 
 scalar_t__ mbfl_no_encoding_sjis_sb ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
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
mbfl_filt_conv_wchar_sjis_mobile(int c, mbfl_convert_filter *filter)
{
	int c1, c2, s1, s2;

	s1 = 0;
	s2 = 0;
	if (c >= ucs_a1_jis_table_min && c < ucs_a1_jis_table_max) {
		s1 = ucs_a1_jis_table[c - ucs_a1_jis_table_min];
	} else if (c >= ucs_a2_jis_table_min && c < ucs_a2_jis_table_max) {
		s1 = ucs_a2_jis_table[c - ucs_a2_jis_table_min];
	} else if (c >= ucs_i_jis_table_min && c < ucs_i_jis_table_max) {
		s1 = ucs_i_jis_table[c - ucs_i_jis_table_min];
	} else if (c >= ucs_r_jis_table_min && c < ucs_r_jis_table_max) {
		s1 = ucs_r_jis_table[c - ucs_r_jis_table_min];
	} else if (c >= 0xe000 && c < (0xe000 + 20*94)) {	/* user  (95ku - 114ku) */
		s1 = c - 0xe000;
		c1 = s1/94 + 0x7f;
		c2 = s1%94 + 0x21;
		s1 = (c1 << 8) | c2;
		s2 = 1;
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
		} else if (c == 0xa5) {		/* YEN SIGN */
			s1 = 0x216f;	/* FULLWIDTH YEN SIGN */
		} else if (c == 0x203e) {	/* OVER LINE */
			s1 = 0x2131;	/* FULLWIDTH MACRON */
		} else if (c == 0xff3c) {	/* FULLWIDTH REVERSE SOLIDUS */
			s1 = 0x2140;
		} else if (c == 0xff5e) {	/* FULLWIDTH TILDE */
			s1 = 0x2141;
		} else if (c == 0x2225) {	/* PARALLEL TO */
			s1 = 0x2142;
		} else if (c == 0xff0d) {	/* FULLWIDTH HYPHEN-MINUS */
			s1 = 0x215d;
		} else if (c == 0xffe0) {	/* FULLWIDTH CENT SIGN */
			s1 = 0x2171;
		} else if (c == 0xffe1) {	/* FULLWIDTH POUND SIGN */
			s1 = 0x2172;
		} else if (c == 0xffe2) {	/* FULLWIDTH NOT SIGN */
			s1 = 0x224c;
		}
	}

	if ((s1 <= 0) || (s1 >= 0x8080 && s2 == 0)) {	/* not found or X 0212 */
		s1 = -1;
		c1 = 0;
		c2 = cp932ext1_ucs_table_max - cp932ext1_ucs_table_min;
		while (c1 < c2) {		/* CP932 vendor ext1 (13ku) */
			if (c == cp932ext1_ucs_table[c1]) {
				s1 = ((c1/94 + 0x2d) << 8) + (c1%94 + 0x21);
				break;
			}
			c1++;
		}
		if (s1 <= 0) {
			c1 = 0;
			c2 = cp932ext2_ucs_table_max - cp932ext2_ucs_table_min;
			while (c1 < c2) {		/* CP932 vendor ext2 (115ku - 119ku) */
				if (c == cp932ext2_ucs_table[c1]) {
					s1 = ((c1/94 + 0x93) << 8) + (c1%94 + 0x21);
					break;
				}
				c1++;
			}
		}

		if (s1 <= 0) {
			c1 = 0;
			c2 = cp932ext3_ucs_table_max - cp932ext3_ucs_table_min;
			while (c1 < c2) {		/* CP932 vendor ext3 (115ku - 119ku) */
				if (c == cp932ext3_ucs_table[c1]) {
					s1 = ((c1/94 + 0x93) << 8) + (c1%94 + 0x21);
					break;
				}
				c1++;
			}
		}
		if (c == 0) {
			s1 = 0;
		} else if (s1 <= 0) {
			s1 = -1;
		}
	}

 	if ((filter->to->no_encoding == mbfl_no_encoding_sjis_docomo &&
		 mbfilter_unicode2sjis_emoji_docomo(c, &s1, filter) > 0) ||
		(filter->to->no_encoding == mbfl_no_encoding_sjis_kddi &&
		 mbfilter_unicode2sjis_emoji_kddi(c, &s1, filter) > 0) ||
		(filter->to->no_encoding == mbfl_no_encoding_sjis_sb &&
		 mbfilter_unicode2sjis_emoji_sb(c, &s1, filter) > 0 )) {
		CODE2JIS(c1,c2,s1,s2);
 	}

	if (filter->status == 1 && filter->cache > 0) {
		return c;
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

	return c;
}