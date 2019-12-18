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
 int spins_per_delay ; 

int
update_spins_per_delay(int shared_spins_per_delay)
{
	/*
	 * We use an exponential moving average with a relatively slow adaption
	 * rate, so that noise in any one backend's result won't affect the shared
	 * value too much.  As long as both inputs are within the allowed range,
	 * the result must be too, so we need not worry about clamping the result.
	 *
	 * We deliberately truncate rather than rounding; this is so that single
	 * adjustments inside a backend can affect the shared estimate (see the
	 * asymmetric adjustment rules above).
	 */
	return (shared_spins_per_delay * 15 + spins_per_delay) / 16;
}