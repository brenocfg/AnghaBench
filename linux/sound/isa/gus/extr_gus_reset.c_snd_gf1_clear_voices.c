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
struct TYPE_4__ {int default_voice_address; scalar_t__ enh_mode; scalar_t__ memory; TYPE_1__* syn_voices; } ;
struct snd_gus_card {int /*<<< orphan*/  reg_lock; TYPE_2__ gf1; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_GF1_VA_CURRENT ; 
 int /*<<< orphan*/  SNDRV_GF1_VA_END ; 
 int /*<<< orphan*/  SNDRV_GF1_VA_START ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_ACCUMULATOR ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_ADDRESS_CONTROL ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_MODE ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_PAN ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_VOLUME_CONTROL ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_VOLUME_END ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_VOLUME_RATE ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_VOLUME_START ; 
 int /*<<< orphan*/  SNDRV_GF1_VW_EFFECT_VOLUME ; 
 int /*<<< orphan*/  SNDRV_GF1_VW_EFFECT_VOLUME_FINAL ; 
 int /*<<< orphan*/  SNDRV_GF1_VW_FREQUENCY ; 
 int /*<<< orphan*/  SNDRV_GF1_VW_VOLUME ; 
 int /*<<< orphan*/  ULTRA_LFO_TREMOLO ; 
 int /*<<< orphan*/  ULTRA_LFO_VIBRATO ; 
 int /*<<< orphan*/  VFLG_DYNAMIC ; 
 int /*<<< orphan*/  snd_gf1_ctrl_stop (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_lfo_shutdown (struct snd_gus_card*,unsigned short,int /*<<< orphan*/ ) ; 
 int snd_gf1_read8 (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_select_voice (struct snd_gus_card*,unsigned short) ; 
 int /*<<< orphan*/  snd_gf1_write16 (struct snd_gus_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_gf1_write8 (struct snd_gus_card*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_gf1_write_addr (struct snd_gus_card*,int /*<<< orphan*/ ,unsigned int,unsigned short) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_gf1_clear_voices(struct snd_gus_card * gus, unsigned short v_min,
				 unsigned short v_max)
{
	unsigned long flags;
	unsigned int daddr;
	unsigned short i, w_16;

	daddr = gus->gf1.default_voice_address << 4;
	for (i = v_min; i <= v_max; i++) {
#if 0
		if (gus->gf1.syn_voices)
			gus->gf1.syn_voices[i].flags = ~VFLG_DYNAMIC;
#endif
		spin_lock_irqsave(&gus->reg_lock, flags);
		snd_gf1_select_voice(gus, i);
		snd_gf1_ctrl_stop(gus, SNDRV_GF1_VB_ADDRESS_CONTROL);	/* Voice Control Register = voice stop */
		snd_gf1_ctrl_stop(gus, SNDRV_GF1_VB_VOLUME_CONTROL);	/* Volume Ramp Control Register = ramp off */
		if (gus->gf1.enh_mode)
			snd_gf1_write8(gus, SNDRV_GF1_VB_MODE, gus->gf1.memory ? 0x02 : 0x82);	/* Deactivate voice */
		w_16 = snd_gf1_read8(gus, SNDRV_GF1_VB_ADDRESS_CONTROL) & 0x04;
		snd_gf1_write16(gus, SNDRV_GF1_VW_FREQUENCY, 0x400);
		snd_gf1_write_addr(gus, SNDRV_GF1_VA_START, daddr, w_16);
		snd_gf1_write_addr(gus, SNDRV_GF1_VA_END, daddr, w_16);
		snd_gf1_write8(gus, SNDRV_GF1_VB_VOLUME_START, 0);
		snd_gf1_write8(gus, SNDRV_GF1_VB_VOLUME_END, 0);
		snd_gf1_write8(gus, SNDRV_GF1_VB_VOLUME_RATE, 0);
		snd_gf1_write16(gus, SNDRV_GF1_VW_VOLUME, 0);
		snd_gf1_write_addr(gus, SNDRV_GF1_VA_CURRENT, daddr, w_16);
		snd_gf1_write8(gus, SNDRV_GF1_VB_PAN, 7);
		if (gus->gf1.enh_mode) {
			snd_gf1_write8(gus, SNDRV_GF1_VB_ACCUMULATOR, 0);
			snd_gf1_write16(gus, SNDRV_GF1_VW_EFFECT_VOLUME, 0);
			snd_gf1_write16(gus, SNDRV_GF1_VW_EFFECT_VOLUME_FINAL, 0);
		}
		spin_unlock_irqrestore(&gus->reg_lock, flags);
#if 0
		snd_gf1_lfo_shutdown(gus, i, ULTRA_LFO_VIBRATO);
		snd_gf1_lfo_shutdown(gus, i, ULTRA_LFO_TREMOLO);
#endif
	}
}