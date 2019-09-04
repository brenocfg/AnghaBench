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
struct via82xx {void*** playback_volume; } ;
struct TYPE_4__ {unsigned int subdevice; } ;
struct snd_kcontrol {TYPE_1__ id; } ;
struct TYPE_5__ {void** value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;

/* Variables and functions */
 void* VIA_DXS_MAX_VOLUME ; 
 struct via82xx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_via8233_dxs_volume_get(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_value *ucontrol)
{
	struct via82xx *chip = snd_kcontrol_chip(kcontrol);
	unsigned int idx = kcontrol->id.subdevice;

	ucontrol->value.integer.value[0] = VIA_DXS_MAX_VOLUME - chip->playback_volume[idx][0];
	ucontrol->value.integer.value[1] = VIA_DXS_MAX_VOLUME - chip->playback_volume[idx][1];
	return 0;
}