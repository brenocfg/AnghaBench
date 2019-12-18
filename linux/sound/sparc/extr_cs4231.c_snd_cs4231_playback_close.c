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
struct snd_cs4231 {int /*<<< orphan*/ * playback_substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231_MODE_PLAY ; 
 int /*<<< orphan*/  snd_cs4231_close (struct snd_cs4231*,int /*<<< orphan*/ ) ; 
 struct snd_cs4231* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cs4231_playback_close(struct snd_pcm_substream *substream)
{
	struct snd_cs4231 *chip = snd_pcm_substream_chip(substream);

	snd_cs4231_close(chip, CS4231_MODE_PLAY);
	chip->playback_substream = NULL;

	return 0;
}