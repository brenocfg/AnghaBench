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
struct lola_pin {int nid; int is_analog; unsigned int max_level; scalar_t__ cur_gain_step; scalar_t__ fixed_gain_list_len; scalar_t__ config_default_reg; int /*<<< orphan*/  amp_offset; int /*<<< orphan*/  amp_step_size; int /*<<< orphan*/  amp_num_steps; int /*<<< orphan*/  amp_mute; } ;
struct lola {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CAPT ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOLA_AMP_MUTE_CAPABLE (unsigned int) ; 
 int /*<<< orphan*/  LOLA_AMP_NUM_STEPS (unsigned int) ; 
 int /*<<< orphan*/  LOLA_AMP_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  LOLA_AMP_STEP_SIZE (unsigned int) ; 
 int /*<<< orphan*/  LOLA_PAR_AMP_IN_CAP ; 
 int /*<<< orphan*/  LOLA_PAR_AMP_OUT_CAP ; 
 int /*<<< orphan*/  LOLA_PAR_AUDIO_WIDGET_CAP ; 
 int /*<<< orphan*/  LOLA_VERB_GET_MAX_LEVEL ; 
 int PLAY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int lola_codec_read (struct lola*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *) ; 
 int lola_read_param (struct lola*,int,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int lola_init_pin(struct lola *chip, struct lola_pin *pin,
			 int dir, int nid)
{
	unsigned int val;
	int err;

	pin->nid = nid;
	err = lola_read_param(chip, nid, LOLA_PAR_AUDIO_WIDGET_CAP, &val);
	if (err < 0) {
		dev_err(chip->card->dev, "Can't read wcaps for 0x%x\n", nid);
		return err;
	}
	val &= 0x00f00fff; /* test TYPE and bits 0..11 */
	if (val == 0x00400200)    /* Type = 4, Digital = 1 */
		pin->is_analog = false;
	else if (val == 0x0040000a && dir == CAPT) /* Dig=0, InAmp/ovrd */
		pin->is_analog = true;
	else if (val == 0x0040000c && dir == PLAY) /* Dig=0, OutAmp/ovrd */
		pin->is_analog = true;
	else {
		dev_err(chip->card->dev, "Invalid wcaps 0x%x for 0x%x\n", val, nid);
		return -EINVAL;
	}

	/* analog parameters only following, so continue in case of Digital pin
	 */
	if (!pin->is_analog)
		return 0;

	if (dir == PLAY)
		err = lola_read_param(chip, nid, LOLA_PAR_AMP_OUT_CAP, &val);
	else
		err = lola_read_param(chip, nid, LOLA_PAR_AMP_IN_CAP, &val);
	if (err < 0) {
		dev_err(chip->card->dev, "Can't read AMP-caps for 0x%x\n", nid);
		return err;
	}

	pin->amp_mute = LOLA_AMP_MUTE_CAPABLE(val);
	pin->amp_step_size = LOLA_AMP_STEP_SIZE(val);
	pin->amp_num_steps = LOLA_AMP_NUM_STEPS(val);
	if (pin->amp_num_steps) {
		/* zero as mute state */
		pin->amp_num_steps++;
		pin->amp_step_size++;
	}
	pin->amp_offset = LOLA_AMP_OFFSET(val);

	err = lola_codec_read(chip, nid, LOLA_VERB_GET_MAX_LEVEL, 0, 0, &val,
			      NULL);
	if (err < 0) {
		dev_err(chip->card->dev, "Can't get MAX_LEVEL 0x%x\n", nid);
		return err;
	}
	pin->max_level = val & 0x3ff;   /* 10 bits */

	pin->config_default_reg = 0;
	pin->fixed_gain_list_len = 0;
	pin->cur_gain_step = 0;

	return 0;
}