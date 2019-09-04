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

__attribute__((used)) static int mbfl_filt_ident_euccn(int c, mbfl_identify_filter *filter)
{
	switch (filter->status) {
	case  0:	/* latin */
		if (c >= 0 && c < 0x80) {	/* ok */
			;
		} else if (c > 0xa0 && c < 0xff) {	/* DBCS lead byte */
			filter->status = 1;
		} else {							/* bad */
			filter->flag = 1;
		}
		break;

	case  1:	/* got lead byte */
		if (c < 0xa1 || c > 0xfe) {		/* bad */
			filter->flag = 1;
		}
		filter->status = 0;
		break;

	default:
		filter->status = 0;
		break;
	}

	return c;
}