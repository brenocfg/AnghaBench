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
struct snd_pcsp {int playback_ptr; int fmt_size; int period_ptr; int /*<<< orphan*/  substream_lock; struct snd_pcm_substream* playback_substream; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int PCSP_INDEX_INC () ; 
 int /*<<< orphan*/  pcsp_pcm_tasklet ; 
 size_t snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 size_t snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcsp_pointer_update(struct snd_pcsp *chip)
{
	struct snd_pcm_substream *substream;
	size_t period_bytes, buffer_bytes;
	int periods_elapsed;
	unsigned long flags;

	/* update the playback position */
	substream = chip->playback_substream;
	if (!substream)
		return;

	period_bytes = snd_pcm_lib_period_bytes(substream);
	buffer_bytes = snd_pcm_lib_buffer_bytes(substream);

	spin_lock_irqsave(&chip->substream_lock, flags);
	chip->playback_ptr += PCSP_INDEX_INC() * chip->fmt_size;
	periods_elapsed = chip->playback_ptr - chip->period_ptr;
	if (periods_elapsed < 0) {
#if PCSP_DEBUG
		printk(KERN_INFO "PCSP: buffer_bytes mod period_bytes != 0 ? "
			"(%zi %zi %zi)\n",
			chip->playback_ptr, period_bytes, buffer_bytes);
#endif
		periods_elapsed += buffer_bytes;
	}
	periods_elapsed /= period_bytes;
	/* wrap the pointer _before_ calling snd_pcm_period_elapsed(),
	 * or ALSA will BUG on us. */
	chip->playback_ptr %= buffer_bytes;

	if (periods_elapsed) {
		chip->period_ptr += periods_elapsed * period_bytes;
		chip->period_ptr %= buffer_bytes;
	}
	spin_unlock_irqrestore(&chip->substream_lock, flags);

	if (periods_elapsed)
		tasklet_schedule(&pcsp_pcm_tasklet);
}