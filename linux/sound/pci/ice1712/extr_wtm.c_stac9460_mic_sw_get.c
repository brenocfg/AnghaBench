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
struct snd_ice1712 {int dummy; } ;
struct TYPE_3__ {unsigned char* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAC946X_GENERAL_PURPOSE ; 
 int snd_ctl_get_ioffidx (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned char stac9460_2_get (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 unsigned char stac9460_get (struct snd_ice1712*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stac9460_mic_sw_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	unsigned char val;
	int id;

	id = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	if (id == 0)
		val = stac9460_get(ice, STAC946X_GENERAL_PURPOSE);
	else
		val = stac9460_2_get(ice, STAC946X_GENERAL_PURPOSE);
	ucontrol->value.enumerated.item[0] = (val >> 7) & 0x1;
	return 0;
}