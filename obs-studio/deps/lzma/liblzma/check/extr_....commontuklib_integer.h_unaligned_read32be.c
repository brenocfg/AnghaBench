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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
unaligned_read32be(const uint8_t *buf)
{
	uint32_t num = (uint32_t)buf[0] << 24;
	num |= (uint32_t)buf[1] << 16;
	num |= (uint32_t)buf[2] << 8;
	num |= (uint32_t)buf[3];
	return num;
}