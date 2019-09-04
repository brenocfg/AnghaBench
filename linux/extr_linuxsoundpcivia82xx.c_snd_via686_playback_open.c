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
struct viadev {int dummy; } ;
struct via82xx {size_t playback_devno; struct viadev* devs; } ;
struct snd_pcm_substream {size_t number; } ;

/* Variables and functions */
 struct via82xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int snd_via82xx_pcm_open (struct via82xx*,struct viadev*,struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_via686_playback_open(struct snd_pcm_substream *substream)
{
	struct via82xx *chip = snd_pcm_substream_chip(substream);
	struct viadev *viadev = &chip->devs[chip->playback_devno + substream->number];
	int err;

	if ((err = snd_via82xx_pcm_open(chip, viadev, substream)) < 0)
		return err;
	return 0;
}