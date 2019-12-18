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
 int MBFL_WCSPLANE_SUPMAX ; 
 int MBFL_WCSPLANE_SUPMIN ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 

int mbfl_filt_conv_utf16_wchar(int c, mbfl_convert_filter *filter)
{
	int n, endian;

	endian = filter->status & 0xff00;
	switch (filter->status & 0x0f) {
	case 0:
		if (endian) {
			n = c & 0xff;
		} else {
			n = (c & 0xff) << 8;
		}
		filter->cache |= n;
		filter->status++;
		break;
	default:
		if (endian) {
			n = (c & 0xff) << 8;
		} else {
			n = c & 0xff;
		}
		n |= filter->cache & 0xffff;
		filter->status &= ~0x0f;
		if (n >= 0xd800 && n < 0xdc00) {
			filter->cache = ((n & 0x3ff) << 16) + 0x400000;
		} else if (n >= 0xdc00 && n < 0xe000) {
			n &= 0x3ff;
			n |= (filter->cache & 0xfff0000) >> 6;
			filter->cache = 0;
			if (n >= MBFL_WCSPLANE_SUPMIN && n < MBFL_WCSPLANE_SUPMAX) {
				CK((*filter->output_function)(n, filter->data));
			} else {		/* illegal character */
				n &= MBFL_WCSGROUP_MASK;
				n |= MBFL_WCSGROUP_THROUGH;
				CK((*filter->output_function)(n, filter->data));
			}
		} else {
			int is_first = filter->status & 0x10;
			filter->cache = 0;
			filter->status |= 0x10;
			if (!is_first) {
				if (n == 0xfffe) {
					if (endian) {
						filter->status &= ~0x100;		/* big-endian */
					} else {
						filter->status |= 0x100;		/* little-endian */
					}
					break;
				} else if (n == 0xfeff) {
					break;
				}
			}
			CK((*filter->output_function)(n, filter->data));
		}
		break;
	}

	return c;
}