#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* runtime; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_2__ {scalar_t__ access; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_ACCESS_MMAP_INTERLEAVED ; 
 scalar_t__ SNDRV_PCM_ACCESS_RW_INTERLEAVED ; 
 int /*<<< orphan*/  fill_silence ; 
 int interleaved_copy (struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int noninterleaved_copy (struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_silence_frames(struct snd_pcm_substream *substream,
			       snd_pcm_uframes_t off, snd_pcm_uframes_t frames)
{
	if (substream->runtime->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED ||
	    substream->runtime->access == SNDRV_PCM_ACCESS_MMAP_INTERLEAVED)
		return interleaved_copy(substream, off, NULL, 0, frames,
					fill_silence);
	else
		return noninterleaved_copy(substream, off, NULL, 0, frames,
					   fill_silence);
}