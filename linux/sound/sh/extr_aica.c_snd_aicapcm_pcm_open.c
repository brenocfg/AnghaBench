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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; TYPE_1__* pcm; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;
struct snd_card_aica {scalar_t__ dma_check; scalar_t__ current_period; scalar_t__ clicks; struct aica_channel* channel; int /*<<< orphan*/  master_volume; } ;
struct aica_channel {int pan; scalar_t__ flags; scalar_t__ pos; int /*<<< orphan*/  vol; int /*<<< orphan*/  cmd; int /*<<< orphan*/  sfmt; } ;
struct TYPE_2__ {struct snd_card_aica* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AICA_CMD_START ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SM_8BIT ; 
 int /*<<< orphan*/  enable ; 
 struct aica_channel* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_aica_playback_hw ; 
 int /*<<< orphan*/  spu_enable () ; 

__attribute__((used)) static int snd_aicapcm_pcm_open(struct snd_pcm_substream
				*substream)
{
	struct snd_pcm_runtime *runtime;
	struct aica_channel *channel;
	struct snd_card_aica *dreamcastcard;
	if (!enable)
		return -ENOENT;
	dreamcastcard = substream->pcm->private_data;
	channel = kmalloc(sizeof(struct aica_channel), GFP_KERNEL);
	if (!channel)
		return -ENOMEM;
	/* set defaults for channel */
	channel->sfmt = SM_8BIT;
	channel->cmd = AICA_CMD_START;
	channel->vol = dreamcastcard->master_volume;
	channel->pan = 0x80;
	channel->pos = 0;
	channel->flags = 0;	/* default to mono */
	dreamcastcard->channel = channel;
	runtime = substream->runtime;
	runtime->hw = snd_pcm_aica_playback_hw;
	spu_enable();
	dreamcastcard->clicks = 0;
	dreamcastcard->current_period = 0;
	dreamcastcard->dma_check = 0;
	return 0;
}