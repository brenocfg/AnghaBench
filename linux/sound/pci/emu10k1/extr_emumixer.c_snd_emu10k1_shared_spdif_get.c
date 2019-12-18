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
struct snd_kcontrol {int dummy; } ;
struct snd_emu10k1 {TYPE_1__* card_capabilities; scalar_t__ port; scalar_t__ audigy; } ;
struct TYPE_5__ {int* value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct TYPE_4__ {scalar_t__ invert_shared_spdif; } ;

/* Variables and functions */
 scalar_t__ A_IOCFG ; 
 int A_IOCFG_GPOUT0 ; 
 scalar_t__ HCFG ; 
 int HCFG_GPOUT0 ; 
 int inl (scalar_t__) ; 
 struct snd_emu10k1* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_emu10k1_shared_spdif_get(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);

	if (emu->audigy)
		ucontrol->value.integer.value[0] = inl(emu->port + A_IOCFG) & A_IOCFG_GPOUT0 ? 1 : 0;
	else
		ucontrol->value.integer.value[0] = inl(emu->port + HCFG) & HCFG_GPOUT0 ? 1 : 0;
	if (emu->card_capabilities->invert_shared_spdif)
		ucontrol->value.integer.value[0] =
			!ucontrol->value.integer.value[0];
		
	return 0;
}