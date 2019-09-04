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
struct usb_mixer_elem_info {int min; int cmask; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int MAX_CHANNELS ; 
 int filter_error (struct usb_mixer_elem_info*,int) ; 
 int get_relative_value (struct usb_mixer_elem_info*,int) ; 
 int snd_usb_get_cur_mix_value (struct usb_mixer_elem_info*,int,int,int*) ; 

__attribute__((used)) static int mixer_ctl_feature_get(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_info *cval = kcontrol->private_data;
	int c, cnt, val, err;

	ucontrol->value.integer.value[0] = cval->min;
	if (cval->cmask) {
		cnt = 0;
		for (c = 0; c < MAX_CHANNELS; c++) {
			if (!(cval->cmask & (1 << c)))
				continue;
			err = snd_usb_get_cur_mix_value(cval, c + 1, cnt, &val);
			if (err < 0)
				return filter_error(cval, err);
			val = get_relative_value(cval, val);
			ucontrol->value.integer.value[cnt] = val;
			cnt++;
		}
		return 0;
	} else {
		/* master channel */
		err = snd_usb_get_cur_mix_value(cval, 0, 0, &val);
		if (err < 0)
			return filter_error(cval, err);
		val = get_relative_value(cval, val);
		ucontrol->value.integer.value[0] = val;
	}
	return 0;
}