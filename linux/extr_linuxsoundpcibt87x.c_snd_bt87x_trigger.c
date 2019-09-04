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
struct snd_bt87x {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int snd_bt87x_start (struct snd_bt87x*) ; 
 int snd_bt87x_stop (struct snd_bt87x*) ; 
 struct snd_bt87x* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_bt87x_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_bt87x *chip = snd_pcm_substream_chip(substream);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		return snd_bt87x_start(chip);
	case SNDRV_PCM_TRIGGER_STOP:
		return snd_bt87x_stop(chip);
	default:
		return -EINVAL;
	}
}