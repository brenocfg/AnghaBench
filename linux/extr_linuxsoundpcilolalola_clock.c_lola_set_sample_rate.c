#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cur_freq; int items; TYPE_1__* sample_clock; scalar_t__ cur_valid; } ;
struct lola {TYPE_2__ clock; } ;
struct TYPE_3__ {scalar_t__ type; int freq; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LOLA_CLOCK_TYPE_INTERNAL ; 
 int lola_set_clock (struct lola*,int) ; 

int lola_set_sample_rate(struct lola *chip, int rate)
{
	int i;

	if (chip->clock.cur_freq == rate && chip->clock.cur_valid)
		return 0;
	/* search for new dwClockIndex */
	for (i = 0; i < chip->clock.items; i++) {
		if (chip->clock.sample_clock[i].type == LOLA_CLOCK_TYPE_INTERNAL &&
		    chip->clock.sample_clock[i].freq == rate)
			break;
	}
	if (i >= chip->clock.items)
		return -EINVAL;
	return lola_set_clock(chip, i);
}