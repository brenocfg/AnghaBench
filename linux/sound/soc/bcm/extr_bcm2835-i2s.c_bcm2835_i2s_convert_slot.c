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

__attribute__((used)) static int bcm2835_i2s_convert_slot(unsigned int slot, unsigned int odd_offset)
{
	if (!odd_offset)
		return slot;

	if (slot & 1)
		return (slot >> 1) + odd_offset;

	return slot >> 1;
}