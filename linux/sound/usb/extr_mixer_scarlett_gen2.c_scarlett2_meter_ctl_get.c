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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int /*<<< orphan*/  mixer; } ;
struct usb_mixer_elem_info {int channels; TYPE_3__ head; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int SCARLETT2_NUM_METERS ; 
 int scarlett2_usb_get_meter_levels (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scarlett2_meter_ctl_get(struct snd_kcontrol *kctl,
				   struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_info *elem = kctl->private_data;
	u16 meter_levels[SCARLETT2_NUM_METERS];
	int i, err;

	err = scarlett2_usb_get_meter_levels(elem->head.mixer, meter_levels);
	if (err < 0)
		return err;

	for (i = 0; i < elem->channels; i++)
		ucontrol->value.integer.value[i] = meter_levels[i];

	return 0;
}