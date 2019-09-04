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
struct nm256 {scalar_t__ badintrcount; TYPE_1__* streams; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ running; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_nm256_capture_stop (struct nm256*) ; 
 int /*<<< orphan*/  snd_nm256_playback_stop (struct nm256*) ; 

__attribute__((used)) static irqreturn_t
snd_nm256_intr_check(struct nm256 *chip)
{
	if (chip->badintrcount++ > 1000) {
		/*
		 * I'm not sure if the best thing is to stop the card from
		 * playing or just release the interrupt (after all, we're in
		 * a bad situation, so doing fancy stuff may not be such a good
		 * idea).
		 *
		 * I worry about the card engine continuing to play noise
		 * over and over, however--that could become a very
		 * obnoxious problem.  And we know that when this usually
		 * happens things are fairly safe, it just means the user's
		 * inserted a PCMCIA card and someone's spamming us with IRQ 9s.
		 */
		if (chip->streams[SNDRV_PCM_STREAM_PLAYBACK].running)
			snd_nm256_playback_stop(chip);
		if (chip->streams[SNDRV_PCM_STREAM_CAPTURE].running)
			snd_nm256_capture_stop(chip);
		chip->badintrcount = 0;
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}