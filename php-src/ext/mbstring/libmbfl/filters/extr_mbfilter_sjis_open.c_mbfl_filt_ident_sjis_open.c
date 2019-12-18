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

__attribute__((used)) static int mbfl_filt_ident_sjis_open(int c, mbfl_identify_filter *filter)
{
	if (filter->status) {		/* kanji second char */
		if (c < 0x40 || c > 0xfc || c == 0x7f) {	/* bad */
		    filter->flag = 1;
		}
		filter->status = 0;
	} else if (c >= 0 && c < 0x80) {	/* latin  ok */
		;
	} else if (c > 0xa0 && c < 0xe0) {	/* kana  ok */
		;
	} else if (c > 0x80 && c < 0xfd && c != 0xa0) {	/* kanji first char */
		filter->status = 1;
	} else {							/* bad */
		filter->flag = 1;
	}

	return c;
}