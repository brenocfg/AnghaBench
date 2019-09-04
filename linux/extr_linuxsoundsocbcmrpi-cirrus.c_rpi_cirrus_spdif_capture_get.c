#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {unsigned int* status; } ;
struct TYPE_6__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_8__ {TYPE_3__* codec_dai; } ;
struct TYPE_7__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 scalar_t__ WM8804_RXCHAN1 ; 
 TYPE_4__* get_wm8804_runtime (struct snd_soc_card*) ; 
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_soc_component_read (struct snd_soc_component*,scalar_t__,unsigned int*) ; 

__attribute__((used)) static int rpi_cirrus_spdif_capture_get(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct snd_soc_component *wm8804_component =
		get_wm8804_runtime(card)->codec_dai->component;
	unsigned int val, mask;
	int i, ret;

	for (i = 0; i < 4; i++) {
		ret = snd_soc_component_read(wm8804_component,
			WM8804_RXCHAN1 + i, &val);
		if (ret)
			return ret;
		mask = (i == 3) ? 0x3f : 0xff;
		ucontrol->value.iec958.status[i] = val & mask;
	}

	return 0;
}