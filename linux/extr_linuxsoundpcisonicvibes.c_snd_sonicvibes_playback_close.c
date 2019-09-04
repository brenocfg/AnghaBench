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
struct sonicvibes {int /*<<< orphan*/  mode; int /*<<< orphan*/ * playback_substream; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SV_MODE_PLAY ; 
 struct sonicvibes* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_sonicvibes_playback_close(struct snd_pcm_substream *substream)
{
	struct sonicvibes *sonic = snd_pcm_substream_chip(substream);

	sonic->playback_substream = NULL;
	sonic->mode &= ~SV_MODE_PLAY;
	return 0;
}