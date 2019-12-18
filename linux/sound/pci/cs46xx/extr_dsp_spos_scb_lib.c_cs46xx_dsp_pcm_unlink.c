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
struct snd_cs46xx {int /*<<< orphan*/  reg_lock; TYPE_1__* dsp_spos_instance; } ;
struct dsp_pcm_channel_descriptor {int unlinked; int /*<<< orphan*/  pcm_reader_scb; int /*<<< orphan*/  active; } ;
struct TYPE_2__ {scalar_t__ npcm_channels; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  _dsp_unlink_scb (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cs46xx_dsp_pcm_unlink (struct snd_cs46xx * chip,
			   struct dsp_pcm_channel_descriptor * pcm_channel)
{
	unsigned long flags;

	if (snd_BUG_ON(!pcm_channel->active ||
		       chip->dsp_spos_instance->npcm_channels <= 0))
		return -EIO;

	spin_lock_irqsave(&chip->reg_lock, flags);
	if (pcm_channel->unlinked) {
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		return -EIO;
	}

	pcm_channel->unlinked = 1;

	_dsp_unlink_scb (chip,pcm_channel->pcm_reader_scb);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	return 0;
}