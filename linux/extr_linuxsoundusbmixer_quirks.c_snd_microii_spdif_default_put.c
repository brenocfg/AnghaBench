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
struct usb_mixer_elem_list {int dummy; } ;
struct snd_kcontrol {unsigned int private_value; } ;
struct TYPE_3__ {int* status; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 struct usb_mixer_elem_list* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_microii_spdif_default_update (struct usb_mixer_elem_list*) ; 

__attribute__((used)) static int snd_microii_spdif_default_put(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_list *list = snd_kcontrol_chip(kcontrol);
	unsigned int pval, pval_old;
	int err;

	pval = pval_old = kcontrol->private_value;
	pval &= 0xfffff0f0;
	pval |= (ucontrol->value.iec958.status[1] & 0x0f) << 8;
	pval |= (ucontrol->value.iec958.status[0] & 0x0f);

	pval &= 0xffff0fff;
	pval |= (ucontrol->value.iec958.status[1] & 0xf0) << 8;

	/* The frequency bits in AES3 cannot be set via register access. */

	/* Silently ignore any bits from the request that cannot be set. */

	if (pval == pval_old)
		return 0;

	kcontrol->private_value = pval;
	err = snd_microii_spdif_default_update(list);
	return err < 0 ? err : 1;
}