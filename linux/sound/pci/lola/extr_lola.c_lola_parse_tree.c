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
struct lola {unsigned int lola_caps; int cold_reset; scalar_t__ granularity; TYPE_2__* card; TYPE_1__* pin; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ num_pins; } ;

/* Variables and functions */
 size_t CAPT ; 
 int EINVAL ; 
 scalar_t__ LOLA_AFG_CLOCK_WIDGET_PRESENT (unsigned int) ; 
 scalar_t__ LOLA_AFG_INPUT_PIN_COUNT (unsigned int) ; 
 scalar_t__ LOLA_AFG_MIXER_WIDGET_PRESENT (unsigned int) ; 
 scalar_t__ LOLA_AFG_OUTPUT_PIN_COUNT (unsigned int) ; 
 scalar_t__ LOLA_GRANULARITY_MIN ; 
 int /*<<< orphan*/  LOLA_PAR_FUNCTION_TYPE ; 
 int /*<<< orphan*/  LOLA_PAR_SPECIFIC_CAPS ; 
 int /*<<< orphan*/  LOLA_PAR_VENDOR_ID ; 
 scalar_t__ MAX_AUDIO_INOUT_COUNT ; 
 size_t PLAY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int lola_enable_clock_events (struct lola*) ; 
 int lola_init_clock_widget (struct lola*,int) ; 
 int lola_init_mixer_widget (struct lola*,int) ; 
 int lola_init_pcm (struct lola*,size_t,int*) ; 
 int lola_init_pins (struct lola*,size_t,int*) ; 
 int lola_read_param (struct lola*,int,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  lola_reset_setups (struct lola*) ; 
 int /*<<< orphan*/  lola_set_granularity (struct lola*,scalar_t__,int) ; 

__attribute__((used)) static int lola_parse_tree(struct lola *chip)
{
	unsigned int val;
	int nid, err;

	err = lola_read_param(chip, 0, LOLA_PAR_VENDOR_ID, &val);
	if (err < 0) {
		dev_err(chip->card->dev, "Can't read VENDOR_ID\n");
		return err;
	}
	val >>= 16;
	if (val != 0x1369) {
		dev_err(chip->card->dev, "Unknown codec vendor 0x%x\n", val);
		return -EINVAL;
	}

	err = lola_read_param(chip, 1, LOLA_PAR_FUNCTION_TYPE, &val);
	if (err < 0) {
		dev_err(chip->card->dev, "Can't read FUNCTION_TYPE\n");
		return err;
	}
	if (val != 1) {
		dev_err(chip->card->dev, "Unknown function type %d\n", val);
		return -EINVAL;
	}

	err = lola_read_param(chip, 1, LOLA_PAR_SPECIFIC_CAPS, &val);
	if (err < 0) {
		dev_err(chip->card->dev, "Can't read SPECCAPS\n");
		return err;
	}
	chip->lola_caps = val;
	chip->pin[CAPT].num_pins = LOLA_AFG_INPUT_PIN_COUNT(chip->lola_caps);
	chip->pin[PLAY].num_pins = LOLA_AFG_OUTPUT_PIN_COUNT(chip->lola_caps);
	dev_dbg(chip->card->dev, "speccaps=0x%x, pins in=%d, out=%d\n",
		    chip->lola_caps,
		    chip->pin[CAPT].num_pins, chip->pin[PLAY].num_pins);

	if (chip->pin[CAPT].num_pins > MAX_AUDIO_INOUT_COUNT ||
	    chip->pin[PLAY].num_pins > MAX_AUDIO_INOUT_COUNT) {
		dev_err(chip->card->dev, "Invalid Lola-spec caps 0x%x\n", val);
		return -EINVAL;
	}

	nid = 0x02;
	err = lola_init_pcm(chip, CAPT, &nid);
	if (err < 0)
		return err;
	err = lola_init_pcm(chip, PLAY, &nid);
	if (err < 0)
		return err;

	err = lola_init_pins(chip, CAPT, &nid);
	if (err < 0)
		return err;
	err = lola_init_pins(chip, PLAY, &nid);
	if (err < 0)
		return err;

	if (LOLA_AFG_CLOCK_WIDGET_PRESENT(chip->lola_caps)) {
		err = lola_init_clock_widget(chip, nid);
		if (err < 0)
			return err;
		nid++;
	}
	if (LOLA_AFG_MIXER_WIDGET_PRESENT(chip->lola_caps)) {
		err = lola_init_mixer_widget(chip, nid);
		if (err < 0)
			return err;
		nid++;
	}

	/* enable unsolicited events of the clock widget */
	err = lola_enable_clock_events(chip);
	if (err < 0)
		return err;

	/* if last ResetController was not a ColdReset, we don't know
	 * the state of the card; initialize here again
	 */
	if (!chip->cold_reset) {
		lola_reset_setups(chip);
		chip->cold_reset = 1;
	} else {
		/* set the granularity if it is not the default */
		if (chip->granularity != LOLA_GRANULARITY_MIN)
			lola_set_granularity(chip, chip->granularity, true);
	}

	return 0;
}