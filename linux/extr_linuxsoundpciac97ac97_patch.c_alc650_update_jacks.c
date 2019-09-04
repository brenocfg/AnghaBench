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
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_ALC650_CLOCK ; 
 int /*<<< orphan*/  AC97_ALC650_GPIO_STATUS ; 
 int /*<<< orphan*/  AC97_ALC650_MULTICH ; 
 int is_shared_clfeout (struct snd_ac97*) ; 
 int is_shared_surrout (struct snd_ac97*) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void alc650_update_jacks(struct snd_ac97 *ac97)
{
	int shared;
	
	/* shared Line-In / Surround Out */
	shared = is_shared_surrout(ac97);
	snd_ac97_update_bits(ac97, AC97_ALC650_MULTICH, 1 << 9,
			     shared ? (1 << 9) : 0);
	/* update shared Mic In / Center/LFE Out */
	shared = is_shared_clfeout(ac97);
	/* disable/enable vref */
	snd_ac97_update_bits(ac97, AC97_ALC650_CLOCK, 1 << 12,
			     shared ? (1 << 12) : 0);
	/* turn on/off center-on-mic */
	snd_ac97_update_bits(ac97, AC97_ALC650_MULTICH, 1 << 10,
			     shared ? (1 << 10) : 0);
	/* GPIO0 high for mic */
	snd_ac97_update_bits(ac97, AC97_ALC650_GPIO_STATUS, 0x100,
			     shared ? 0 : 0x100);
}