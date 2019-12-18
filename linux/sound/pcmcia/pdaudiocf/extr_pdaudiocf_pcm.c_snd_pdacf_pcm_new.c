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
struct snd_pdacf {int /*<<< orphan*/  ak4117; struct snd_pcm* pcm; TYPE_2__* card; } ;
struct snd_pcm {int nonatomic; TYPE_1__* streams; int /*<<< orphan*/  name; scalar_t__ info_flags; struct snd_pdacf* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  shortname; } ;
struct TYPE_3__ {int /*<<< orphan*/  substream; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  pdacf_pcm_capture_ops ; 
 int snd_ak4117_build (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_new (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_pdacf_pcm_new(struct snd_pdacf *chip)
{
	struct snd_pcm *pcm;
	int err;

	err = snd_pcm_new(chip->card, "PDAudioCF", 0, 0, 1, &pcm);
	if (err < 0)
		return err;
		
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &pdacf_pcm_capture_ops);

	pcm->private_data = chip;
	pcm->info_flags = 0;
	pcm->nonatomic = true;
	strcpy(pcm->name, chip->card->shortname);
	chip->pcm = pcm;
	
	err = snd_ak4117_build(chip->ak4117, pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream);
	if (err < 0)
		return err;

	return 0;
}