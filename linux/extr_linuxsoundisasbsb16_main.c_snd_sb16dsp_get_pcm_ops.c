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
struct snd_pcm_ops {int dummy; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 struct snd_pcm_ops const snd_sb16_capture_ops ; 
 struct snd_pcm_ops const snd_sb16_playback_ops ; 

const struct snd_pcm_ops *snd_sb16dsp_get_pcm_ops(int direction)
{
	return direction == SNDRV_PCM_STREAM_PLAYBACK ?
		&snd_sb16_playback_ops : &snd_sb16_capture_ops;
}