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

__attribute__((used)) static long ppb_to_scaled_ppm(int ppb)
{
	/*
	 * The 'freq' field in the 'struct timex' is in parts per
	 * million, but with a 16 bit binary fractional field.
	 * Instead of calculating either one of
	 *
	 *    scaled_ppm = (ppb / 1000) << 16  [1]
	 *    scaled_ppm = (ppb << 16) / 1000  [2]
	 *
	 * we simply use double precision math, in order to avoid the
	 * truncation in [1] and the possible overflow in [2].
	 */
	return (long) (ppb * 65.536);
}