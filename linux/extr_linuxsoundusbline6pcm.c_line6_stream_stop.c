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
struct snd_line6_pcm {scalar_t__ prev_fsize; int /*<<< orphan*/ * prev_fbuf; } ;
struct line6_pcm_stream {int /*<<< orphan*/  lock; int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 struct line6_pcm_stream* get_stream (struct snd_line6_pcm*,int) ; 
 int /*<<< orphan*/  line6_unlink_audio_urbs (struct snd_line6_pcm*,struct line6_pcm_stream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void line6_stream_stop(struct snd_line6_pcm *line6pcm, int direction,
			  int type)
{
	unsigned long flags;
	struct line6_pcm_stream *pstr = get_stream(line6pcm, direction);

	spin_lock_irqsave(&pstr->lock, flags);
	clear_bit(type, &pstr->running);
	if (!pstr->running) {
		spin_unlock_irqrestore(&pstr->lock, flags);
		line6_unlink_audio_urbs(line6pcm, pstr);
		spin_lock_irqsave(&pstr->lock, flags);
		if (direction == SNDRV_PCM_STREAM_CAPTURE) {
			line6pcm->prev_fbuf = NULL;
			line6pcm->prev_fsize = 0;
		}
	}
	spin_unlock_irqrestore(&pstr->lock, flags);
}