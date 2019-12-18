#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int private_value; } ;
struct TYPE_4__ {int /*<<< orphan*/ * value; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct layout_dev {int switch_on_headphone; int switch_on_lineout; } ;

/* Variables and functions */
 int ENODEV ; 
 struct layout_dev* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int detect_choice_put(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct layout_dev *ldev = snd_kcontrol_chip(kcontrol);

	switch (kcontrol->private_value) {
	case 0:
		ldev->switch_on_headphone = !!ucontrol->value.integer.value[0];
		break;
	case 1:
		ldev->switch_on_lineout = !!ucontrol->value.integer.value[0];
		break;
	default:
		return -ENODEV;
	}
	return 1;
}