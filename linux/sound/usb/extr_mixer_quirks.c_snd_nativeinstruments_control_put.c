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
typedef  scalar_t__ u8 ;
struct usb_mixer_elem_list {int dummy; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 struct usb_mixer_elem_list* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_ni_update_cur_val (struct usb_mixer_elem_list*) ; 

__attribute__((used)) static int snd_nativeinstruments_control_put(struct snd_kcontrol *kcontrol,
					     struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	u8 oldval = (kcontrol->private_value >> 24) & 0xff;
	u8 newval = ucontrol->value.integer.value[0];
	int err;

	if (oldval == newval)
		return 0;

	kcontrol->private_value &= ~(0xff << 24);
	kcontrol->private_value |= (unsigned int)newval << 24;
	err = snd_ni_update_cur_val(list);
	return err < 0 ? err : 1;
}