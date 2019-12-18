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
struct TYPE_3__ {int status; int flag; } ;
typedef  TYPE_1__ mbfl_identify_filter ;

/* Variables and functions */

int mbfl_filt_ident_utf8(int c, mbfl_identify_filter *filter)
{
	int c1;

	c1 = (filter->status >> 8) & 0xff;
	filter->status &= 0xff;

	if (c < 0x80) {
		if (c < 0) {
			filter->flag = 1;	/* bad */
		} else if (filter->status) {
			filter->flag = 1;	/* bad */
		}
		filter->status = 0;
	} else if (c < 0xc0) {
		switch (filter->status) {
		case 0x20: /* 3 byte code 2nd char */
			if ((c1 == 0x0 && c >= 0xa0) ||
				(c1 == 0xd && c < 0xa0) ||
				(c1 > 0x0 && c1 != 0xd)) {
				filter->status++;
			} else {
				filter->flag = 1;	/* bad */
				filter->status = 0;
			}
			break;
		case 0x30: /* 4 byte code 2nd char */
			if ((c1 == 0x0 && c >= 0x90) ||
				(c1 > 0x0 && c1 < 0x4) ||
				(c1 == 0x4 && c < 0x90)) {
				filter->status++;
			} else {
				filter->flag = 1;	/* bad */
				filter->status = 0;
			}
			break;
		case 0x31: /* 4 byte code 3rd char */
			filter->status++;
			break;
		case 0x10: /* 2 byte code 2nd char */
		case 0x21: /* 3 byte code 3rd char */
		case 0x32: /* 4 byte code 4th char */
			filter->status = 0;
			break;
		default:
			filter->flag = 1;	/* bad */
			filter->status = 0;
			break;
		}
	} else if (c < 0xc2) { /* 0xc0,0xc1 */
		filter->flag = 1;	/* bad */
		filter->status = 0;
	} else {
		if (filter->status) {
			filter->flag = 1;	/* bad */
		}
		filter->status = 0;
		if (c < 0xe0) {				/* 2 byte code first char */
			filter->status = 0x10;
		} else if (c < 0xf0) {		/* 3 byte code 1st char */
			filter->status = 0x20;
			filter->status |= (c & 0xf) << 8;
		} else if (c < 0xf5) {		/* 4 byte code 1st char */
			filter->status = 0x30;
			filter->status |= (c & 0x7) << 8;
		} else {
			filter->flag = 1;	/* bad */
		}
	}

	return c;
}