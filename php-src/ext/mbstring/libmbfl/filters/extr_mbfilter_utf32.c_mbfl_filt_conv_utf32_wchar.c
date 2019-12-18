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
 int MBFL_WCSPLANE_UTF32MAX ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 

int mbfl_filt_conv_utf32_wchar(int c, mbfl_convert_filter *filter)
{
	int n, endian;

	endian = filter->status & 0xff00;
	switch (filter->status & 0xff) {
	case 0:
		if (endian) {
			n = c & 0xff;
		} else {
			n = (unsigned) (c & 0xff) << 24;
		}
		filter->cache = n;
		filter->status++;
		break;
	case 1:
		if (endian) {
			n = (c & 0xff) << 8;
		} else {
			n = (c & 0xff) << 16;
		}
		filter->cache |= n;
		filter->status++;
		break;
	case 2:
		if (endian) {
			n = (c & 0xff) << 16;
		} else {
			n = (c & 0xff) << 8;
		}
		filter->cache |= n;
		filter->status++;
		break;
	default:
		if (endian) {
			n = (c & 0xff) << 24;
		} else {
			n = c & 0xff;
		}
		n |= filter->cache;
		if ((n & 0xffff) == 0 && ((n >> 16) & 0xffff) == 0xfffe) {
			if (endian) {
				filter->status = 0;		/* big-endian */
			} else {
				filter->status = 0x100;		/* little-endian */
			}
			CK((*filter->output_function)(0xfeff, filter->data));
		} else {
			filter->status &= ~0xff;
			if (n < MBFL_WCSPLANE_UTF32MAX && (n < 0xd800 || n > 0xdfff)) {
				CK((*filter->output_function)(n, filter->data));
			} else {
				n = (n & MBFL_WCSGROUP_MASK) | MBFL_WCSGROUP_THROUGH;
				CK((*filter->output_function)(n, filter->data));
			}
		}
		break;
	}

	return c;
}