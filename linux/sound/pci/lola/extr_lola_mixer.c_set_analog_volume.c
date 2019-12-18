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
struct lola_pin {unsigned int amp_num_steps; unsigned int cur_gain_step; int /*<<< orphan*/  nid; int /*<<< orphan*/  is_analog; } ;
struct lola {TYPE_2__* card; TYPE_1__* pin; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {unsigned int num_pins; struct lola_pin* pins; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOLA_VERB_SET_AMP_GAIN_MUTE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  lola_codec_flush (struct lola*) ; 
 int lola_codec_write (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_analog_volume(struct lola *chip, int dir,
			     unsigned int idx, unsigned int val,
			     bool external_call)
{
	struct lola_pin *pin;
	int err;

	if (idx >= chip->pin[dir].num_pins)
		return -EINVAL;
	pin = &chip->pin[dir].pins[idx];
	if (!pin->is_analog || pin->amp_num_steps <= val)
		return -EINVAL;
	if (external_call && pin->cur_gain_step == val)
		return 0;
	if (external_call)
		lola_codec_flush(chip);
	dev_dbg(chip->card->dev,
		"set_analog_volume (dir=%d idx=%d, volume=%d)\n",
			dir, idx, val);
	err = lola_codec_write(chip, pin->nid,
			       LOLA_VERB_SET_AMP_GAIN_MUTE, val, 0);
	if (err < 0)
		return err;
	if (external_call)
		pin->cur_gain_step = val;
	return 0;
}