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
 int MBFL_WCSPLANE_KSC5601 ; 
 int MBFL_WCSPLANE_MASK ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int,int /*<<< orphan*/ ) ; 
 int* uhc2_ucs_table ; 
 int uhc2_ucs_table_size ; 
 int* uhc3_ucs_table ; 
 int uhc3_ucs_table_size ; 

int
mbfl_filt_conv_2022kr_wchar(int c, mbfl_convert_filter *filter)
{
	int c1, w, flag;

retry:
	switch (filter->status & 0xf) {
		/* case 0x00: ASCII */
		/* case 0x10: KSC5601 */
	case 0:
		if (c == 0x1b) { /* ESC */
			filter->status += 2;
		} else if (c == 0x0f) { /* SI (ASCII) */
			filter->status &= ~0xff;
		} else if (c == 0x0e) { /* SO (KSC5601) */
			filter->status |= 0x10;
		} else if ((filter->status & 0x10) != 0  && c > 0x20 && c < 0x7f) {
			/* KSC5601 lead byte */
			filter->cache = c;
			filter->status += 1;
		} else if ((filter->status & 0x10) == 0 &&  c >= 0 && c < 0x80) {
			/* latin, CTLs */
			CK((*filter->output_function)(c, filter->data));
		} else {
			w = c & MBFL_WCSGROUP_MASK;
			w |= MBFL_WCSGROUP_THROUGH;
			CK((*filter->output_function)(w, filter->data));
		}
		break;

	case 1:		/* dbcs second byte */
		filter->status &= ~0xf;
		c1 = filter->cache;
		flag = 0;
		if (c1 > 0x20 && c1 < 0x47) {
			flag = 1;
		} else if (c1 >= 0x47 && c1 <= 0x7e && c1 != 0x49) {
			flag = 2;
		}
		if (flag > 0 && c > 0x20 && c < 0x7f) {
			if (flag == 1){
				w = (c1 - 0x21)*190 + (c - 0x41) + 0x80;
				if (w >= 0 && w < uhc2_ucs_table_size) {
					w = uhc2_ucs_table[w];
				} else {
					w = 0;
				}
			} else {
				w = (c1 - 0x47)*94 + (c - 0x21);
				if (w >= 0 && w < uhc3_ucs_table_size) {
					w = uhc3_ucs_table[w];
				} else {
					w = 0;
				}
			}

			if (w <= 0) {
				w = (c1 << 8) | c;
				w &= MBFL_WCSPLANE_MASK;
				w |= MBFL_WCSPLANE_KSC5601;
			}
			CK((*filter->output_function)(w, filter->data));
		} else if (c == 0x1b) {	 /* ESC */
			filter->status++;
		} else if ((c >= 0 && c < 0x21) || c == 0x7f) {		/* CTLs */
			CK((*filter->output_function)(c, filter->data));
		} else {
			w = (c1 << 8) | c;
			w &= MBFL_WCSGROUP_MASK;
			w |= MBFL_WCSGROUP_THROUGH;
			CK((*filter->output_function)(w, filter->data));
		}
		break;

	case 2: 		/* ESC */
		if (c == 0x24) { /* '$' */
			filter->status++;
		} else {
			filter->status &= ~0xf;
			CK((*filter->output_function)(0x1b, filter->data));
			goto retry;
		}
		break;
	case 3:         /* ESC $ */
		if (c == 0x29) { /* ')' */
			filter->status++;
		} else {
			filter->status &= ~0xf;
			CK((*filter->output_function)(0x1b, filter->data));
			CK((*filter->output_function)(0x24, filter->data));
			goto retry;
		}
		break;
	case 4:         /* ESC $ )  */
		if (c == 0x43) { /* 'C' */
			filter->status &= ~0xf;
			filter->status |= 0x100;
		} else {
			filter->status &= ~0xf;
			CK((*filter->output_function)(0x1b, filter->data));
			CK((*filter->output_function)(0x24, filter->data));
			CK((*filter->output_function)(0x29, filter->data));
			goto retry;
		}
		break;
	default:
		filter->status = 0;
		break;
	}

	return c;
}