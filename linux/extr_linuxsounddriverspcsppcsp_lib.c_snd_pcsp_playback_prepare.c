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
struct snd_pcsp {int fmt_size; int /*<<< orphan*/  is_signed; scalar_t__ period_ptr; scalar_t__ playback_ptr; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcsp_sync_stop (struct snd_pcsp*) ; 
 int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_format_signed (int /*<<< orphan*/ ) ; 
 struct snd_pcsp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcsp_playback_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcsp *chip = snd_pcm_substream_chip(substream);
	pcsp_sync_stop(chip);
	chip->playback_ptr = 0;
	chip->period_ptr = 0;
	chip->fmt_size =
		snd_pcm_format_physical_width(substream->runtime->format) >> 3;
	chip->is_signed = snd_pcm_format_signed(substream->runtime->format);
#if PCSP_DEBUG
	printk(KERN_INFO "PCSP: prepare called, "
			"size=%zi psize=%zi f=%zi f1=%i fsize=%i\n",
			snd_pcm_lib_buffer_bytes(substream),
			snd_pcm_lib_period_bytes(substream),
			snd_pcm_lib_buffer_bytes(substream) /
			snd_pcm_lib_period_bytes(substream),
			substream->runtime->periods,
			chip->fmt_size);
#endif
	return 0;
}