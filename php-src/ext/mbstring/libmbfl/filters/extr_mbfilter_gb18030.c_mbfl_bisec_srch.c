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

/* Variables and functions */

int
mbfl_bisec_srch(int w, const unsigned short *tbl, int n)
{
	int k, k1 = 0, k2 = n-1;

	while (k1 < k2) {
		k = (k1+k2) >> 1;
		if (w <= tbl[2*k+1]) {
			k2 = k;
		} else if (w >= tbl[2*k+2]) {
			k1 = k + 1;
		} else {
			return -1;
		}
	}
	return k1;
}