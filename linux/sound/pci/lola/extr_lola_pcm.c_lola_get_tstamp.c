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
struct lola {int granularity; } ;

/* Variables and functions */
 int lola_get_lrc (struct lola*) ; 

__attribute__((used)) static unsigned int lola_get_tstamp(struct lola *chip, bool quick_no_sync)
{
	unsigned int tstamp = lola_get_lrc(chip) >> 8;
	if (chip->granularity) {
		unsigned int wait_banks = quick_no_sync ? 0 : 8;
		tstamp += (wait_banks + 1) * chip->granularity - 1;
		tstamp -= tstamp % chip->granularity;
	}
	return tstamp << 8;
}