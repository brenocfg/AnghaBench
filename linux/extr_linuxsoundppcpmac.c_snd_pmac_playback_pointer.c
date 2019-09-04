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
struct snd_pmac {int /*<<< orphan*/  playback; } ;
struct snd_pcm_substream {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 struct snd_pmac* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pmac_pcm_pointer (struct snd_pmac*,int /*<<< orphan*/ *,struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_pmac_playback_pointer(struct snd_pcm_substream *subs)
{
	struct snd_pmac *chip = snd_pcm_substream_chip(subs);
	return snd_pmac_pcm_pointer(chip, &chip->playback, subs);
}