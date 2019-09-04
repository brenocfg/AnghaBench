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

__attribute__((used)) static int get_pending_timer_val(int val)
{
	int mult_bits = val >> 6;
	int mult = 1;

	switch (mult_bits)
	{
	case 1:
		mult = 4; break;
	case 2:
		mult = 16; break;
	case 3:
		mult = 64; break;
	case 0:
	default:
		break;
	}

	return (val & 0x3f) * mult;
}