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
struct snd_rme9652 {int /*<<< orphan*/  card_name; struct snd_pcm* pcm; } ;
struct snd_pcm {int /*<<< orphan*/  info_flags; int /*<<< orphan*/  name; struct snd_rme9652* private_data; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_INFO_JOINT_DUPLEX ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int snd_pcm_new (struct snd_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_rme9652_capture_ops ; 
 int /*<<< orphan*/  snd_rme9652_playback_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_rme9652_create_pcm(struct snd_card *card,
				  struct snd_rme9652 *rme9652)
{
	struct snd_pcm *pcm;
	int err;

	if ((err = snd_pcm_new(card,
			       rme9652->card_name,
			       0, 1, 1, &pcm)) < 0) {
		return err;
	}

	rme9652->pcm = pcm;
	pcm->private_data = rme9652;
	strcpy(pcm->name, rme9652->card_name);

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_rme9652_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_rme9652_capture_ops);

	pcm->info_flags = SNDRV_PCM_INFO_JOINT_DUPLEX;

	return 0;
}