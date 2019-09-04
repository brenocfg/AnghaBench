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
struct snd_pcsp {unsigned int playback_ptr; int /*<<< orphan*/  substream_lock; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,unsigned int) ; 
 struct snd_pcsp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_pcsp_playback_pointer(struct snd_pcm_substream
						   *substream)
{
	struct snd_pcsp *chip = snd_pcm_substream_chip(substream);
	unsigned int pos;
	spin_lock(&chip->substream_lock);
	pos = chip->playback_ptr;
	spin_unlock(&chip->substream_lock);
	return bytes_to_frames(substream->runtime, pos);
}