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
 unsigned int DA9063_TWDSCALE_MAX ; 
 unsigned int DA9063_TWDSCALE_MIN ; 
 unsigned int* wdt_timeout ; 

__attribute__((used)) static unsigned int da9063_wdt_timeout_to_sel(unsigned int secs)
{
	unsigned int i;

	for (i = DA9063_TWDSCALE_MIN; i <= DA9063_TWDSCALE_MAX; i++) {
		if (wdt_timeout[i] >= secs)
			return i;
	}

	return DA9063_TWDSCALE_MAX;
}