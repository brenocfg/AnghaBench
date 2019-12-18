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
struct dg {int output_sel; } ;

/* Variables and functions */
 unsigned int OXYGEN_PLAY_DAC0_SOURCE_MASK ; 
 int /*<<< orphan*/  OXYGEN_PLAY_DAC0_SOURCE_SHIFT ; 
 int /*<<< orphan*/  OXYGEN_PLAY_DAC1_SOURCE_MASK ; 
 int /*<<< orphan*/  OXYGEN_PLAY_DAC1_SOURCE_SHIFT ; 
 int /*<<< orphan*/  OXYGEN_PLAY_DAC2_SOURCE_MASK ; 
 int /*<<< orphan*/  OXYGEN_PLAY_DAC2_SOURCE_SHIFT ; 
 int /*<<< orphan*/  OXYGEN_PLAY_DAC3_SOURCE_MASK ; 
 int /*<<< orphan*/  OXYGEN_PLAY_DAC3_SOURCE_SHIFT ; 
 int OXYGEN_PLAY_MUTE01 ; 
 int OXYGEN_PLAY_MUTE23 ; 
 int OXYGEN_PLAY_MUTE45 ; 
 int OXYGEN_PLAY_MUTE67 ; 
 int /*<<< orphan*/  OXYGEN_PLAY_MUTE_MASK ; 
 int /*<<< orphan*/  OXYGEN_PLAY_ROUTING ; 
#define  PLAYBACK_DST_HP 130 
#define  PLAYBACK_DST_HP_FP 129 
#define  PLAYBACK_DST_MULTICH 128 
 int /*<<< orphan*/  oxygen_write8_masked (struct oxygen*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned int shift_bits (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int adjust_dg_dac_routing(struct oxygen *chip,
					  unsigned int play_routing)
{
	struct dg *data = chip->model_data;

	switch (data->output_sel) {
	case PLAYBACK_DST_HP:
	case PLAYBACK_DST_HP_FP:
		oxygen_write8_masked(chip, OXYGEN_PLAY_ROUTING,
			OXYGEN_PLAY_MUTE23 | OXYGEN_PLAY_MUTE45 |
			OXYGEN_PLAY_MUTE67, OXYGEN_PLAY_MUTE_MASK);
		break;
	case PLAYBACK_DST_MULTICH:
		oxygen_write8_masked(chip, OXYGEN_PLAY_ROUTING,
			OXYGEN_PLAY_MUTE01, OXYGEN_PLAY_MUTE_MASK);
		break;
	}
	return (play_routing & OXYGEN_PLAY_DAC0_SOURCE_MASK) |
	       shift_bits(play_routing,
			  OXYGEN_PLAY_DAC2_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC1_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC1_SOURCE_MASK) |
	       shift_bits(play_routing,
			  OXYGEN_PLAY_DAC1_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC2_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC2_SOURCE_MASK) |
	       shift_bits(play_routing,
			  OXYGEN_PLAY_DAC0_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC3_SOURCE_SHIFT,
			  OXYGEN_PLAY_DAC3_SOURCE_MASK);
}