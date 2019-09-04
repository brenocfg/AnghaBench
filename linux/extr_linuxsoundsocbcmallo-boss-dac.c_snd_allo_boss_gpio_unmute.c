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
struct snd_soc_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mute_gpio ; 

__attribute__((used)) static void snd_allo_boss_gpio_unmute(struct snd_soc_card *card)
{
	if (mute_gpio)
		gpiod_set_value_cansleep(mute_gpio, 0);
}