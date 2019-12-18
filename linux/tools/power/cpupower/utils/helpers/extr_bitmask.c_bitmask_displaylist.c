#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bitmask {unsigned int size; } ;

/* Variables and functions */
 unsigned int bitmask_first (struct bitmask const*) ; 
 unsigned int bitmask_next (struct bitmask const*,unsigned int) ; 
 int emit (char*,int,unsigned int,unsigned int,int) ; 

int bitmask_displaylist(char *buf, int buflen, const struct bitmask *bmp)
{
	int len = 0;
	/* current bit is 'cur', most recently seen range is [rbot, rtop] */
	unsigned int cur, rbot, rtop;

	if (buflen > 0)
		*buf = 0;
	rbot = cur = bitmask_first(bmp);
	while (cur < bmp->size) {
		rtop = cur;
		cur = bitmask_next(bmp, cur+1);
		if (cur >= bmp->size || cur > rtop + 1) {
			len = emit(buf, buflen, rbot, rtop, len);
			rbot = cur;
		}
	}
	return len;
}