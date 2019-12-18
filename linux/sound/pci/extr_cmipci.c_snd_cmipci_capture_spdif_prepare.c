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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct cmipci {int /*<<< orphan*/ * channel; int /*<<< orphan*/  reg_lock; scalar_t__ can_96k; } ;
struct TYPE_2__ {int rate; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CAPTURE_SPDF ; 
 size_t CM_CH_CAPT ; 
 int /*<<< orphan*/  CM_DBLSPDS ; 
 int /*<<< orphan*/  CM_REG_CHFORMAT ; 
 int /*<<< orphan*/  CM_REG_FUNCTRL1 ; 
 int /*<<< orphan*/  CM_REG_MISC_CTRL ; 
 int /*<<< orphan*/  CM_SPD32SEL ; 
 int /*<<< orphan*/  snd_cmipci_clear_bit (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_cmipci_pcm_prepare (struct cmipci*,int /*<<< orphan*/ *,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_cmipci_set_bit (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 
 struct cmipci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cmipci_capture_spdif_prepare(struct snd_pcm_substream *substream)
{
	struct cmipci *cm = snd_pcm_substream_chip(substream);

	spin_lock_irq(&cm->reg_lock);
	snd_cmipci_set_bit(cm, CM_REG_FUNCTRL1, CM_CAPTURE_SPDF);
	if (cm->can_96k) {
		if (substream->runtime->rate > 48000)
			snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_DBLSPDS);
		else
			snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_DBLSPDS);
	}
	if (snd_pcm_format_width(substream->runtime->format) > 16)
		snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);
	else
		snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);

	spin_unlock_irq(&cm->reg_lock);

	return snd_cmipci_pcm_prepare(cm, &cm->channel[CM_CH_CAPT], substream);
}