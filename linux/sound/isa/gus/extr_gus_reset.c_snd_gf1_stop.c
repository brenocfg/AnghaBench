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
struct snd_gus_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_GF1_GB_RESET ; 
 int /*<<< orphan*/  SNDRV_GF1_GB_SOUND_BLASTER_CONTROL ; 
 int /*<<< orphan*/  snd_gf1_i_write8 (struct snd_gus_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_gf1_lfo_done (struct snd_gus_card*) ; 
 int /*<<< orphan*/  snd_gf1_mem_done (struct snd_gus_card*) ; 
 int /*<<< orphan*/  snd_gf1_stop_voices (struct snd_gus_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_gf1_timers_done (struct snd_gus_card*) ; 

int snd_gf1_stop(struct snd_gus_card * gus)
{
	snd_gf1_i_write8(gus, SNDRV_GF1_GB_SOUND_BLASTER_CONTROL, 0); /* stop all timers */
	snd_gf1_stop_voices(gus, 0, 31);		/* stop all voices */
	snd_gf1_i_write8(gus, SNDRV_GF1_GB_RESET, 1);	/* disable IRQ & DAC */
	snd_gf1_timers_done(gus);
	snd_gf1_mem_done(gus);
#if 0
	snd_gf1_lfo_done(gus);
#endif
	return 0;
}