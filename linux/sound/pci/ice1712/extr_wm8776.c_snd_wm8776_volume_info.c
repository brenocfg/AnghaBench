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
struct snd_wm8776 {TYPE_3__* ctl; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_4__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
 int WM8776_FLAG_STEREO ; 
 struct snd_wm8776* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_wm8776_volume_info(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_info *uinfo)
{
	struct snd_wm8776 *wm = snd_kcontrol_chip(kcontrol);
	int n = kcontrol->private_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = (wm->ctl[n].flags & WM8776_FLAG_STEREO) ? 2 : 1;
	uinfo->value.integer.min = wm->ctl[n].min;
	uinfo->value.integer.max = wm->ctl[n].max;

	return 0;
}