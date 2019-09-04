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
struct TYPE_4__ {int cur_index; int cur_freq; int cur_valid; TYPE_1__* sample_clock; } ;
struct lola {TYPE_2__ clock; int /*<<< orphan*/  granularity; } ;
struct TYPE_3__ {scalar_t__ type; int freq; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LOLA_CLOCK_TYPE_INTERNAL ; 
 int /*<<< orphan*/  check_gran_clock_compatibility (struct lola*,int /*<<< orphan*/ ,int) ; 
 int lola_set_clock_index (struct lola*,int) ; 

int lola_set_clock(struct lola *chip, int idx)
{
	int freq = 0;
	bool valid = false;

	if (idx == chip->clock.cur_index) {
		/* current clock is allowed */
		freq = chip->clock.cur_freq;
		valid = chip->clock.cur_valid;
	} else if (chip->clock.sample_clock[idx].type ==
		   LOLA_CLOCK_TYPE_INTERNAL) {
		/* internal clocks allowed */
		freq = chip->clock.sample_clock[idx].freq;
		valid = true;
	}

	if (!freq || !valid)
		return -EINVAL;

	if (!check_gran_clock_compatibility(chip, chip->granularity, freq))
		return -EINVAL;

	if (idx != chip->clock.cur_index) {
		int err = lola_set_clock_index(chip, idx);
		if (err < 0)
			return err;
		/* update new settings */
		chip->clock.cur_index = idx;
		chip->clock.cur_freq = freq;
		chip->clock.cur_valid = true;
	}
	return 0;
}