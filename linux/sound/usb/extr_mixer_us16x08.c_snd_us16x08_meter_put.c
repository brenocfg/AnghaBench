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
struct usb_mixer_elem_info {struct snd_us16x08_meter_store* private_data; } ;
struct snd_us16x08_meter_store {int comp_active_index; int comp_index; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_US16X08_MAX_CHANNELS ; 

__attribute__((used)) static int snd_us16x08_meter_put(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_info *elem = kcontrol->private_data;
	struct snd_us16x08_meter_store *store = elem->private_data;
	int val;

	val = ucontrol->value.integer.value[0];

	/* sanity check */
	if (val < 0 || val >= SND_US16X08_MAX_CHANNELS)
		return -EINVAL;

	store->comp_active_index = val;
	store->comp_index = val;

	return 1;
}