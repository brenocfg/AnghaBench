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
typedef  int off_t ;

/* Variables and functions */
 size_t strlen (char*) ; 
 char* xitoa (int) ; 
 size_t xstrlcpy (char*,char*,int) ; 

__attribute__((used)) static char *coolsize(off_t size)
{
	const char * const U = "BKMGTPEZY";
	static char size_buf[12]; /* Buffer to hold human readable size */
	off_t rem = 0;
	size_t ret;
	int i = 0;

	while (size >= 1024) {
		rem = size & (0x3FF); /* 1024 - 1 = 0x3FF */
		size >>= 10;
		++i;
	}

	if (i == 1) {
		rem = (rem * 1000) >> 10;

		rem /= 10;
		if (rem % 10 >= 5) {
			rem = (rem / 10) + 1;
			if (rem == 10) {
				++size;
				rem = 0;
			}
		} else
			rem /= 10;
	} else if (i == 2) {
		rem = (rem * 1000) >> 10;

		if (rem % 10 >= 5) {
			rem = (rem / 10) + 1;
			if (rem == 100) {
				++size;
				rem = 0;
			}
		} else
			rem /= 10;
	} else if (i > 0) {
		rem = (rem * 10000) >> 10;

		if (rem % 10 >= 5) {
			rem = (rem / 10) + 1;
			if (rem == 1000) {
				++size;
				rem = 0;
			}
		} else
			rem /= 10;
	}

	if (i > 0 && i < 6 && rem) {
		ret = xstrlcpy(size_buf, xitoa(size), 12);
		size_buf[ret - 1] = '.';

		char *frac = xitoa(rem);
		size_t toprint = i > 3 ? 3 : i;
		size_t len = strlen(frac);

		if (len < toprint) {
			size_buf[ret] = size_buf[ret + 1] = size_buf[ret + 2] = '0';
			xstrlcpy(size_buf + ret + (toprint - len), frac, len + 1);
		} else
			xstrlcpy(size_buf + ret, frac, toprint + 1);

		ret += toprint;
	} else {
		ret = xstrlcpy(size_buf, size ? xitoa(size) : "0", 12);
		--ret;
	}

	size_buf[ret] = U[i];
	size_buf[ret + 1] = '\0';

	return size_buf;
}