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
struct snd_pcm_substream {size_t number; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; int /*<<< orphan*/  private_free; struct snd_emu10k1_pcm* private_data; } ;
struct snd_emu10k1_pcm_mixer {int** send_routing; int** send_volume; int* attn; struct snd_emu10k1_pcm* epcm; } ;
struct snd_emu10k1_pcm {struct snd_pcm_substream* substream; int /*<<< orphan*/  type; struct snd_emu10k1* emu; } ;
struct TYPE_4__ {scalar_t__ internal_clock; } ;
struct snd_emu10k1 {struct snd_emu10k1_pcm_mixer* pcm_mixer; TYPE_2__ emu1010; TYPE_1__* card_capabilities; } ;
struct TYPE_3__ {scalar_t__ emu_model; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PLAYBACK_EMUVOICE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  kfree (struct snd_emu10k1_pcm*) ; 
 struct snd_emu10k1_pcm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int***,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_emu10k1_pcm_free_substream ; 
 int /*<<< orphan*/  snd_emu10k1_pcm_mixer_notify (struct snd_emu10k1*,size_t,int) ; 
 int /*<<< orphan*/  snd_emu10k1_playback ; 
 int snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_minmax (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_rule_noresample (struct snd_pcm_runtime*,int) ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_emu10k1_playback_open(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_emu10k1_pcm *epcm;
	struct snd_emu10k1_pcm_mixer *mix;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int i, err, sample_rate;

	epcm = kzalloc(sizeof(*epcm), GFP_KERNEL);
	if (epcm == NULL)
		return -ENOMEM;
	epcm->emu = emu;
	epcm->type = PLAYBACK_EMUVOICE;
	epcm->substream = substream;
	runtime->private_data = epcm;
	runtime->private_free = snd_emu10k1_pcm_free_substream;
	runtime->hw = snd_emu10k1_playback;
	if ((err = snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS)) < 0) {
		kfree(epcm);
		return err;
	}
	if ((err = snd_pcm_hw_constraint_minmax(runtime, SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 256, UINT_MAX)) < 0) {
		kfree(epcm);
		return err;
	}
	if (emu->card_capabilities->emu_model && emu->emu1010.internal_clock == 0)
		sample_rate = 44100;
	else
		sample_rate = 48000;
	err = snd_pcm_hw_rule_noresample(runtime, sample_rate);
	if (err < 0) {
		kfree(epcm);
		return err;
	}
	mix = &emu->pcm_mixer[substream->number];
	for (i = 0; i < 4; i++)
		mix->send_routing[0][i] = mix->send_routing[1][i] = mix->send_routing[2][i] = i;
	memset(&mix->send_volume, 0, sizeof(mix->send_volume));
	mix->send_volume[0][0] = mix->send_volume[0][1] =
	mix->send_volume[1][0] = mix->send_volume[2][1] = 255;
	mix->attn[0] = mix->attn[1] = mix->attn[2] = 0xffff;
	mix->epcm = epcm;
	snd_emu10k1_pcm_mixer_notify(emu, substream->number, 1);
	return 0;
}