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
struct snd_emu10k1_pcm {int capture_ipr; int /*<<< orphan*/  capture_idx_reg; int /*<<< orphan*/  capture_bs_reg; int /*<<< orphan*/  capture_ba_reg; int /*<<< orphan*/  capture_inte; struct snd_pcm_substream* substream; int /*<<< orphan*/  type; struct snd_emu10k1* emu; } ;
struct snd_emu10k1 {struct snd_pcm_substream* pcm_capture_substream; int /*<<< orphan*/  capture_interrupt; scalar_t__ audigy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADCBA ; 
 int /*<<< orphan*/  ADCBS ; 
 int /*<<< orphan*/  ADCIDX ; 
 int /*<<< orphan*/  A_ADCIDX ; 
 int /*<<< orphan*/  CAPTURE_AC97ADC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTE_ADCBUFENABLE ; 
 int IPR_ADCBUFFULL ; 
 int IPR_ADCBUFHALFFULL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  hw_constraints_capture_period_sizes ; 
 int /*<<< orphan*/  hw_constraints_capture_rates ; 
 struct snd_emu10k1_pcm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_capture ; 
 int /*<<< orphan*/  snd_emu10k1_pcm_ac97adc_interrupt ; 
 int /*<<< orphan*/  snd_emu10k1_pcm_free_substream ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_emu10k1_capture_open(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_emu10k1_pcm *epcm;

	epcm = kzalloc(sizeof(*epcm), GFP_KERNEL);
	if (epcm == NULL)
		return -ENOMEM;
	epcm->emu = emu;
	epcm->type = CAPTURE_AC97ADC;
	epcm->substream = substream;
	epcm->capture_ipr = IPR_ADCBUFFULL|IPR_ADCBUFHALFFULL;
	epcm->capture_inte = INTE_ADCBUFENABLE;
	epcm->capture_ba_reg = ADCBA;
	epcm->capture_bs_reg = ADCBS;
	epcm->capture_idx_reg = emu->audigy ? A_ADCIDX : ADCIDX;
	runtime->private_data = epcm;
	runtime->private_free = snd_emu10k1_pcm_free_substream;
	runtime->hw = snd_emu10k1_capture;
	emu->capture_interrupt = snd_emu10k1_pcm_ac97adc_interrupt;
	emu->pcm_capture_substream = substream;
	snd_pcm_hw_constraint_list(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, &hw_constraints_capture_period_sizes);
	snd_pcm_hw_constraint_list(runtime, 0, SNDRV_PCM_HW_PARAM_RATE, &hw_constraints_capture_rates);
	return 0;
}