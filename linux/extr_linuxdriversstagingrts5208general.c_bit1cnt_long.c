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
typedef  int u32 ;

/* Variables and functions */

int bit1cnt_long(u32 data)
{
	int i, cnt = 0;

	for (i = 0; i < 32; i++) {
		if (data & 0x01)
			cnt++;
		data >>= 1;
	}
	return cnt;
}