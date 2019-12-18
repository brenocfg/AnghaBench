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
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICEMT (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROUTE_SPDOUT ; 
 unsigned int inw (int /*<<< orphan*/ ) ; 
 int snd_ctl_get_ioffidx (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ice1712_pro_route_spdif_get(struct snd_kcontrol *kcontrol,
					   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	int idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	unsigned int val, cval;
	val = inw(ICEMT(ice, ROUTE_SPDOUT));
	cval = (val >> (idx * 4 + 8)) & 0x0f;
	val = (val >> (idx * 2)) & 0x03;
	if (val == 1)
		ucontrol->value.enumerated.item[0] = 11;
	else if (val == 2)
		ucontrol->value.enumerated.item[0] = (cval & 7) + 1;
	else if (val == 3)
		ucontrol->value.enumerated.item[0] = ((cval >> 3) & 1) + 9;
	else
		ucontrol->value.enumerated.item[0] = 0;
	return 0;
}