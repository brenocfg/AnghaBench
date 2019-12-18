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
typedef  int uint32_t ;
typedef  scalar_t__ u_int16_t ;

/* Variables and functions */
 scalar_t__ ntohs (scalar_t__) ; 

__attribute__((used)) static uint32_t raw_checksum(uint8_t *buf, int len, uint32_t sum)
{
	int i;

	for (i = 0; i < (len & ~1U); i += 2) {
		sum += (u_int16_t)ntohs(*((u_int16_t *)(buf + i)));
		if (sum > 0xffff)
			sum -= 0xffff;
	}

	if (i < len) {
		sum += buf[i] << 8;
		if (sum > 0xffff)
			sum -= 0xffff;
	}

	return sum;
}