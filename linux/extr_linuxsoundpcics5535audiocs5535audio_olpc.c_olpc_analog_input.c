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
struct snd_ac97 {TYPE_2__* bus; } ;
struct TYPE_4__ {TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AC97_AD_HPFD_SHIFT ; 
 int /*<<< orphan*/  AC97_AD_TEST2 ; 
 int /*<<< orphan*/  OLPC_GPIO_MIC_AC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  machine_is_olpc () ; 
 int snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int,int) ; 

void olpc_analog_input(struct snd_ac97 *ac97, int on)
{
	int err;

	if (!machine_is_olpc())
		return;

	/* update the High Pass Filter (via AC97_AD_TEST2) */
	err = snd_ac97_update_bits(ac97, AC97_AD_TEST2,
			1 << AC97_AD_HPFD_SHIFT, on << AC97_AD_HPFD_SHIFT);
	if (err < 0) {
		dev_err(ac97->bus->card->dev,
			"setting High Pass Filter - %d\n", err);
		return;
	}

	/* set Analog Input through GPIO */
	gpio_set_value(OLPC_GPIO_MIC_AC, on);
}