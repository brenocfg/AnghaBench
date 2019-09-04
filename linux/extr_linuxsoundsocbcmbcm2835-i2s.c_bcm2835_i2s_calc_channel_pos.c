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
 unsigned int bcm2835_i2s_convert_slot (scalar_t__,unsigned int) ; 
 scalar_t__ ffs (unsigned int) ; 
 scalar_t__ fls (unsigned int) ; 

__attribute__((used)) static void bcm2835_i2s_calc_channel_pos(
	unsigned int *ch1_pos, unsigned int *ch2_pos,
	unsigned int mask, unsigned int width,
	unsigned int bit_offset, unsigned int odd_offset)
{
	*ch1_pos = bcm2835_i2s_convert_slot((ffs(mask) - 1), odd_offset)
			* width + bit_offset;
	*ch2_pos = bcm2835_i2s_convert_slot((fls(mask) - 1), odd_offset)
			* width + bit_offset;
}