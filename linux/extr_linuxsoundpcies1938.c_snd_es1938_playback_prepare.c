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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int snd_es1938_playback1_prepare (struct snd_pcm_substream*) ; 
 int snd_es1938_playback2_prepare (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_es1938_playback_prepare(struct snd_pcm_substream *substream)
{
	switch (substream->number) {
	case 0:
		return snd_es1938_playback1_prepare(substream);
	case 1:
		return snd_es1938_playback2_prepare(substream);
	}
	snd_BUG();
	return -EINVAL;
}