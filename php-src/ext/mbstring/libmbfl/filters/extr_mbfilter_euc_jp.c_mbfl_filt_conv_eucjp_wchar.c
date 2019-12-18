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
 int* jisx0208_ucs_table ; 
 int jisx0208_ucs_table_size ; 
 int* jisx0212_ucs_table ; 
 int jisx0212_ucs_table_size ; 
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

int
mbfl_filt_conv_eucjp_wchar(int c, mbfl_convert_filter *filter)
{
	int c1, s, w;

	switch (filter->status) {
	case 0:
		if (c >= 0 && c < 0x80) {	/* latin */
			CK((*filter->output_function)(c, filter->data));
		} else if (c > 0xa0 && c < 0xff) {	/* X 0208 first char */
			filter->status = 1;
			filter->cache = c;
		} else if (c == 0x8e) {	/* kana first char */
			filter->status = 2;
		} else if (c == 0x8f) {	/* X 0212 first char */
			filter->status = 3;
		} else {
			w = c & MBFL_WCSGROUP_MASK;
			w |= MBFL_WCSGROUP_THROUGH;
			CK((*filter->output_function)(w, filter->data));
		}
		break;

	case 1:	/* got first half */
		filter->status = 0;
		c1 = filter->cache;
		if (c > 0xa0 && c < 0xff) {
			s = (c1 - 0xa1)*94 + c - 0xa1;
			if (s >= 0 && s < jisx0208_ucs_table_size) {
				w = jisx0208_ucs_table[s];
			} else {
				w = 0;
			}
			if (w <= 0) {
				w = ((c1 & 0x7f) << 8) | (c & 0x7f);
				w &= MBFL_WCSPLANE_MASK;
				w |= MBFL_WCSPLANE_JIS0208;
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

	case 2:	/* got 0x8e */
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

	case 3:	/* got 0x8f,  X 0212 first char */
		if ((c >= 0 && c < 0x21) || c == 0x7f) {		/* CTLs */
			CK((*filter->output_function)(c, filter->data));
			filter->status = 0;
		} else {
			filter->status++;
			filter->cache = c;
		}
		break;
	case 4:	/* got 0x8f,  X 0212 second char */
		filter->status = 0;
		c1 = filter->cache;
		if (c1 > 0xa0 && c1 < 0xff && c > 0xa0 && c < 0xff) {
			s = (c1 - 0xa1)*94 + c - 0xa1;
			if (s >= 0 && s < jisx0212_ucs_table_size) {
				w = jisx0212_ucs_table[s];
			} else {
				w = 0;
			}
			if (w <= 0) {
				w = ((c1 & 0x7f) << 8) | (c & 0x7f);
				w &= MBFL_WCSPLANE_MASK;
				w |= MBFL_WCSPLANE_JIS0212;
			}
			CK((*filter->output_function)(w, filter->data));
		} else if ((c >= 0 && c < 0x21) || c == 0x7f) {		/* CTLs */
			CK((*filter->output_function)(c, filter->data));
		} else {
			w = (c1 << 8) | c | 0x8f0000;
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