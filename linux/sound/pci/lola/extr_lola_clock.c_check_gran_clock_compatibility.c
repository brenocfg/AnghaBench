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
struct lola {int /*<<< orphan*/  granularity; } ;

/* Variables and functions */
 unsigned int LOLA_GRANULARITY_MAX ; 
 unsigned int LOLA_GRANULARITY_MIN ; 
 unsigned int LOLA_GRANULARITY_STEP ; 
 unsigned int LOLA_MAXFREQ_AT_GRANULARITY_BELOW_MAX ; 
 unsigned int LOLA_MAXFREQ_AT_GRANULARITY_MIN ; 

__attribute__((used)) static bool check_gran_clock_compatibility(struct lola *chip,
					   unsigned int val,
					   unsigned int freq)
{
	if (!chip->granularity)
		return true;

	if (val < LOLA_GRANULARITY_MIN || val > LOLA_GRANULARITY_MAX ||
	    (val % LOLA_GRANULARITY_STEP) != 0)
		return false;

	if (val == LOLA_GRANULARITY_MIN) {
		if (freq > LOLA_MAXFREQ_AT_GRANULARITY_MIN)
			return false;
	} else if (val < LOLA_GRANULARITY_MAX) {
		if (freq > LOLA_MAXFREQ_AT_GRANULARITY_BELOW_MAX)
			return false;
	}
	return true;
}