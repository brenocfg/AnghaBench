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
struct usb_mixer_interface {int dummy; } ;
struct usb_mixer_elem_list {struct usb_mixer_interface* mixer; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 struct usb_mixer_elem_list* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_mbox1_switch_update (struct usb_mixer_interface*,int) ; 

__attribute__((used)) static int snd_mbox1_switch_put(struct snd_kcontrol *kctl,
				struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_list *list = snd_kcontrol_chip(kctl);
	struct usb_mixer_interface *mixer = list->mixer;
	int err;
	bool cur_val, new_val;

	cur_val = kctl->private_value;
	new_val = ucontrol->value.enumerated.item[0];
	if (cur_val == new_val)
		return 0;

	kctl->private_value = new_val;
	err = snd_mbox1_switch_update(mixer, new_val);
	return err < 0 ? err : 1;
}