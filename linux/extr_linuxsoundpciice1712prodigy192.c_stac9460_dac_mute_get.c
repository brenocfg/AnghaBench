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
struct snd_kcontrol {scalar_t__ private_value; } ;
struct snd_ice1712 {int dummy; } ;
struct TYPE_4__ {unsigned char* value; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_1__ value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int STAC946X_LF_VOLUME ; 
 int STAC946X_MASTER_VOLUME ; 
 int snd_ctl_get_ioffidx (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned char stac9460_get (struct snd_ice1712*,int) ; 

__attribute__((used)) static int stac9460_dac_mute_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	unsigned char val;
	int idx;

	if (kcontrol->private_value)
		idx = STAC946X_MASTER_VOLUME;
	else
		idx  = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id) + STAC946X_LF_VOLUME;
	val = stac9460_get(ice, idx);
	ucontrol->value.integer.value[0] = (~val >> 7) & 0x1;
	return 0;
}