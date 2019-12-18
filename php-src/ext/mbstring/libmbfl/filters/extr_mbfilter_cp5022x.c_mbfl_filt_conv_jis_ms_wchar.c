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
 int MBFL_WCSPLANE_JIS0208 ; 
 int MBFL_WCSPLANE_JIS0212 ; 
 int MBFL_WCSPLANE_MASK ; 
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
 int* jisx0212_ucs_table ; 
 int jisx0212_ucs_table_size ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int,int /*<<< orphan*/ ) ; 

int
mbfl_filt_conv_jis_ms_wchar(int c, mbfl_convert_filter *filter)
{
	int c1, s, w;

retry:
	switch (filter->status & 0xf) {
/*	case 0x00:	 ASCII */
/*	case 0x10:	 X 0201 latin */
/*	case 0x20:	 X 0201 kana */
/*	case 0x80:	 X 0208 */
/*	case 0x90:	 X 0212 */
	case 0:
		if (c == 0x1b) {
			filter->status += 2;
		} else if (c == 0x0e) {		/* "kana in" */
			filter->status = 0x20;
		} else if (c == 0x0f) {		/* "kana out" */
			filter->status = 0;
		} else if (filter->status == 0x10 && c == 0x5c) {	/* YEN SIGN */
			CK((*filter->output_function)(0xa5, filter->data));
		} else if (filter->status == 0x10 && c == 0x7e) {	/* OVER LINE */
			CK((*filter->output_function)(0x203e, filter->data));
		} else if (filter->status == 0x20 && c > 0x20 && c < 0x60) {		/* kana */
			CK((*filter->output_function)(0xff40 + c, filter->data));
		} else if ((filter->status == 0x80 || filter->status == 0x90) && c > 0x20 && c < 0x93) {		/* kanji first char */
			filter->cache = c;
			filter->status += 1;
		} else if (c >= 0 && c < 0x80) {		/* latin, CTLs */
			CK((*filter->output_function)(c, filter->data));
		} else if (c > 0xa0 && c < 0xe0) {	/* GR kana */
			CK((*filter->output_function)(0xfec0 + c, filter->data));
		} else {
			w = c & MBFL_WCSGROUP_MASK;
			w |= MBFL_WCSGROUP_THROUGH;
			CK((*filter->output_function)(w, filter->data));
		}
		break;

/*	case 0x81:	 X 0208 second char */
/*	case 0x91:	 X 0212 second char */
	case 1:
		filter->status &= ~0xf;
		c1 = filter->cache;
		if (c > 0x20 && c < 0x7f) {
			s = (c1 - 0x21)*94 + c - 0x21;
			if (filter->status == 0x80) {
				if (s >= 0 && s < jisx0208_ucs_table_size) {
					w = jisx0208_ucs_table[s];
				} else if (s >= cp932ext1_ucs_table_min && s < cp932ext1_ucs_table_max) {
					w = cp932ext1_ucs_table[s - cp932ext1_ucs_table_min];
				} else if (s >= cp932ext2_ucs_table_min && s < cp932ext2_ucs_table_max) {
					w = cp932ext2_ucs_table[s - cp932ext2_ucs_table_min];
				} else if (s >= cp932ext3_ucs_table_min && s < cp932ext3_ucs_table_max) {
					w = cp932ext3_ucs_table[s - cp932ext3_ucs_table_min];
				} else if (s >= 94 * 94 && s < 114 * 94) {
					/* user-defined => PUA (Microsoft extended) */
					w = s - 94*94 + 0xe000;
				} else {
					w = 0;
				}
				if (w <= 0) {
					w = (c1 << 8) | c;
					w &= MBFL_WCSPLANE_MASK;
					w |= MBFL_WCSPLANE_JIS0208;
				}
			} else {
				if (s >= 0 && s < jisx0212_ucs_table_size) {
					w = jisx0212_ucs_table[s];
				} else {
					w = 0;
				}
				if (w <= 0) {
					w = (c1 << 8) | c;
					w &= MBFL_WCSPLANE_MASK;
					w |= MBFL_WCSPLANE_JIS0212;
				}
			}
			CK((*filter->output_function)(w, filter->data));
		} else if (c == 0x1b) {
			filter->status += 2;
		} else if ((c >= 0 && c < 0x21) || c == 0x7f) {		/* CTLs */
			CK((*filter->output_function)(c, filter->data));
		} else {
			w = (c1 << 8) | c;
			w &= MBFL_WCSGROUP_MASK;
			w |= MBFL_WCSGROUP_THROUGH;
			CK((*filter->output_function)(w, filter->data));
		}
		break;

	/* ESC */
/*	case 0x02:	*/
/*	case 0x12:	*/
/*	case 0x22:	*/
/*	case 0x82:	*/
/*	case 0x92:	*/
	case 2:
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

	/* ESC $ */
/*	case 0x03:	*/
/*	case 0x13:	*/
/*	case 0x23:	*/
/*	case 0x83:	*/
/*	case 0x93:	*/
	case 3:
		if (c == 0x40 || c == 0x42) {	/* '@' or 'B' */
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

	/* ESC $ ( */
/*	case 0x04:	*/
/*	case 0x14:	*/
/*	case 0x24:	*/
/*	case 0x84:	*/
/*	case 0x94:	*/
	case 4:
		if (c == 0x40 || c == 0x42) {	/* '@' or 'B' */
			filter->status = 0x80;
		} else if (c == 0x44) {			/* 'D' */
			filter->status = 0x90;
		} else {
			filter->status &= ~0xf;
			CK((*filter->output_function)(0x1b, filter->data));
			CK((*filter->output_function)(0x24, filter->data));
			CK((*filter->output_function)(0x28, filter->data));
			goto retry;
		}
		break;

	/* ESC ( */
/*	case 0x05:	*/
/*	case 0x15:	*/
/*	case 0x25:	*/
/*	case 0x85:	*/
/*	case 0x95:	*/
	case 5:
		if (c == 0x42 || c == 0x48) {		/* 'B' or 'H' */
			filter->status = 0;
		} else if (c == 0x4a) {		/* 'J' */
			filter->status = 0x10;
		} else if (c == 0x49) {		/* 'I' */
			filter->status = 0x20;
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