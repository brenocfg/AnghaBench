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
struct usb_mixer_elem_info {struct scarlett_mixer_elem_enum_info* private_data; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct scarlett_mixer_elem_enum_info {int start; } ;

/* Variables and functions */
 int snd_usb_get_cur_mix_value (struct usb_mixer_elem_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  snd_usb_set_cur_mix_value (struct usb_mixer_elem_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int scarlett_ctl_enum_put(struct snd_kcontrol *kctl,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_info *elem = kctl->private_data;
	struct scarlett_mixer_elem_enum_info *opt = elem->private_data;
	int err, oval, val;

	err = snd_usb_get_cur_mix_value(elem, 0, 0, &oval);
	if (err < 0)
		return err;

	val = ucontrol->value.integer.value[0];
	val = val + opt->start;
	if (val != oval) {
		snd_usb_set_cur_mix_value(elem, 0, 0, val);
		return 1;
	}
	return 0;
}