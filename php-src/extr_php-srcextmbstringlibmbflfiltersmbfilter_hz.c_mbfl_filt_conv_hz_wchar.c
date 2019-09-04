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
 int MBFL_WCSPLANE_GB2312 ; 
 int MBFL_WCSPLANE_MASK ; 
 int* cp936_ucs_table ; 
 int cp936_ucs_table_size ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 

int
mbfl_filt_conv_hz_wchar(int c, mbfl_convert_filter *filter)
{
	int c1, s, w;

	switch (filter->status & 0xf) {
/*	case 0x00:	 ASCII */
/*	case 0x10:	 GB2312 */
	case 0:
		if (c == 0x7e) {
			filter->status += 2;
		} else if (filter->status == 0x10 && c > 0x20 && c < 0x7f) {	/* DBCS first char */
			filter->cache = c;
			filter->status += 1;
		} else if (c >= 0 && c < 0x80) {		/* latin, CTLs */
			CK((*filter->output_function)(c, filter->data));
		} else {
			w = c & MBFL_WCSGROUP_MASK;
			w |= MBFL_WCSGROUP_THROUGH;
			CK((*filter->output_function)(w, filter->data));
		}
		break;

/*	case 0x11:	 GB2312 second char */
	case 1:
		filter->status &= ~0xf;
		c1 = filter->cache;
		if (c1 > 0x20 && c1 < 0x7f && c > 0x20 && c < 0x7f) {
			s = (c1 - 1)*192 + c + 0x40; /* GB2312 */
			if (s >= 0 && s < cp936_ucs_table_size) {
				w = cp936_ucs_table[s];
			} else {
				w = 0;
			}
			if (w <= 0) {
				w = (c1 << 8) | c;
				w &= MBFL_WCSPLANE_MASK;
				w |= MBFL_WCSPLANE_GB2312;
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

	/* '~' */
	case 2:
		if (c == 0x7d) {		/* '}' */
			filter->status = 0x0;
		} else if (c == 0x7b) {		/* '{' */
			filter->status = 0x10;
		} else if (c == 0x7e) { /* '~' */
			filter->status = 0x0;
			CK((*filter->output_function)(0x007e, filter->data));
		}
		break;

	default:
		filter->status = 0;
		break;
	}

	return c;
}