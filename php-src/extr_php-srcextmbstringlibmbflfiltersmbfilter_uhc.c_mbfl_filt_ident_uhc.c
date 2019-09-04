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

__attribute__((used)) static int mbfl_filt_ident_uhc(int c, mbfl_identify_filter *filter)
{
	switch (filter->status) {
	case 0: /* latin */
		if (c >= 0 && c < 0x80) { /* ok */
			;
		} else if (c >= 0x81 && c <= 0xa0) {	/* dbcs first char */
		    filter->status= 1;
		} else if (c >= 0xa1 && c <= 0xc6) {	/* dbcs first char */
		    filter->status= 2;
		} else if (c >= 0xc7 && c <= 0xfe) {	/* dbcs first char */
		    filter->status= 3;
		} else { /* bad */
			filter->flag = 1;
		}

	case 1:
	case 2:
		if (c < 0x41 || (c > 0x5a && c < 0x61)
			|| (c > 0x7a && c < 0x81) || c > 0xfe) {	/* bad */
		    filter->flag = 1;
		}
		filter->status = 0;
		break;

	case 3:
		if (c < 0xa1 || c > 0xfe) {	/* bad */
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