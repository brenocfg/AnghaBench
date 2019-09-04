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
struct snd_emu10k1_pcm_mixer {int** send_routing; int** send_volume; int* attn; struct snd_emu10k1_pcm* epcm; } ;
struct snd_emu10k1_pcm {struct snd_pcm_substream* substream; int /*<<< orphan*/  type; struct snd_emu10k1* emu; } ;
struct snd_emu10k1 {struct snd_emu10k1_pcm_mixer* efx_pcm_mixer; struct snd_pcm_substream* pcm_playback_efx_substream; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NUM_EFX_PLAYBACK ; 
 int /*<<< orphan*/  PLAYBACK_EFX ; 
 struct snd_emu10k1_pcm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int***,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_emu10k1_efx_playback ; 
 int /*<<< orphan*/  snd_emu10k1_pcm_efx_mixer_notify (struct snd_emu10k1*,int,int) ; 
 int /*<<< orphan*/  snd_emu10k1_pcm_free_substream ; 
 struct snd_emu10k1* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_emu10k1_efx_playback_open(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_emu10k1_pcm *epcm;
	struct snd_emu10k1_pcm_mixer *mix;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int i;

	epcm = kzalloc(sizeof(*epcm), GFP_KERNEL);
	if (epcm == NULL)
		return -ENOMEM;
	epcm->emu = emu;
	epcm->type = PLAYBACK_EFX;
	epcm->substream = substream;
	
	emu->pcm_playback_efx_substream = substream;

	runtime->private_data = epcm;
	runtime->private_free = snd_emu10k1_pcm_free_substream;
	runtime->hw = snd_emu10k1_efx_playback;
	
	for (i = 0; i < NUM_EFX_PLAYBACK; i++) {
		mix = &emu->efx_pcm_mixer[i];
		mix->send_routing[0][0] = i;
		memset(&mix->send_volume, 0, sizeof(mix->send_volume));
		mix->send_volume[0][0] = 255;
		mix->attn[0] = 0xffff;
		mix->epcm = epcm;
		snd_emu10k1_pcm_efx_mixer_notify(emu, i, 1);
	}
	return 0;
}