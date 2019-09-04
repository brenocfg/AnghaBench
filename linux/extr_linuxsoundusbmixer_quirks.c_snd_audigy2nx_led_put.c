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
struct TYPE_4__ {unsigned int* value; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int snd_audigy2nx_led_update (struct usb_mixer_interface*,unsigned int,int) ; 
 struct usb_mixer_elem_list* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_audigy2nx_led_put(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	struct usb_mixer_interface *mixer = list->mixer;
	int index = kcontrol->private_value & 0xff;
	unsigned int value = ucontrol->value.integer.value[0];
	int old_value = kcontrol->private_value >> 8;
	int err;

	if (value > 1)
		return -EINVAL;
	if (value == old_value)
		return 0;
	kcontrol->private_value = (value << 8) | index;
	err = snd_audigy2nx_led_update(mixer, value, index);
	return err < 0 ? err : 1;
}