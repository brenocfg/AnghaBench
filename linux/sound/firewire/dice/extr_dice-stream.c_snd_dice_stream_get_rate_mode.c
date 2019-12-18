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
struct snd_dice {int clock_caps; } ;
typedef  enum snd_dice_rate_mode { ____Placeholder_snd_dice_rate_mode } snd_dice_rate_mode ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int BIT (int) ; 
 int EINVAL ; 
#define  SND_DICE_RATE_MODE_HIGH 130 
#define  SND_DICE_RATE_MODE_LOW 129 
#define  SND_DICE_RATE_MODE_MIDDLE 128 
 unsigned int* snd_dice_rates ; 

int snd_dice_stream_get_rate_mode(struct snd_dice *dice, unsigned int rate,
				  enum snd_dice_rate_mode *mode)
{
	/* Corresponding to each entry in snd_dice_rates. */
	static const enum snd_dice_rate_mode modes[] = {
		[0] = SND_DICE_RATE_MODE_LOW,
		[1] = SND_DICE_RATE_MODE_LOW,
		[2] = SND_DICE_RATE_MODE_LOW,
		[3] = SND_DICE_RATE_MODE_MIDDLE,
		[4] = SND_DICE_RATE_MODE_MIDDLE,
		[5] = SND_DICE_RATE_MODE_HIGH,
		[6] = SND_DICE_RATE_MODE_HIGH,
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(snd_dice_rates); i++) {
		if (!(dice->clock_caps & BIT(i)))
			continue;
		if (snd_dice_rates[i] != rate)
			continue;

		*mode = modes[i];
		return 0;
	}

	return -EINVAL;
}