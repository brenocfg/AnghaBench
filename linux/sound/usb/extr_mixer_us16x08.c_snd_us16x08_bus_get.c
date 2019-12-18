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
struct TYPE_6__ {int id; } ;
struct usb_mixer_elem_info {int /*<<< orphan*/ * cache_val; TYPE_3__ head; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
#define  SND_US16X08_ID_BUSS_OUT 130 
#define  SND_US16X08_ID_BYPASS 129 
#define  SND_US16X08_ID_MUTE 128 

__attribute__((used)) static int snd_us16x08_bus_get(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_info *elem = kcontrol->private_data;

	switch (elem->head.id) {
	case SND_US16X08_ID_BUSS_OUT:
		ucontrol->value.integer.value[0] = elem->cache_val[0];
		break;
	case SND_US16X08_ID_BYPASS:
		ucontrol->value.integer.value[0] = elem->cache_val[0];
		break;
	case SND_US16X08_ID_MUTE:
		ucontrol->value.integer.value[0] = elem->cache_val[0];
		break;
	}

	return 0;
}