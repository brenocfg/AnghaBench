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
struct uac_rtd_params {int /*<<< orphan*/  hw_ptr; } ;
struct snd_uac_chip {struct uac_rtd_params c_prm; struct uac_rtd_params p_prm; } ;
struct snd_pcm_substream {scalar_t__ stream; int /*<<< orphan*/  runtime; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_uac_chip* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t uac_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct snd_uac_chip *uac = snd_pcm_substream_chip(substream);
	struct uac_rtd_params *prm;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		prm = &uac->p_prm;
	else
		prm = &uac->c_prm;

	return bytes_to_frames(substream->runtime, prm->hw_ptr);
}