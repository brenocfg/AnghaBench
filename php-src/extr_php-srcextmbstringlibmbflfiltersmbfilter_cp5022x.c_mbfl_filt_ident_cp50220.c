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

__attribute__((used)) static int mbfl_filt_ident_cp50220(int c, mbfl_identify_filter *filter)
{
retry:
	switch (filter->status & 0xf) {
/*	case 0x00:	 ASCII */
/*	case 0x10:	 X 0201 latin */
/*	case 0x80:	 X 0208 */
	case 0:
		if (c == 0x1b) {
			filter->status += 2;
		} else if (filter->status == 0x80 && c > 0x20 && c < 0x7f) {		/* kanji first char */
			filter->status += 1;
		} else if (c >= 0 && c < 0x80) {		/* latin, CTLs */
			;
		} else {
			filter->flag = 1;	/* bad */
		}
		break;

/*	case 0x81:	 X 0208 second char */
	case 1:
		if (c == 0x1b) {
			filter->status++;
		} else {
			filter->status &= ~0xf;
			if (c < 0x21 || c > 0x7e) {		/* bad */
				filter->flag = 1;
			}
		}
		break;

	/* ESC */
	case 2:
		if (c == 0x24) {		/* '$' */
			filter->status++;
		} else if (c == 0x28) {		/* '(' */
			filter->status += 3;
		} else {
			filter->flag = 1;	/* bad */
			filter->status &= ~0xf;
			goto retry;
		}
		break;

	/* ESC $ */
	case 3:
		if (c == 0x40 || c == 0x42) {		/* '@' or 'B' */
			filter->status = 0x80;
		} else {
			filter->flag = 1;	/* bad */
			filter->status &= ~0xf;
			goto retry;
		}
		break;

	/* ESC ( */
	case 5:
		if (c == 0x42) {		/* 'B' */
			filter->status = 0;
		} else if (c == 0x4a) {		/* 'J' */
			filter->status = 0x10;
		} else {
			filter->flag = 1;	/* bad */
			filter->status &= ~0xf;
			goto retry;
		}
		break;

	default:
		filter->status = 0;
		break;
	}

	return c;
}