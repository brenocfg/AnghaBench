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
struct oxygen {struct dg* model_data; } ;
struct dg {scalar_t__ output_sel; int /*<<< orphan*/ * cs4245_shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4245_A_OUT_SEL_DAC ; 
 int /*<<< orphan*/  CS4245_A_OUT_SEL_MASK ; 
 size_t CS4245_SIGNAL_SEL ; 
 int /*<<< orphan*/  GPIO_HP_REAR ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 scalar_t__ PLAYBACK_DST_HP ; 
 scalar_t__ PLAYBACK_DST_HP_FP ; 
 int cs4245_write_spi (struct oxygen*,size_t) ; 
 int /*<<< orphan*/  oxygen_clear_bits8 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_set_bits8 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int output_select_apply(struct oxygen *chip)
{
	struct dg *data = chip->model_data;

	data->cs4245_shadow[CS4245_SIGNAL_SEL] &= ~CS4245_A_OUT_SEL_MASK;
	if (data->output_sel == PLAYBACK_DST_HP) {
		/* mute FP (aux output) amplifier, switch rear jack to CS4245 */
		oxygen_set_bits8(chip, OXYGEN_GPIO_DATA, GPIO_HP_REAR);
	} else if (data->output_sel == PLAYBACK_DST_HP_FP) {
		/*
		 * Unmute FP amplifier, switch rear jack to CS4361;
		 * I2S channels 2,3,4 should be inactive.
		 */
		oxygen_clear_bits8(chip, OXYGEN_GPIO_DATA, GPIO_HP_REAR);
		data->cs4245_shadow[CS4245_SIGNAL_SEL] |= CS4245_A_OUT_SEL_DAC;
	} else {
		/*
		 * 2.0, 4.0, 5.1: switch to CS4361, mute FP amp.,
		 * and change playback routing.
		 */
		oxygen_clear_bits8(chip, OXYGEN_GPIO_DATA, GPIO_HP_REAR);
	}
	return cs4245_write_spi(chip, CS4245_SIGNAL_SEL);
}