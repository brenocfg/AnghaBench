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
struct snd_pcm_substream {int dummy; } ;
struct snd_msnd {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_AUDIO_WRITE_INUSE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_msnd_disable_irq (struct snd_msnd*) ; 
 struct snd_msnd* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_msnd_playback_close(struct snd_pcm_substream *substream)
{
	struct snd_msnd *chip = snd_pcm_substream_chip(substream);

	snd_msnd_disable_irq(chip);
	clear_bit(F_AUDIO_WRITE_INUSE, &chip->flags);
	return 0;
}