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
mbfilter_conv_r_map_tbl(int c, int *w, const unsigned short map[][3], int n)
{
	int i, match = 0;

	for (i = 0; i < n; i++) {
		if (map[i][2] <= c && c <= map[i][2] - map[i][0] + map[i][1]) {
			*w = c + map[i][0] - map[i][2];
			match = 1;
			break;
		}
	}
	return match;
}