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

__attribute__((used)) static int mbfl_filt_ident_gb18030(int c, mbfl_identify_filter *filter)
{
	int c1;

	c1 = (filter->status >> 8) & 0xff;
	filter->status &= 0xff;

	if (filter->status == 0) {
		if (c <= 0x80 || c == 0xff) {
			filter->status = 0;
		} else {
			filter->status = 1;
			filter->status |= (c << 8);
		}
	} else if (filter->status == 1) { /* dbcs/qbcs 2nd byte */
		if (((c1 >= 0x81 && c1 <= 0x84) || (c1 >= 0x90 && c1 <= 0xe3)) && c >= 0x30 && c <= 0x39) { /* qbcs */
			filter->status = 2;
		} else if (((c1 >= 0xaa && c1 <= 0xaf) || (c1 >= 0xf8 && c1 <= 0xfe)) && (c >= 0xa1 && c <= 0xfe)) {
			filter->status = 0; /* UDA part 1,2 */
		} else if (c1 >= 0xa1 && c1 <= 0xa7 && c >= 0x40 && c < 0xa1 && c != 0x7f) {
			filter->status = 0; /* UDA part 3 */
		} else if ((c1 >= 0xa1 && c1 <= 0xa9 && c >= 0xa1 && c <= 0xfe) ||
				   (c1 >= 0xb0 && c1 <= 0xf7 && c >= 0xa1 && c <= 0xfe) ||
				   (c1 >= 0x81 && c1 <= 0xa0 && c >= 0x40 && c <= 0xfe && c != 0x7f) ||
				   (c1 >= 0xaa && c1 <= 0xfe && c >= 0x40 && c <= 0xa0 && c != 0x7f) ||
				   (c1 >= 0xa8 && c1 <= 0xa9 && c >= 0x40 && c <= 0xa0 && c != 0x7f)) {
			filter->status = 0; /* DBCS */
		} else {
			filter->flag = 1; /* bad */
			filter->status = 0;
		}
	} else if (filter->status == 2) { /* qbcs 3rd byte */
		if (c > 0x80 && c < 0xff) {
			filter->status = 3;
		} else {
			filter->flag = 1; /* bad */
			filter->status = 0;
		}
	} else if (filter->status == 3) { /* qbcs 4th byte */
		if (c >= 0x30 && c < 0x40) {
			filter->status = 0;
		} else {
			filter->flag = 1; /* bad */
			filter->status = 0;
		}
	} else {							/* bad */
		filter->flag = 1;
	}

	return c;
}