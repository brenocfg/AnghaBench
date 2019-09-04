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

__attribute__((used)) static u32 sis_rate_to_delta(unsigned int rate)
{
	u32 delta;

	/* This was copied from the trident driver, but it seems its gotten
	 * around a bit... nevertheless, it works well.
	 *
	 * We special case 44100 and 8000 since rounding with the equation
	 * does not give us an accurate enough value. For 11025 and 22050
	 * the equation gives us the best answer. All other frequencies will
	 * also use the equation. JDW
	 */
	if (rate == 44100)
		delta = 0xeb3;
	else if (rate == 8000)
		delta = 0x2ab;
	else if (rate == 48000)
		delta = 0x1000;
	else
		delta = (((rate << 12) + 24000) / 48000) & 0x0000ffff;
	return delta;
}