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

u32 ncsi_calculate_checksum(unsigned char *data, int len)
{
	u32 checksum = 0;
	int i;

	for (i = 0; i < len; i += 2)
		checksum += (((u32)data[i] << 8) | data[i + 1]);

	checksum = (~checksum + 1);
	return checksum;
}