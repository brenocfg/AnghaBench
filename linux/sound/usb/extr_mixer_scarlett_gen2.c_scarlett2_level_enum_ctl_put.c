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
struct usb_mixer_elem_info {int control; TYPE_1__ head; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct scarlett2_mixer_data {int* level_switch; int /*<<< orphan*/  data_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCARLETT2_CONFIG_LEVEL_SWITCH ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int scarlett2_usb_set_config (struct usb_mixer_interface*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int scarlett2_level_enum_ctl_put(struct snd_kcontrol *kctl,
					struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_info *elem = kctl->private_data;
	struct usb_mixer_interface *mixer = elem->head.mixer;
	struct scarlett2_mixer_data *private = mixer->private_data;

	int index = elem->control;
	int oval, val, err = 0;

	mutex_lock(&private->data_mutex);

	oval = private->level_switch[index];
	val = !!ucontrol->value.integer.value[0];

	if (oval == val)
		goto unlock;

	private->level_switch[index] = val;

	/* Send switch change to the device */
	err = scarlett2_usb_set_config(mixer, SCARLETT2_CONFIG_LEVEL_SWITCH,
				       index, val);

unlock:
	mutex_unlock(&private->data_mutex);
	return err;
}