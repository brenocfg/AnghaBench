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
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  printf (char*) ; 
 unsigned long long timing (int /*<<< orphan*/ ,unsigned long long) ; 

unsigned long long calibrate(void)
{
	unsigned long long i;

	printf("Calibrating reasonable sample size...\n");

	for (i = 5; ; i++) {
		unsigned long long samples = 1 << i;

		/* Find something that takes more than 5 seconds to run. */
		if (timing(CLOCK_REALTIME, samples) / 1000000000ULL > 5)
			return samples;
	}
}