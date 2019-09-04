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
struct snd_usb_substream {int last_delay; int last_frame_number; scalar_t__ direction; int /*<<< orphan*/  dev; } ;
typedef  int snd_pcm_uframes_t ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int usb_get_current_frame_number (int /*<<< orphan*/ ) ; 

snd_pcm_uframes_t snd_usb_pcm_delay(struct snd_usb_substream *subs,
				    unsigned int rate)
{
	int current_frame_number;
	int frame_diff;
	int est_delay;

	if (!subs->last_delay)
		return 0; /* short path */

	current_frame_number = usb_get_current_frame_number(subs->dev);
	/*
	 * HCD implementations use different widths, use lower 8 bits.
	 * The delay will be managed up to 256ms, which is more than
	 * enough
	 */
	frame_diff = (current_frame_number - subs->last_frame_number) & 0xff;

	/* Approximation based on number of samples per USB frame (ms),
	   some truncation for 44.1 but the estimate is good enough */
	est_delay =  frame_diff * rate / 1000;
	if (subs->direction == SNDRV_PCM_STREAM_PLAYBACK)
		est_delay = subs->last_delay - est_delay;
	else
		est_delay = subs->last_delay + est_delay;

	if (est_delay < 0)
		est_delay = 0;
	return est_delay;
}