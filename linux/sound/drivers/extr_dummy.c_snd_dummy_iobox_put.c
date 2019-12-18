#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct snd_dummy {int iobox; TYPE_6__* cd_switch_ctl; int /*<<< orphan*/  card; TYPE_5__* cd_volume_ctl; } ;
struct TYPE_7__ {int* item; } ;
struct TYPE_8__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_12__ {int /*<<< orphan*/  id; TYPE_4__* vd; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; TYPE_3__* vd; } ;
struct TYPE_10__ {int /*<<< orphan*/  access; } ;
struct TYPE_9__ {int /*<<< orphan*/  access; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_INFO ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_dummy* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_dummy_iobox_put(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *value)
{
	struct snd_dummy *dummy = snd_kcontrol_chip(kcontrol);
	int changed;

	if (value->value.enumerated.item[0] > 1)
		return -EINVAL;

	changed = value->value.enumerated.item[0] != dummy->iobox;
	if (changed) {
		dummy->iobox = value->value.enumerated.item[0];

		if (dummy->iobox) {
			dummy->cd_volume_ctl->vd[0].access &=
				~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
			dummy->cd_switch_ctl->vd[0].access &=
				~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		} else {
			dummy->cd_volume_ctl->vd[0].access |=
				SNDRV_CTL_ELEM_ACCESS_INACTIVE;
			dummy->cd_switch_ctl->vd[0].access |=
				SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		}

		snd_ctl_notify(dummy->card, SNDRV_CTL_EVENT_MASK_INFO,
			       &dummy->cd_volume_ctl->id);
		snd_ctl_notify(dummy->card, SNDRV_CTL_EVENT_MASK_INFO,
			       &dummy->cd_switch_ctl->id);
	}

	return changed;
}