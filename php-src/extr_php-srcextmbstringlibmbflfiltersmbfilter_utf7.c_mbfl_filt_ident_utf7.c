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

__attribute__((used)) static int mbfl_filt_ident_utf7(int c, mbfl_identify_filter *filter)
{
	int n;

	switch (filter->status) {
	/* directly encoded characters */
	case 0:
		if (c == 0x2b) {	/* '+'  shift character */
			filter->status++;
		} else if (c == 0x5c || c == 0x7e || c < 0 || c > 0x7f) {	/* illegal character */
			filter->flag = 1;	/* bad */
		}
		break;

	/* Modified Base64 */
	case 1:
	case 2:
		n = 0;
		if (c >= 0x41 && c <= 0x5a) {		/* A - Z */
			n = 1;
		} else if (c >= 0x61 && c <= 0x7a) {	/* a - z */
			n = 1;
		} else if (c >= 0x30 && c <= 0x39) {	/* 0 - 9 */
			n = 1;
		} else if (c == 0x2b) {			/* '+' */
			n = 1;
		} else if (c == 0x2f) {			/* '/' */
			n = 1;
		}
		if (n <= 0) {
			if (filter->status == 1 && c != 0x2d) {
				filter->flag = 1;	/* bad */
			} else if (c < 0 || c > 0x7f) {
				filter->flag = 1;	/* bad */
			}
			filter->status = 0;
		} else {
			filter->status = 2;
		}
		break;

	default:
		filter->status = 0;
		break;
	}

	return c;
}