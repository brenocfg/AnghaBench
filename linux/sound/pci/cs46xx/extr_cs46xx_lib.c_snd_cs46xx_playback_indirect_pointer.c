#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_2__* runtime; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct snd_cs46xx_pcm {int /*<<< orphan*/  pcm_rec; TYPE_1__ hw_buf; TYPE_4__* pcm_channel; } ;
struct snd_cs46xx {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_8__ {TYPE_3__* pcm_reader_scb; } ;
struct TYPE_7__ {int address; } ;
struct TYPE_6__ {struct snd_cs46xx_pcm* private_data; } ;

/* Variables and functions */
 int BA1_PBA ; 
 int /*<<< orphan*/  ENXIO ; 
 scalar_t__ snd_BUG_ON (int) ; 
 size_t snd_cs46xx_peek (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  snd_pcm_indirect_playback_pointer (struct snd_pcm_substream*,int /*<<< orphan*/ *,size_t) ; 
 struct snd_cs46xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_cs46xx_playback_indirect_pointer(struct snd_pcm_substream *substream)
{
	struct snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	size_t ptr;
	struct snd_cs46xx_pcm *cpcm = substream->runtime->private_data;

#ifdef CONFIG_SND_CS46XX_NEW_DSP
	if (snd_BUG_ON(!cpcm->pcm_channel))
		return -ENXIO;
	ptr = snd_cs46xx_peek(chip, (cpcm->pcm_channel->pcm_reader_scb->address + 2) << 2);
#else
	ptr = snd_cs46xx_peek(chip, BA1_PBA);
#endif
	ptr -= cpcm->hw_buf.addr;
	return snd_pcm_indirect_playback_pointer(substream, &cpcm->pcm_rec, ptr);
}