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
struct snd_pcm_substream {int number; } ;
struct es1938 {int /*<<< orphan*/ * playback2_substream; int /*<<< orphan*/ * playback1_substream; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  snd_BUG () ; 
 struct es1938* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_es1938_playback_close(struct snd_pcm_substream *substream)
{
	struct es1938 *chip = snd_pcm_substream_chip(substream);

	switch (substream->number) {
	case 0:
		chip->playback1_substream = NULL;
		break;
	case 1:
		chip->playback2_substream = NULL;
		break;
	default:
		snd_BUG();
		return -EINVAL;
	}
	return 0;
}