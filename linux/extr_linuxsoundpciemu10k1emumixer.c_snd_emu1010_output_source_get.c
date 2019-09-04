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
struct snd_kcontrol {int private_value; } ;
struct TYPE_5__ {int /*<<< orphan*/ * output_source; } ;
struct snd_emu10k1 {TYPE_1__ emu1010; TYPE_2__* card_capabilities; } ;
struct TYPE_7__ {int /*<<< orphan*/ * item; } ;
struct TYPE_8__ {TYPE_3__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_4__ value; } ;
struct TYPE_6__ {scalar_t__ emu_model; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EMU_MODEL_EMU1616 ; 
 struct snd_emu10k1* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_emu1010_output_source_get(struct snd_kcontrol *kcontrol,
                                 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	unsigned int channel;

	channel = (kcontrol->private_value) & 0xff;
	/* Limit: emu1010_output_dst, emu->emu1010.output_source */
	if (channel >= 24 ||
	    (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616 &&
	     channel >= 18))
		return -EINVAL;
	ucontrol->value.enumerated.item[0] = emu->emu1010.output_source[channel];
	return 0;
}