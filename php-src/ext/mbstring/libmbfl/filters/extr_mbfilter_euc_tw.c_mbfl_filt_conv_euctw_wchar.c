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
 int MBFL_WCSPLANE_CNS11643 ; 
 int MBFL_WCSPLANE_MASK ; 
 int* cns11643_14_ucs_table ; 
 int cns11643_14_ucs_table_size ; 
 int* cns11643_1_ucs_table ; 
 int cns11643_1_ucs_table_size ; 
 int* cns11643_2_ucs_table ; 
 int cns11643_2_ucs_table_size ; 
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
mbfl_filt_conv_euctw_wchar(int c, mbfl_convert_filter *filter)
{
	int c1, s, w, plane;

	switch (filter->status) {
	case 0:
		if (c >= 0 && c < 0x80) {	/* latin */
			CK((*filter->output_function)(c, filter->data));
		} else if (c > 0xa0 && c < 0xff) {	/* dbcs first byte */
			filter->status = 1;
			filter->cache = c;
		} else if (c == 0x8e) {	/* mbcs first byte */
			filter->status = 2;
			filter->cache = c;
		} else {
			w = c & MBFL_WCSGROUP_MASK;
			w |= MBFL_WCSGROUP_THROUGH;
			CK((*filter->output_function)(w, filter->data));
		}
		break;

	case 1:		/* mbcs second byte */
		filter->status = 0;
		c1 = filter->cache;
		if (c > 0xa0 && c < 0xff) {
			w = (c1 - 0xa1)*94 + (c - 0xa1);
			if (w >= 0 && w < cns11643_1_ucs_table_size) {
				w = cns11643_1_ucs_table[w];
			} else {
				w = 0;
			}
			if (w <= 0) {
				w = (c1 << 8) | c;
				w &= MBFL_WCSPLANE_MASK;
				w |= MBFL_WCSPLANE_CNS11643;
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

	case 2:	/* got 0x8e,  first char */
		c1 = filter->cache;
		if ((c >= 0 && c < 0x21) || c == 0x7f) {		/* CTLs */
			CK((*filter->output_function)(c, filter->data));
			filter->status = 0;
		} else if (c > 0xa0 && c < 0xaf) {
			filter->status = 3;
			filter->cache = c - 0xa1;
		} else {
			w = (c1 << 8) | c;
			w &= MBFL_WCSGROUP_MASK;
			w |= MBFL_WCSGROUP_THROUGH;
			CK((*filter->output_function)(w, filter->data));
		}
		break;

	case 3:	/* got 0x8e,  third char */
		filter->status = 0;
		c1 = filter->cache;
		if ((c >= 0 && c < 0x21) || c == 0x7f) {		/* CTLs */
			CK((*filter->output_function)(c, filter->data));
			filter->status = 0;
		} else if (c > 0xa0 && c < 0xff) {
			filter->status = 4;
			filter->cache = (c1 << 8) + c - 0xa1;
		} else {
			w = (c1 << 8) | c;
			w &= MBFL_WCSGROUP_MASK;
			w |= MBFL_WCSGROUP_THROUGH;
			CK((*filter->output_function)(w, filter->data));
		}
		break;

	case 4:	/* mbcs fourth char */
		filter->status = 0;
		c1 = filter->cache;
		if (c1 >= 0x100 && c1 <= 0xdff && c > 0xa0 && c < 0xff) {
			plane = (c1 & 0xf00) >> 8;
			s = (c1 & 0xff)*94 + c - 0xa1;
			w = 0;
			if (s >= 0) {
				if (plane == 1 && s < cns11643_2_ucs_table_size) {
					w = cns11643_2_ucs_table[s];
				}
				if (plane == 13 && s < cns11643_14_ucs_table_size) {
					w = cns11643_14_ucs_table[s];
				}
			}
			if (w <= 0) {
				w = ((c1 & 0x7f) << 8) | (c & 0x7f);
				w &= MBFL_WCSPLANE_MASK;
				w |= MBFL_WCSPLANE_CNS11643;
			}
			CK((*filter->output_function)(w, filter->data));
		} else if ((c >= 0 && c < 0x21) || c == 0x7f) {		/* CTLs */
			CK((*filter->output_function)(c, filter->data));
		} else {
			w = (c1 << 8) | c | 0x8e0000;
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