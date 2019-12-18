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
struct TYPE_2__ {scalar_t__ enh_mode; } ;
struct snd_gus_card {int /*<<< orphan*/  reg_lock; TYPE_1__ gf1; } ;

/* Variables and functions */
 unsigned short SNDRV_GF1_MIN_OFFSET ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_VOLUME_CONTROL ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_VOLUME_END ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_VOLUME_RATE ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_VOLUME_START ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  snd_gf1_clear_voices (struct snd_gus_card*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  snd_gf1_delay (struct snd_gus_card*) ; 
 int snd_gf1_read16 (struct snd_gus_card*,int) ; 
 int /*<<< orphan*/  snd_gf1_select_voice (struct snd_gus_card*,short) ; 
 int /*<<< orphan*/  snd_gf1_write8 (struct snd_gus_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_gf1_stop_voices(struct snd_gus_card * gus, unsigned short v_min, unsigned short v_max)
{
	unsigned long flags;
	short i, ramp_ok;
	unsigned short ramp_end;

	if (!in_interrupt()) {	/* this can't be done in interrupt */
		for (i = v_min, ramp_ok = 0; i <= v_max; i++) {
			spin_lock_irqsave(&gus->reg_lock, flags);
			snd_gf1_select_voice(gus, i);
			ramp_end = snd_gf1_read16(gus, 9) >> 8;
			if (ramp_end > SNDRV_GF1_MIN_OFFSET) {
				ramp_ok++;
				snd_gf1_write8(gus, SNDRV_GF1_VB_VOLUME_RATE, 20);	/* ramp rate */
				snd_gf1_write8(gus, SNDRV_GF1_VB_VOLUME_START, SNDRV_GF1_MIN_OFFSET);	/* ramp start */
				snd_gf1_write8(gus, SNDRV_GF1_VB_VOLUME_END, ramp_end);	/* ramp end */
				snd_gf1_write8(gus, SNDRV_GF1_VB_VOLUME_CONTROL, 0x40);	/* ramp down */
				if (gus->gf1.enh_mode) {
					snd_gf1_delay(gus);
					snd_gf1_write8(gus, SNDRV_GF1_VB_VOLUME_CONTROL, 0x40);
				}
			}
			spin_unlock_irqrestore(&gus->reg_lock, flags);
		}
		msleep_interruptible(50);
	}
	snd_gf1_clear_voices(gus, v_min, v_max);
}