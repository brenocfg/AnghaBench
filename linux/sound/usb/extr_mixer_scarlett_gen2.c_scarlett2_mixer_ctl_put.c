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
struct usb_mixer_interface {struct scarlett2_mixer_data* private_data; } ;
struct TYPE_4__ {struct usb_mixer_interface* mixer; } ;
struct usb_mixer_elem_info {size_t control; TYPE_1__ head; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_5__ {int* value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct scarlett2_ports {int* num; } ;
struct scarlett2_mixer_data {int* mix; int /*<<< orphan*/  data_mutex; struct scarlett2_device_info* info; } ;
struct scarlett2_device_info {struct scarlett2_ports* ports; } ;

/* Variables and functions */
 size_t SCARLETT2_PORT_OUT ; 
 size_t SCARLETT2_PORT_TYPE_MIX ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int scarlett2_usb_set_mix (struct usb_mixer_interface*,int) ; 

__attribute__((used)) static int scarlett2_mixer_ctl_put(struct snd_kcontrol *kctl,
				   struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_info *elem = kctl->private_data;
	struct usb_mixer_interface *mixer = elem->head.mixer;
	struct scarlett2_mixer_data *private = mixer->private_data;
	const struct scarlett2_device_info *info = private->info;
	const struct scarlett2_ports *ports = info->ports;
	int oval, val, num_mixer_in, mix_num, err = 0;

	mutex_lock(&private->data_mutex);

	oval = private->mix[elem->control];
	val = ucontrol->value.integer.value[0];
	num_mixer_in = ports[SCARLETT2_PORT_TYPE_MIX].num[SCARLETT2_PORT_OUT];
	mix_num = elem->control / num_mixer_in;

	if (oval == val)
		goto unlock;

	private->mix[elem->control] = val;
	err = scarlett2_usb_set_mix(mixer, mix_num);
	if (err == 0)
		err = 1;

unlock:
	mutex_unlock(&private->data_mutex);
	return err;
}