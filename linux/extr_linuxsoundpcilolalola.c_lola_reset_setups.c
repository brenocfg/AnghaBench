#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cur_index; } ;
struct lola {int /*<<< orphan*/  input_src_mask; TYPE_1__ clock; int /*<<< orphan*/  granularity; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPT ; 
 int /*<<< orphan*/  PLAY ; 
 int /*<<< orphan*/  lola_enable_clock_events (struct lola*) ; 
 int /*<<< orphan*/  lola_set_clock_index (struct lola*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lola_set_granularity (struct lola*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lola_set_src_config (struct lola*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lola_setup_all_analog_gains (struct lola*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lola_reset_setups(struct lola *chip)
{
	/* update the granularity */
	lola_set_granularity(chip, chip->granularity, true);
	/* update the sample clock */
	lola_set_clock_index(chip, chip->clock.cur_index);
	/* enable unsolicited events of the clock widget */
	lola_enable_clock_events(chip);
	/* update the analog gains */
	lola_setup_all_analog_gains(chip, CAPT, false); /* input, update */
	/* update SRC configuration if applicable */
	lola_set_src_config(chip, chip->input_src_mask, false);
	/* update the analog outputs */
	lola_setup_all_analog_gains(chip, PLAY, false); /* output, update */
}