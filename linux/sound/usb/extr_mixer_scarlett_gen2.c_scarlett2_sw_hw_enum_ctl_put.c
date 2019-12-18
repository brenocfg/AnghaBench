#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_mixer_interface {TYPE_5__* chip; struct scarlett2_mixer_data* private_data; } ;
struct TYPE_7__ {struct usb_mixer_interface* mixer; } ;
struct usb_mixer_elem_info {int control; TYPE_1__ head; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_8__ {int /*<<< orphan*/ * value; } ;
struct TYPE_9__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct scarlett2_mixer_data {int* vol_sw_hw_switch; int* vol; int master_vol; int /*<<< orphan*/  data_mutex; TYPE_6__** vol_ctls; } ;
struct TYPE_12__ {int /*<<< orphan*/  id; TYPE_4__* vd; } ;
struct TYPE_11__ {int /*<<< orphan*/  card; } ;
struct TYPE_10__ {int /*<<< orphan*/  access; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCARLETT2_CONFIG_LINE_OUT_VOLUME ; 
 int /*<<< orphan*/  SCARLETT2_CONFIG_SW_HW_SWITCH ; 
 int SCARLETT2_VOLUME_BIAS ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_WRITE ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_INFO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int scarlett2_usb_set_config (struct usb_mixer_interface*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scarlett2_sw_hw_enum_ctl_put(struct snd_kcontrol *kctl,
					struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_info *elem = kctl->private_data;
	struct usb_mixer_interface *mixer = elem->head.mixer;
	struct scarlett2_mixer_data *private = mixer->private_data;

	int index = elem->control;
	int oval, val, err = 0;

	mutex_lock(&private->data_mutex);

	oval = private->vol_sw_hw_switch[index];
	val = !!ucontrol->value.integer.value[0];

	if (oval == val)
		goto unlock;

	private->vol_sw_hw_switch[index] = val;

	/* Change access mode to RO (hardware controlled volume)
	 * or RW (software controlled volume)
	 */
	if (val)
		private->vol_ctls[index]->vd[0].access &=
			~SNDRV_CTL_ELEM_ACCESS_WRITE;
	else
		private->vol_ctls[index]->vd[0].access |=
			SNDRV_CTL_ELEM_ACCESS_WRITE;

	/* Reset volume to master volume */
	private->vol[index] = private->master_vol;

	/* Set SW volume to current HW volume */
	err = scarlett2_usb_set_config(
		mixer, SCARLETT2_CONFIG_LINE_OUT_VOLUME,
		index, private->master_vol - SCARLETT2_VOLUME_BIAS);
	if (err < 0)
		goto unlock;

	/* Notify of RO/RW change */
	snd_ctl_notify(mixer->chip->card, SNDRV_CTL_EVENT_MASK_INFO,
		       &private->vol_ctls[index]->id);

	/* Send SW/HW switch change to the device */
	err = scarlett2_usb_set_config(mixer, SCARLETT2_CONFIG_SW_HW_SWITCH,
				       index, val);

unlock:
	mutex_unlock(&private->data_mutex);
	return err;
}