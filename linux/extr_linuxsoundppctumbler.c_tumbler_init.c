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
struct snd_pmac {struct pmac_tumbler* mixer_data; } ;
struct pmac_tumbler {int headphone_irq; int lineout_irq; int /*<<< orphan*/  line_detect; int /*<<< orphan*/  hp_detect; int /*<<< orphan*/  line_mute; int /*<<< orphan*/  hp_mute; int /*<<< orphan*/  amp_mute; int /*<<< orphan*/  audio_reset; } ;

/* Variables and functions */
 scalar_t__ IS_G4DA ; 
 int tumbler_find_device (char*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tumbler_reset_audio (struct snd_pmac*) ; 

__attribute__((used)) static int tumbler_init(struct snd_pmac *chip)
{
	int irq;
	struct pmac_tumbler *mix = chip->mixer_data;

	if (tumbler_find_device("audio-hw-reset",
				"platform-do-hw-reset",
				&mix->audio_reset, 0) < 0)
		tumbler_find_device("hw-reset",
				    "platform-do-hw-reset",
				    &mix->audio_reset, 1);
	if (tumbler_find_device("amp-mute",
				"platform-do-amp-mute",
				&mix->amp_mute, 0) < 0)
		tumbler_find_device("amp-mute",
				    "platform-do-amp-mute",
				    &mix->amp_mute, 1);
	if (tumbler_find_device("headphone-mute",
				"platform-do-headphone-mute",
				&mix->hp_mute, 0) < 0)
		tumbler_find_device("headphone-mute",
				    "platform-do-headphone-mute",
				    &mix->hp_mute, 1);
	if (tumbler_find_device("line-output-mute",
				"platform-do-lineout-mute",
				&mix->line_mute, 0) < 0)
		tumbler_find_device("line-output-mute",
				   "platform-do-lineout-mute",
				    &mix->line_mute, 1);
	irq = tumbler_find_device("headphone-detect",
				  NULL, &mix->hp_detect, 0);
	if (irq <= 0)
		irq = tumbler_find_device("headphone-detect",
					  NULL, &mix->hp_detect, 1);
	if (irq <= 0)
		irq = tumbler_find_device("keywest-gpio15",
					  NULL, &mix->hp_detect, 1);
	mix->headphone_irq = irq;
 	irq = tumbler_find_device("line-output-detect",
				  NULL, &mix->line_detect, 0);
	if (irq <= 0)
		irq = tumbler_find_device("line-output-detect",
					  NULL, &mix->line_detect, 1);
	if (IS_G4DA && irq <= 0)
		irq = tumbler_find_device("keywest-gpio16",
					  NULL, &mix->line_detect, 1);
	mix->lineout_irq = irq;

	tumbler_reset_audio(chip);
  
	return 0;
}