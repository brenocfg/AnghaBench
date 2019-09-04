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

__attribute__((used)) static int mbfl_filt_ident_hz(int c, mbfl_identify_filter *filter)
{
	switch (filter->status & 0xf) {
/*	case 0x00:	 ASCII */
/*	case 0x10:	 GB2312 */
	case 0:
		if (c == 0x7e) {
			filter->status += 2;
		} else if (filter->status == 0x10 && c > 0x20 && c < 0x7f) {		/* DBCS first char */
			filter->status += 1;
		} else if (c >= 0 && c < 0x80) {		/* latin, CTLs */
			;
		} else {
			filter->flag = 1;	/* bad */
		}
		break;

/*	case 0x11:	 GB2312 second char */
	case 1:
		filter->status &= ~0xf;
		if (c < 0x21 || c > 0x7e) {		/* bad */
			filter->flag = 1;
		}
		break;

	case 2:
		if (c == 0x7d) {		/* '}' */
			filter->status = 0;
		} else if (c == 0x7b) {		/* '{' */
			filter->status = 0x10;
		} else if (c == 0x7e) {		/* '~' */
			filter->status = 0;
		} else {
			filter->flag = 1;	/* bad */
			filter->status &= ~0xf;
		}
		break;

	default:
		filter->status = 0;
		break;
	}

	return c;
}