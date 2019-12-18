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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t checksum_fw(uint8_t *data, int len)
{
	int i;
	int32_t checksum = 0;

	for (i = 0; i < len - 1; i += 2) {
		checksum += (data[i + 1] << 8) | data[i];
	}
	if (i < len) {
		checksum += data[i];
	}
	checksum = checksum + (checksum >> 16) + 0xffff;
	checksum = ~(checksum + (checksum >> 16)) & 0xffff;
	return (uint16_t) checksum;
}