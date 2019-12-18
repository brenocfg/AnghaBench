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
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hdsp {int dummy; } ;

/* Variables and functions */
 int hdsp_spdif_sample_rate (struct hdsp*) ; 
 struct hdsp* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_hdsp_get_spdif_sample_rate(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	switch (hdsp_spdif_sample_rate(hdsp)) {
	case 32000:
		ucontrol->value.enumerated.item[0] = 0;
		break;
	case 44100:
		ucontrol->value.enumerated.item[0] = 1;
		break;
	case 48000:
		ucontrol->value.enumerated.item[0] = 2;
		break;
	case 64000:
		ucontrol->value.enumerated.item[0] = 3;
		break;
	case 88200:
		ucontrol->value.enumerated.item[0] = 4;
		break;
	case 96000:
		ucontrol->value.enumerated.item[0] = 5;
		break;
	case 128000:
		ucontrol->value.enumerated.item[0] = 7;
		break;
	case 176400:
		ucontrol->value.enumerated.item[0] = 8;
		break;
	case 192000:
		ucontrol->value.enumerated.item[0] = 9;
		break;
	default:
		ucontrol->value.enumerated.item[0] = 6;
	}
	return 0;
}