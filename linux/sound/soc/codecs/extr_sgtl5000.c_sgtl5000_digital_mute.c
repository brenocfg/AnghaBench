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
typedef  int /*<<< orphan*/  u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGTL5000_CHIP_DIG_POWER ; 
 int /*<<< orphan*/  SGTL5000_I2S_IN_POWERUP ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sgtl5000_digital_mute(struct snd_soc_dai *codec_dai, int mute)
{
	struct snd_soc_component *component = codec_dai->component;
	u16 i2s_pwr = SGTL5000_I2S_IN_POWERUP;

	/*
	 * During 'digital mute' do not mute DAC
	 * because LINE_IN would be muted aswell. We want to mute
	 * only I2S block - this can be done by powering it off
	 */
	snd_soc_component_update_bits(component, SGTL5000_CHIP_DIG_POWER,
			i2s_pwr, mute ? 0 : i2s_pwr);

	return 0;
}