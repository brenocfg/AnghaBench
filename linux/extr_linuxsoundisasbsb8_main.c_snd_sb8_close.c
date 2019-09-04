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
struct snd_sb {int /*<<< orphan*/  open_lock; int /*<<< orphan*/  mode; int /*<<< orphan*/  open; int /*<<< orphan*/ * capture_substream; int /*<<< orphan*/ * playback_substream; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_MODE_CAPTURE ; 
 int /*<<< orphan*/  SB_MODE_PLAYBACK ; 
 int /*<<< orphan*/  SB_OPEN_PCM ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 struct snd_sb* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_sb8_close(struct snd_pcm_substream *substream)
{
	unsigned long flags;
	struct snd_sb *chip = snd_pcm_substream_chip(substream);

	chip->playback_substream = NULL;
	chip->capture_substream = NULL;
	spin_lock_irqsave(&chip->open_lock, flags);
	chip->open &= ~SB_OPEN_PCM;
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		chip->mode &= ~SB_MODE_PLAYBACK;
	else
		chip->mode &= ~SB_MODE_CAPTURE;
	spin_unlock_irqrestore(&chip->open_lock, flags);
	return 0;
}