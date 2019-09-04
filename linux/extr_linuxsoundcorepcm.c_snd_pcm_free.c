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
struct snd_pcm {int /*<<< orphan*/ * streams; int /*<<< orphan*/  (* private_free ) (struct snd_pcm*) ;int /*<<< orphan*/  internal; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  kfree (struct snd_pcm*) ; 
 int /*<<< orphan*/  n_unregister ; 
 int /*<<< orphan*/  pcm_call_notify (struct snd_pcm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_free_stream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_free_for_all (struct snd_pcm*) ; 
 int /*<<< orphan*/  stub1 (struct snd_pcm*) ; 

__attribute__((used)) static int snd_pcm_free(struct snd_pcm *pcm)
{
	if (!pcm)
		return 0;
	if (!pcm->internal)
		pcm_call_notify(pcm, n_unregister);
	if (pcm->private_free)
		pcm->private_free(pcm);
	snd_pcm_lib_preallocate_free_for_all(pcm);
	snd_pcm_free_stream(&pcm->streams[SNDRV_PCM_STREAM_PLAYBACK]);
	snd_pcm_free_stream(&pcm->streams[SNDRV_PCM_STREAM_CAPTURE]);
	kfree(pcm);
	return 0;
}