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
 int /*<<< orphan*/  AC97_ALC850_JACK_SELECT ; 
 int /*<<< orphan*/  AC97_ALC850_MISC1 ; 
 int /*<<< orphan*/  AC97_ALC850_MULTICH ; 
 int alc850_is_aux_back_surround (struct snd_ac97*) ; 
 int is_shared_clfeout (struct snd_ac97*) ; 
 int is_shared_surrout (struct snd_ac97*) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void alc850_update_jacks(struct snd_ac97 *ac97)
{
	int shared;
	int aux_is_back_surround;
	
	/* shared Line-In / Surround Out */
	shared = is_shared_surrout(ac97);
	/* SURR 1kOhm (bit4), Amp (bit5) */
	snd_ac97_update_bits(ac97, AC97_ALC850_MISC1, (1<<4)|(1<<5),
			     shared ? (1<<5) : (1<<4));
	/* LINE-IN = 0, SURROUND = 2 */
	snd_ac97_update_bits(ac97, AC97_ALC850_JACK_SELECT, 7 << 12,
			     shared ? (2<<12) : (0<<12));
	/* update shared Mic In / Center/LFE Out */
	shared = is_shared_clfeout(ac97);
	/* Vref disable (bit12), 1kOhm (bit13) */
	snd_ac97_update_bits(ac97, AC97_ALC850_MISC1, (1<<12)|(1<<13),
			     shared ? (1<<12) : (1<<13));
	/* MIC-IN = 1, CENTER-LFE = 5 */
	snd_ac97_update_bits(ac97, AC97_ALC850_JACK_SELECT, 7 << 4,
			     shared ? (5<<4) : (1<<4));

	aux_is_back_surround = alc850_is_aux_back_surround(ac97);
	/* Aux is Back Surround */
	snd_ac97_update_bits(ac97, AC97_ALC850_MULTICH, 1 << 10,
				 aux_is_back_surround ? (1<<10) : (0<<10));
}