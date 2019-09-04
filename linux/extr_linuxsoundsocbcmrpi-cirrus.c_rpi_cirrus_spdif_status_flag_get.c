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
struct snd_kcontrol {int private_value; } ;
struct TYPE_5__ {int* value; } ;
struct TYPE_6__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_8__ {TYPE_3__* codec_dai; } ;
struct TYPE_7__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 TYPE_4__* get_wm8804_runtime (struct snd_soc_card*) ; 
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_soc_component_read (struct snd_soc_component*,unsigned int,unsigned int*) ; 

__attribute__((used)) static int rpi_cirrus_spdif_status_flag_get(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct snd_soc_component *wm8804_component =
		get_wm8804_runtime(card)->codec_dai->component;

	unsigned int bit = kcontrol->private_value & 0xff;
	unsigned int reg = (kcontrol->private_value >> 8) & 0xff;
	unsigned int invert = (kcontrol->private_value >> 16) & 0xff;
	int ret;
	unsigned int val;
	bool flag;

	ret = snd_soc_component_read(wm8804_component, reg, &val);
	if (ret)
		return ret;

	flag = val & (1 << bit);

	ucontrol->value.integer.value[0] = invert ? !flag : flag;

	return 0;
}