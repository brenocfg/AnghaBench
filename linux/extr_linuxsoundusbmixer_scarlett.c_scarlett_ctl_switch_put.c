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
struct usb_mixer_elem_info {int channels; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int snd_usb_get_cur_mix_value (struct usb_mixer_elem_info*,int,int,int*) ; 
 int snd_usb_set_cur_mix_value (struct usb_mixer_elem_info*,int,int,int) ; 

__attribute__((used)) static int scarlett_ctl_switch_put(struct snd_kcontrol *kctl,
		struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_info *elem = kctl->private_data;
	int i, changed = 0;
	int err, oval, val;

	for (i = 0; i < elem->channels; i++) {
		err = snd_usb_get_cur_mix_value(elem, i, i, &oval);
		if (err < 0)
			return err;

		val = ucontrol->value.integer.value[i];
		val = !val;
		if (oval != val) {
			err = snd_usb_set_cur_mix_value(elem, i, i, val);
			if (err < 0)
				return err;

			changed = 1;
		}
	}

	return changed;
}