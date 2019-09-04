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
struct snd_soc_pcm_runtime {TYPE_1__* codec_dai; struct snd_soc_card* card; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dapm; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGTL5000_CHIP_ANA_POWER ; 
 int /*<<< orphan*/  SGTL5000_VAG_POWERUP ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int snd_fe_pi_audio_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_card *card = rtd->card;
	struct snd_soc_component *component = rtd->codec_dai->component;

	snd_soc_dapm_force_enable_pin(&card->dapm, "LO");
	snd_soc_dapm_force_enable_pin(&card->dapm, "ADC");
	snd_soc_dapm_force_enable_pin(&card->dapm, "DAC");
	snd_soc_dapm_force_enable_pin(&card->dapm, "HP");
	snd_soc_component_update_bits(component, SGTL5000_CHIP_ANA_POWER,
			SGTL5000_VAG_POWERUP, SGTL5000_VAG_POWERUP);

	return 0;
}