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
struct TYPE_2__ {int rate_min; int rate_max; int channels_min; int /*<<< orphan*/  rates; } ;
struct snd_pcm_runtime {TYPE_1__ hw; int /*<<< orphan*/  private_free; struct snd_emu10k1_pcm* private_data; } ;
struct snd_emu10k1_pcm {int capture_ipr; int /*<<< orphan*/  capture_idx_reg; int /*<<< orphan*/  capture_bs_reg; int /*<<< orphan*/  capture_ba_reg; int /*<<< orphan*/  capture_inte; struct snd_pcm_substream* substream; int /*<<< orphan*/  type; struct snd_emu10k1* emu; } ;
struct snd_emu10k1 {struct snd_pcm_substream* pcm_capture_mic_substream; int /*<<< orphan*/  capture_mic_interrupt; scalar_t__ audigy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_MICIDX ; 
 int /*<<< orphan*/  CAPTURE_AC97MIC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTE_MICBUFENABLE ; 
 int IPR_MICBUFFULL ; 
 int IPR_MICBUFHALFFULL ; 
 int /*<<< orphan*/  MICBA ; 
 int /*<<< orphan*/  MICBS ; 
 int /*<<< orphan*/  MICIDX ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_8000 ; 
 int /*<<< orphan*/  hw_constraints_capture_period_sizes ; 
 struct snd_emu10k1_pcm* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ snd_emu10k1_capture ; 
 int /*<<< orphan*/  snd_emu10k1_pcm_ac97mic_interrupt ; 
 int /*<<< orphan*/  snd_emu10k1_pcm_free_substream ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_emu10k1_capture_mic_open(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_emu10k1_pcm *epcm;
	struct snd_pcm_runtime *runtime = substream->runtime;

	epcm = kzalloc(sizeof(*epcm), GFP_KERNEL);
	if (epcm == NULL)
		return -ENOMEM;
	epcm->emu = emu;
	epcm->type = CAPTURE_AC97MIC;
	epcm->substream = substream;
	epcm->capture_ipr = IPR_MICBUFFULL|IPR_MICBUFHALFFULL;
	epcm->capture_inte = INTE_MICBUFENABLE;
	epcm->capture_ba_reg = MICBA;
	epcm->capture_bs_reg = MICBS;
	epcm->capture_idx_reg = emu->audigy ? A_MICIDX : MICIDX;
	substream->runtime->private_data = epcm;
	substream->runtime->private_free = snd_emu10k1_pcm_free_substream;
	runtime->hw = snd_emu10k1_capture;
	runtime->hw.rates = SNDRV_PCM_RATE_8000;
	runtime->hw.rate_min = runtime->hw.rate_max = 8000;
	runtime->hw.channels_min = 1;
	emu->capture_mic_interrupt = snd_emu10k1_pcm_ac97mic_interrupt;
	emu->pcm_capture_mic_substream = substream;
	snd_pcm_hw_constraint_list(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, &hw_constraints_capture_period_sizes);
	return 0;
}