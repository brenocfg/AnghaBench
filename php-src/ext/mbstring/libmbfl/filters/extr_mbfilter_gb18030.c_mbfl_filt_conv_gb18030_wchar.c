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
 int MBFL_WCSPLANE_GB18030 ; 
 int MBFL_WCSPLANE_MASK ; 
 int* cp936_ucs_table ; 
 int cp936_ucs_table_size ; 
 int mbfl_bisec_srch (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int** mbfl_gb18030_pua_tbl ; 
 int mbfl_gb18030_pua_tbl_max ; 
 int /*<<< orphan*/  mbfl_gb2uni_tbl ; 
 int /*<<< orphan*/  mbfl_gb_uni_max ; 
 int* mbfl_gb_uni_ofst ; 
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
mbfl_filt_conv_gb18030_wchar(int c, mbfl_convert_filter *filter)
{
	int k;
	int c1, c2, c3, w = -1;

	switch (filter->status) {
	case 0:
		if (c >= 0 && c < 0x80) {	/* latin */
			CK((*filter->output_function)(c, filter->data));
		} else if (c == 0x80) {	/* euro sign */
			CK((*filter->output_function)(0x20ac, filter->data));
		} else if (c == 0xff) {
			CK((*filter->output_function)(0x00ff, filter->data));
		} else if (c > 0x80 && c < 0xff) {	/* dbcs/qbcs lead byte */
			filter->status = 1;
			filter->cache = c;
		} else {
			w = c & MBFL_WCSGROUP_MASK;
			w |= MBFL_WCSGROUP_THROUGH;
			CK((*filter->output_function)(w, filter->data));
		}
		break;

	case 1:		/* dbcs/qbcs second byte */
		c1 = filter->cache;
		filter->status = 0;

		if (c1 >= 0x81 && c1 <= 0x84 && c >= 0x30 && c <= 0x39) { /* 4 byte range: Unicode BMP */
			filter->status = 2;
			filter->cache = (c1 << 8) | c;
			return c;
		} else if (c1 >= 0x90 && c1 <= 0xe3 && c >= 0x30 && c <= 0x39) {
			/* 4 byte range: Unicode 16 planes */
			filter->status = 2;
			filter->cache = (c1 << 8) | c;
			return c;
		} else if (((c1 >= 0xaa && c1 <= 0xaf) || (c1 >= 0xf8 && c1 <= 0xfe)) &&
				   (c >= 0xa1 && c <= 0xfe)) { /* UDA part1,2: U+E000-U+E4C5 */
			w = 94*(c1 >= 0xf8 ? c1 - 0xf2 : c1 - 0xaa) + (c - 0xa1) + 0xe000;
			CK((*filter->output_function)(w, filter->data));
		} else if (c1 >= 0xa1 && c1 <= 0xa7 && c >= 0x40 && c < 0xa1 && c != 0x7f) {
			/* UDA part3 : U+E4C6-U+E765*/
			w = 96*(c1 - 0xa1) + c - (c >= 0x80 ? 0x41 : 0x40) + 0xe4c6;
			CK((*filter->output_function)(w, filter->data));
		}

		c2 = (c1 << 8) | c;

		if (w <= 0 &&
			((c2 >= 0xa2ab && c2 <= 0xa9f0 + (0xe80f-0xe801)) ||
			 (c2 >= 0xd7fa && c2 <= 0xd7fa + (0xe814-0xe810)) ||
			 (c2 >= 0xfe50 && c2 <= 0xfe80 + (0xe864-0xe844)))) {
			for (k = 0; k < mbfl_gb18030_pua_tbl_max; k++) {
				if (c2 >= mbfl_gb18030_pua_tbl[k][2] &&
					c2 <= mbfl_gb18030_pua_tbl[k][2] +  mbfl_gb18030_pua_tbl[k][1]
					-  mbfl_gb18030_pua_tbl[k][0]) {
					w = c2 -  mbfl_gb18030_pua_tbl[k][2] + mbfl_gb18030_pua_tbl[k][0];
					CK((*filter->output_function)(w, filter->data));
					break;
				}
			}
		}

		if (w <= 0) {
			if ((c1 >= 0xa1 && c1 <= 0xa9 && c >= 0xa1 && c <= 0xfe) ||
				(c1 >= 0xb0 && c1 <= 0xf7 && c >= 0xa1 && c <= 0xfe) ||
				(c1 >= 0x81 && c1 <= 0xa0 && c >= 0x40 && c <= 0xfe && c != 0x7f) ||
				(c1 >= 0xaa && c1 <= 0xfe && c >= 0x40 && c <= 0xa0 && c != 0x7f) ||
				(c1 >= 0xa8 && c1 <= 0xa9 && c >= 0x40 && c <= 0xa0 && c != 0x7f)) {
				w = (c1 - 0x81)*192 + (c - 0x40);
				if (w >= 0 && w < cp936_ucs_table_size) {
					w = cp936_ucs_table[w];
				} else {
					w = 0;
				}
				if (w <= 0) {
					w = (c1 << 8) | c;
					w &= MBFL_WCSPLANE_MASK;
					w |= MBFL_WCSPLANE_GB18030;
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
		}
		break;
	case 2: /* qbcs third byte */
		c1 = (filter->cache >> 8) & 0xff;
		c2 = filter->cache & 0xff;
		filter->status = 0;
		filter->cache = 0;
		if (((c1 >= 0x81 && c1 <= 0x84) || (c1 >= 0x90 && c1 <= 0xe3)) &&
			c2 >= 0x30 && c2 <= 0x39 && c >= 0x81 && c <= 0xfe) {
			filter->cache = (c1 << 16) | (c2 << 8) | c;
			filter->status = 3;
		} else {
			w = (c1 << 16) | (c2 << 8) | c;
			w &= MBFL_WCSGROUP_MASK;
			w |= MBFL_WCSGROUP_THROUGH;
			CK((*filter->output_function)(w, filter->data));
		}
 		break;

	case 3: /* qbcs fourth byte */
		c1 = (filter->cache >> 16) & 0xff;
		c2 = (filter->cache >> 8) & 0xff;
		c3 = filter->cache & 0xff;
		filter->status = 0;
		filter->cache = 0;
		if (((c1 >= 0x81 && c1 <= 0x84) || (c1 >= 0x90 && c1 <= 0xe3)) &&
			c2 >= 0x30 && c2 <= 0x39 && c3 >= 0x81 && c3 <= 0xfe && c >= 0x30 && c <= 0x39) {
			if (c1 >= 0x90 && c1 <= 0xe3) {
				w = ((((c1 - 0x90)*10 + (c2 - 0x30))*126 + (c3 - 0x81)))*10 + (c - 0x30) + 0x10000;
			} else { /* Unicode BMP */
				w = (((c1 - 0x81)*10 + (c2 - 0x30))*126 + (c3 - 0x81))*10 + (c - 0x30);
				if (w >= 0 && w <= 39419) {
					k = mbfl_bisec_srch(w, mbfl_gb2uni_tbl, mbfl_gb_uni_max);
					if (k<0) {
						/* error */
						w = (c1 << 24) | (c2 << 16) | (c3 << 8) | c;
						w &= MBFL_WCSGROUP_MASK;
						w |= MBFL_WCSGROUP_THROUGH;
						CK((*filter->output_function)(w, filter->data));
						return c;
					}
					w += mbfl_gb_uni_ofst[k];
				} else {
					w = (c1 << 24) | (c2 << 16) | (c3 << 8) | c;
					w &= MBFL_WCSGROUP_MASK;
					w |= MBFL_WCSGROUP_THROUGH;
					CK((*filter->output_function)(w, filter->data));
					return c;
				}
			}
			CK((*filter->output_function)(w, filter->data));
		} else {
			w = (c1 << 24) | (c2 << 16) | (c3 << 8) | c;
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