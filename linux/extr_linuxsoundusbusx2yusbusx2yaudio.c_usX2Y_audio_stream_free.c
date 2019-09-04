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
struct snd_usX2Y_substream {int dummy; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  kfree (struct snd_usX2Y_substream*) ; 

__attribute__((used)) static void usX2Y_audio_stream_free(struct snd_usX2Y_substream **usX2Y_substream)
{
	kfree(usX2Y_substream[SNDRV_PCM_STREAM_PLAYBACK]);
	usX2Y_substream[SNDRV_PCM_STREAM_PLAYBACK] = NULL;

	kfree(usX2Y_substream[SNDRV_PCM_STREAM_CAPTURE]);
	usX2Y_substream[SNDRV_PCM_STREAM_CAPTURE] = NULL;
}