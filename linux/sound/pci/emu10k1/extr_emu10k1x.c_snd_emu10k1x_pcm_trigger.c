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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int periods; struct emu10k1x_pcm* private_data; } ;
struct emu10k1x_pcm {int running; TYPE_1__* voice; } ;
struct emu10k1x {int dummy; } ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 int EINVAL ; 
 int INTE_CH_0_HALF_LOOP ; 
 int INTE_CH_0_LOOP ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  TRIGGER_CHANNEL ; 
 int TRIGGER_CHANNEL_0 ; 
 int /*<<< orphan*/  snd_emu10k1x_intr_disable (struct emu10k1x*,int) ; 
 int /*<<< orphan*/  snd_emu10k1x_intr_enable (struct emu10k1x*,int) ; 
 int snd_emu10k1x_ptr_read (struct emu10k1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1x_ptr_write (struct emu10k1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct emu10k1x* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_emu10k1x_pcm_trigger(struct snd_pcm_substream *substream,
				    int cmd)
{
	struct emu10k1x *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct emu10k1x_pcm *epcm = runtime->private_data;
	int channel = epcm->voice->number;
	int result = 0;

	/*
	dev_dbg(emu->card->dev,
		"trigger - emu10k1x = 0x%x, cmd = %i, pointer = %d\n",
		(int)emu, cmd, (int)substream->ops->pointer(substream));
	*/

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		if(runtime->periods == 2)
			snd_emu10k1x_intr_enable(emu, (INTE_CH_0_LOOP | INTE_CH_0_HALF_LOOP) << channel);
		else
			snd_emu10k1x_intr_enable(emu, INTE_CH_0_LOOP << channel);
		epcm->running = 1;
		snd_emu10k1x_ptr_write(emu, TRIGGER_CHANNEL, 0, snd_emu10k1x_ptr_read(emu, TRIGGER_CHANNEL, 0)|(TRIGGER_CHANNEL_0<<channel));
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		epcm->running = 0;
		snd_emu10k1x_intr_disable(emu, (INTE_CH_0_LOOP | INTE_CH_0_HALF_LOOP) << channel);
		snd_emu10k1x_ptr_write(emu, TRIGGER_CHANNEL, 0, snd_emu10k1x_ptr_read(emu, TRIGGER_CHANNEL, 0) & ~(TRIGGER_CHANNEL_0<<channel));
		break;
	default:
		result = -EINVAL;
		break;
	}
	return result;
}