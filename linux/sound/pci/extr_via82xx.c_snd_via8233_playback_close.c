#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct viadev {int reg_offset; } ;
struct via82xx {TYPE_3__** dxs_controls; int /*<<< orphan*/  card; } ;
struct snd_pcm_substream {TYPE_2__* runtime; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; TYPE_1__* vd; } ;
struct TYPE_5__ {struct viadev* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  access; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_INFO ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct via82xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int snd_via82xx_pcm_close (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_via8233_playback_close(struct snd_pcm_substream *substream)
{
	struct via82xx *chip = snd_pcm_substream_chip(substream);
	struct viadev *viadev = substream->runtime->private_data;
	unsigned int stream;

	stream = viadev->reg_offset / 0x10;
	if (chip->dxs_controls[stream]) {
		chip->dxs_controls[stream]->vd[0].access |=
			SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_INFO,
			       &chip->dxs_controls[stream]->id);
	}
	return snd_via82xx_pcm_close(substream);
}