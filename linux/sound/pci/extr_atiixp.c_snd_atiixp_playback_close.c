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
struct snd_pcm_substream {int dummy; } ;
struct atiixp {int /*<<< orphan*/  open_mutex; int /*<<< orphan*/ * dmas; } ;

/* Variables and functions */
 size_t ATI_DMA_PLAYBACK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_atiixp_pcm_close (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 struct atiixp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_atiixp_playback_close(struct snd_pcm_substream *substream)
{
	struct atiixp *chip = snd_pcm_substream_chip(substream);
	int err;
	mutex_lock(&chip->open_mutex);
	err = snd_atiixp_pcm_close(substream, &chip->dmas[ATI_DMA_PLAYBACK]);
	mutex_unlock(&chip->open_mutex);
	return err;
}