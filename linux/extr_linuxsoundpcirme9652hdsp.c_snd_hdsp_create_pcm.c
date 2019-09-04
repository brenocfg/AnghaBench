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
struct snd_pcm {int /*<<< orphan*/  info_flags; int /*<<< orphan*/  name; struct hdsp* private_data; } ;
struct snd_card {int dummy; } ;
struct hdsp {int /*<<< orphan*/  card_name; struct snd_pcm* pcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_INFO_JOINT_DUPLEX ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_hdsp_capture_ops ; 
 int /*<<< orphan*/  snd_hdsp_playback_ops ; 
 int snd_pcm_new (struct snd_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_hdsp_create_pcm(struct snd_card *card, struct hdsp *hdsp)
{
	struct snd_pcm *pcm;
	int err;

	if ((err = snd_pcm_new(card, hdsp->card_name, 0, 1, 1, &pcm)) < 0)
		return err;

	hdsp->pcm = pcm;
	pcm->private_data = hdsp;
	strcpy(pcm->name, hdsp->card_name);

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_hdsp_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_hdsp_capture_ops);

	pcm->info_flags = SNDRV_PCM_INFO_JOINT_DUPLEX;

	return 0;
}