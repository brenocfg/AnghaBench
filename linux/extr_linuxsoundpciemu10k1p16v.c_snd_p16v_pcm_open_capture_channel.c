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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; int /*<<< orphan*/  private_free; struct snd_emu10k1_pcm* private_data; } ;
struct snd_emu10k1_voice {int number; int use; struct snd_emu10k1_pcm* epcm; struct snd_emu10k1* emu; } ;
struct snd_emu10k1_pcm {struct snd_pcm_substream* substream; struct snd_emu10k1* emu; } ;
struct snd_emu10k1 {struct snd_emu10k1_voice p16v_capture_voice; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 struct snd_emu10k1_pcm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_p16v_capture_hw ; 
 int /*<<< orphan*/  snd_p16v_pcm_free_substream ; 
 int snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_p16v_pcm_open_capture_channel(struct snd_pcm_substream *substream, int channel_id)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_emu10k1_voice *channel = &(emu->p16v_capture_voice);
	struct snd_emu10k1_pcm *epcm;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	epcm = kzalloc(sizeof(*epcm), GFP_KERNEL);
	/* dev_dbg(emu->card->dev, "epcm kcalloc: %p\n", epcm); */

	if (epcm == NULL)
		return -ENOMEM;
	epcm->emu = emu;
	epcm->substream = substream;
	/*
	dev_dbg(emu->card->dev, "epcm device=%d, channel_id=%d\n",
		   substream->pcm->device, channel_id);
	*/
	runtime->private_data = epcm;
	runtime->private_free = snd_p16v_pcm_free_substream;
  
	runtime->hw = snd_p16v_capture_hw;

	channel->emu = emu;
	channel->number = channel_id;

	channel->use=1;
#if 0 /* debug */
	dev_dbg(emu->card->dev,
		   "p16v: open channel_id=%d, channel=%p, use=0x%x\n",
		   channel_id, channel, channel->use);
	dev_dbg(emu->card->dev, "open:channel_id=%d, chip=%p, channel=%p\n",
	       channel_id, chip, channel);
#endif /* debug */
	/* channel->interrupt = snd_p16v_pcm_channel_interrupt; */
	channel->epcm = epcm;
	if ((err = snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		return err;

	return 0;
}