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

/* Variables and functions */
 int snd_ac97_update_bits (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ac97_vt1618_aux_put(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_value *ucontrol)
{
	/* toggle surround rear dac power */

	snd_ac97_update_bits(snd_kcontrol_chip(kcontrol), 0x5c, 0x0008,
			     ucontrol->value.enumerated.item[0] << 3);

	/* toggle aux in surround rear out jack */

	return snd_ac97_update_bits(snd_kcontrol_chip(kcontrol), 0x76, 0x0008,
				    ucontrol->value.enumerated.item[0] << 3);
}