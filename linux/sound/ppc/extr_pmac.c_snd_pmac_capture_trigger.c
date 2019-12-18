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
struct snd_pmac {int /*<<< orphan*/  capture; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 struct snd_pmac* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int snd_pmac_pcm_trigger (struct snd_pmac*,int /*<<< orphan*/ *,struct snd_pcm_substream*,int) ; 

__attribute__((used)) static int snd_pmac_capture_trigger(struct snd_pcm_substream *subs,
				    int cmd)
{
	struct snd_pmac *chip = snd_pcm_substream_chip(subs);
	return snd_pmac_pcm_trigger(chip, &chip->capture, subs, cmd);
}