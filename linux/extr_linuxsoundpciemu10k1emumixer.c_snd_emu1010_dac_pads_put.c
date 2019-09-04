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
struct snd_kcontrol {int private_value; } ;
struct TYPE_5__ {unsigned int dac_pads; } ;
struct snd_emu10k1 {TYPE_2__ emu1010; } ;
struct TYPE_6__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_3__ integer; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU_HANA_DAC_PADS ; 
 int /*<<< orphan*/  snd_emu1010_fpga_write (struct snd_emu10k1*,int /*<<< orphan*/ ,unsigned int) ; 
 struct snd_emu10k1* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_emu1010_dac_pads_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	unsigned int mask = kcontrol->private_value & 0xff;
	unsigned int val, cache;
	val = ucontrol->value.integer.value[0];
	cache = emu->emu1010.dac_pads;
	if (val == 1) 
		cache = cache | mask;
	else
		cache = cache & ~mask;
	if (cache != emu->emu1010.dac_pads) {
		snd_emu1010_fpga_write(emu, EMU_HANA_DAC_PADS, cache );
	        emu->emu1010.dac_pads = cache;
	}

	return 0;
}