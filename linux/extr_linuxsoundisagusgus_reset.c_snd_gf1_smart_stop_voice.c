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
struct snd_gus_card {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_GF1_VB_ADDRESS_CONTROL ; 
 int /*<<< orphan*/  SNDRV_GF1_VB_VOLUME_CONTROL ; 
 int /*<<< orphan*/  snd_gf1_ctrl_stop (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gf1_select_voice (struct snd_gus_card*,unsigned short) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_gf1_smart_stop_voice(struct snd_gus_card * gus, unsigned short voice)
{
	unsigned long flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	snd_gf1_select_voice(gus, voice);
#if 0
	printk(KERN_DEBUG " -%i- smart stop voice - volume = 0x%x\n", voice, snd_gf1_i_read16(gus, SNDRV_GF1_VW_VOLUME));
#endif
	snd_gf1_ctrl_stop(gus, SNDRV_GF1_VB_ADDRESS_CONTROL);
	snd_gf1_ctrl_stop(gus, SNDRV_GF1_VB_VOLUME_CONTROL);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
}