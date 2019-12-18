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
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 

int mbfl_filt_conv_base64dec(int c, mbfl_convert_filter *filter)
{
	int n;

	if (c == 0x0d || c == 0x0a || c == 0x20 || c == 0x09 || c == 0x3d) {	/* CR or LF or SPACE or HTAB or '=' */
		return c;
	}

	n = 0;
	if (c >= 0x41 && c <= 0x5a) {		/* A - Z */
		n = c - 65;
	} else if (c >= 0x61 && c <= 0x7a) {	/* a - z */
		n = c - 71;
	} else if (c >= 0x30 && c <= 0x39) {	/* 0 - 9 */
		n = c + 4;
	} else if (c == 0x2b) {			/* '+' */
		n = 62;
	} else if (c == 0x2f) {			/* '/' */
		n = 63;
	}
	n &= 0x3f;

	switch (filter->status) {
	case 0:
		filter->status = 1;
		filter->cache = n << 18;
		break;
	case 1:
		filter->status = 2;
		filter->cache |= n << 12;
		break;
	case 2:
		filter->status = 3;
		filter->cache |= n << 6;
		break;
	default:
		filter->status = 0;
		n |= filter->cache;
		CK((*filter->output_function)((n >> 16) & 0xff, filter->data));
		CK((*filter->output_function)((n >> 8) & 0xff, filter->data));
		CK((*filter->output_function)(n & 0xff, filter->data));
		break;
	}

	return c;
}