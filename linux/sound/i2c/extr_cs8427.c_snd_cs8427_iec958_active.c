#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_i2c_device {TYPE_2__* bus; struct cs8427* private_data; } ;
struct TYPE_8__ {TYPE_3__* pcm_ctl; int /*<<< orphan*/  def_status; int /*<<< orphan*/  pcm_status; } ;
struct cs8427 {TYPE_4__ playback; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; TYPE_1__* vd; } ;
struct TYPE_6__ {int /*<<< orphan*/  card; } ;
struct TYPE_5__ {int /*<<< orphan*/  access; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int SNDRV_CTL_EVENT_MASK_INFO ; 
 int SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int snd_cs8427_iec958_active(struct snd_i2c_device *cs8427, int active)
{
	struct cs8427 *chip;

	if (snd_BUG_ON(!cs8427))
		return -ENXIO;
	chip = cs8427->private_data;
	if (active)
		memcpy(chip->playback.pcm_status,
		       chip->playback.def_status, 24);
	chip->playback.pcm_ctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notify(cs8427->bus->card,
		       SNDRV_CTL_EVENT_MASK_VALUE | SNDRV_CTL_EVENT_MASK_INFO,
		       &chip->playback.pcm_ctl->id);
	return 0;
}