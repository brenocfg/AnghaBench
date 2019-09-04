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
struct iio_channel_info {scalar_t__ index; } ;

/* Variables and functions */

void bsort_channel_array_by_index(struct iio_channel_info *ci_array, int cnt)
{
	struct iio_channel_info temp;
	int x, y;

	for (x = 0; x < cnt; x++)
		for (y = 0; y < (cnt - 1); y++)
			if (ci_array[y].index > ci_array[y + 1].index) {
				temp = ci_array[y + 1];
				ci_array[y + 1] = ci_array[y];
				ci_array[y] = temp;
			}
}