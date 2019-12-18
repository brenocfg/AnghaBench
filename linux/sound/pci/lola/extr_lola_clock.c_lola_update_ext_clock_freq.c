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
struct TYPE_4__ {size_t cur_index; int cur_valid; int /*<<< orphan*/  cur_freq; TYPE_1__* sample_clock; } ;
struct lola {TYPE_2__ clock; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ LOLA_CLOCK_TYPE_INTERNAL ; 
 unsigned int LOLA_UNSOLICITED_TAG ; 
 unsigned int LOLA_UNSOLICITED_TAG_MASK ; 
 unsigned int LOLA_UNSOL_RESP_TAG_OFFSET ; 
 int /*<<< orphan*/  lola_sample_rate_convert (unsigned int) ; 

bool lola_update_ext_clock_freq(struct lola *chip, unsigned int val)
{
	unsigned int tag;

	/* the current EXTERNAL clock information gets updated by interrupt
	 * with an unsolicited response
	 */
	if (!val)
		return false;
	tag = (val >> LOLA_UNSOL_RESP_TAG_OFFSET) & LOLA_UNSOLICITED_TAG_MASK;
	if (tag != LOLA_UNSOLICITED_TAG)
		return false;

	/* only for current = external clocks */
	if (chip->clock.sample_clock[chip->clock.cur_index].type !=
	    LOLA_CLOCK_TYPE_INTERNAL) {
		chip->clock.cur_freq = lola_sample_rate_convert(val & 0x7f);
		chip->clock.cur_valid = (val & 0x100) != 0;
	}
	return true;
}