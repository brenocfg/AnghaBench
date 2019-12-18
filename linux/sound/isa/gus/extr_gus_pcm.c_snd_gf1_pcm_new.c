#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_substream* next; } ;
struct snd_pcm {scalar_t__ name; int /*<<< orphan*/  id; TYPE_1__* streams; int /*<<< orphan*/  info_flags; int /*<<< orphan*/  dev_subclass; struct snd_gus_card* private_data; } ;
struct TYPE_6__ {int index; } ;
struct snd_kcontrol {TYPE_3__ id; } ;
struct TYPE_5__ {int pcm_channels; int dma1; int dma2; } ;
struct snd_gus_card {int revision; scalar_t__ codec_flag; struct snd_pcm* pcm; scalar_t__ interwave; TYPE_2__ gf1; int /*<<< orphan*/  ace_flag; int /*<<< orphan*/  ess_flag; struct snd_card* card; } ;
struct snd_card {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  SNDRV_PCM_INFO_HALF_DUPLEX ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SNDRV_PCM_SUBCLASS_GENERIC_MIX ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_gus_card*) ; 
 int /*<<< orphan*/  snd_gf1_pcm_capture_ops ; 
 int /*<<< orphan*/  snd_gf1_pcm_playback_ops ; 
 int /*<<< orphan*/  snd_gf1_pcm_volume_control ; 
 int /*<<< orphan*/  snd_gf1_pcm_volume_control1 ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_pcm_new (struct snd_card*,char*,int,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  strcat (scalar_t__,char*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (scalar_t__) ; 

int snd_gf1_pcm_new(struct snd_gus_card *gus, int pcm_dev, int control_index)
{
	struct snd_card *card;
	struct snd_kcontrol *kctl;
	struct snd_pcm *pcm;
	struct snd_pcm_substream *substream;
	int capture, err;

	card = gus->card;
	capture = !gus->interwave && !gus->ess_flag && !gus->ace_flag ? 1 : 0;
	err = snd_pcm_new(card,
			  gus->interwave ? "AMD InterWave" : "GF1",
			  pcm_dev,
			  gus->gf1.pcm_channels / 2,
			  capture,
			  &pcm);
	if (err < 0)
		return err;
	pcm->private_data = gus;
	/* playback setup */
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_gf1_pcm_playback_ops);

	for (substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream; substream; substream = substream->next)
		snd_pcm_lib_preallocate_pages(substream, SNDRV_DMA_TYPE_DEV,
					      card->dev,
					      64*1024, gus->gf1.dma1 > 3 ? 128*1024 : 64*1024);
	
	pcm->info_flags = 0;
	pcm->dev_subclass = SNDRV_PCM_SUBCLASS_GENERIC_MIX;
	if (capture) {
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_gf1_pcm_capture_ops);
		if (gus->gf1.dma2 == gus->gf1.dma1)
			pcm->info_flags |= SNDRV_PCM_INFO_HALF_DUPLEX;
		snd_pcm_lib_preallocate_pages(pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream,
					      SNDRV_DMA_TYPE_DEV, card->dev,
					      64*1024, gus->gf1.dma2 > 3 ? 128*1024 : 64*1024);
	}
	strcpy(pcm->name, pcm->id);
	if (gus->interwave) {
		sprintf(pcm->name + strlen(pcm->name), " rev %c", gus->revision + 'A');
	}
	strcat(pcm->name, " (synth)");
	gus->pcm = pcm;

	if (gus->codec_flag)
		kctl = snd_ctl_new1(&snd_gf1_pcm_volume_control1, gus);
	else
		kctl = snd_ctl_new1(&snd_gf1_pcm_volume_control, gus);
	if ((err = snd_ctl_add(card, kctl)) < 0)
		return err;
	kctl->id.index = control_index;

	return 0;
}