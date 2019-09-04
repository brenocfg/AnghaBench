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
struct snd_kcontrol {size_t private_value; } ;
struct snd_ice1712 {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct qtet_kcontrol_private {int (* get_register ) (struct snd_ice1712*) ;int bit; } ;

/* Variables and functions */
 struct qtet_kcontrol_private* qtet_privates ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int stub1 (struct snd_ice1712*) ; 

__attribute__((used)) static int qtet_sw_get(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct qtet_kcontrol_private private =
		qtet_privates[kcontrol->private_value];
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	ucontrol->value.integer.value[0] =
		(private.get_register(ice) & private.bit) ? 1 : 0;
	return 0;
}