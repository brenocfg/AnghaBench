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
struct usb_mixer_elem_list {int /*<<< orphan*/  mixer; } ;
struct snd_kcontrol {unsigned char private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 struct usb_mixer_elem_list* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_soundblaster_e1_switch_update (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int snd_soundblaster_e1_switch_put(struct snd_kcontrol *kcontrol,
					  struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	unsigned char value = !!ucontrol->value.integer.value[0];
	int err;

	if (kcontrol->private_value == value)
		return 0;
	kcontrol->private_value = value;
	err = snd_soundblaster_e1_switch_update(list->mixer, value);
	return err < 0 ? err : 1;
}