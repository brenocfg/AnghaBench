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
struct TYPE_6__ {unsigned int* item; } ;
struct TYPE_7__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct TYPE_8__ {TYPE_1__* codec_dai; } ;
struct TYPE_5__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8804_SPDSTAT ; 
 TYPE_4__* get_wm8804_runtime (struct snd_soc_card*) ; 
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_soc_component_read (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int rpi_cirrus_recovered_frequency_get(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct snd_soc_component *wm8804_component =
		get_wm8804_runtime(card)->codec_dai->component;
	unsigned int val;
	int ret;

	ret = snd_soc_component_read(wm8804_component, WM8804_SPDSTAT, &val);
	if (ret)
		return ret;

	ucontrol->value.enumerated.item[0] = (val >> 4) & 0x03;
	return 0;
}