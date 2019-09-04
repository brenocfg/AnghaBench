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
struct snd_line6_pcm {int dummy; } ;
struct line6_pcm_stream {int /*<<< orphan*/  lock; int /*<<< orphan*/  running; scalar_t__ count; scalar_t__ unlink_urbs; scalar_t__ active_urbs; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 struct line6_pcm_stream* get_stream (struct snd_line6_pcm*,int) ; 
 int line6_submit_audio_in_all_urbs (struct snd_line6_pcm*) ; 
 int line6_submit_audio_out_all_urbs (struct snd_line6_pcm*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int line6_stream_start(struct snd_line6_pcm *line6pcm, int direction,
			      int type)
{
	unsigned long flags;
	struct line6_pcm_stream *pstr = get_stream(line6pcm, direction);
	int ret = 0;

	spin_lock_irqsave(&pstr->lock, flags);
	if (!test_and_set_bit(type, &pstr->running) &&
	    !(pstr->active_urbs || pstr->unlink_urbs)) {
		pstr->count = 0;
		/* Submit all currently available URBs */
		if (direction == SNDRV_PCM_STREAM_PLAYBACK)
			ret = line6_submit_audio_out_all_urbs(line6pcm);
		else
			ret = line6_submit_audio_in_all_urbs(line6pcm);
	}

	if (ret < 0)
		clear_bit(type, &pstr->running);
	spin_unlock_irqrestore(&pstr->lock, flags);
	return ret;
}