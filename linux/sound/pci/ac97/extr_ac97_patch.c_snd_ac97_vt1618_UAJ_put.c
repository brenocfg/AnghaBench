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
struct snd_kcontrol {size_t private_value; } ;
struct TYPE_4__ {int* item; } ;
struct TYPE_5__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {int shift; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int ac97_update_bits_page (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_kcontrol_chip (struct snd_kcontrol*) ; 
 TYPE_3__* vt1618_uaj ; 

__attribute__((used)) static int snd_ac97_vt1618_UAJ_put(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_value *ucontrol)
{
	return ac97_update_bits_page(snd_kcontrol_chip(kcontrol), 0x60,
				     vt1618_uaj[kcontrol->private_value].mask,
				     ucontrol->value.enumerated.item[0]<<
				     vt1618_uaj[kcontrol->private_value].shift,
				     0);
}