#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {unsigned int private_value; int /*<<< orphan*/  id; TYPE_1__* vd; } ;
struct oxygen {int /*<<< orphan*/  card; } ;
struct TYPE_2__ {unsigned int access; } ;

/* Variables and functions */
 unsigned int SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_INFO ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void activate_control(struct oxygen *chip,
			     struct snd_kcontrol *ctl, unsigned int mode)
{
	unsigned int access;

	if (ctl->private_value & mode)
		access = 0;
	else
		access = SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	if ((ctl->vd[0].access & SNDRV_CTL_ELEM_ACCESS_INACTIVE) != access) {
		ctl->vd[0].access ^= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_INFO, &ctl->id);
	}
}