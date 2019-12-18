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
struct TYPE_3__ {scalar_t__* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM_MASTER ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int wm_get (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm_put (struct snd_ice1712*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aureon_oversampling_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	int temp, temp2;
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	temp2 = temp = wm_get(ice, WM_MASTER);

	if (ucontrol->value.enumerated.item[0])
		temp |= 0x8;
	else
		temp &= ~0x8;

	if (temp != temp2) {
		wm_put(ice, WM_MASTER, temp);
		return 1;
	}
	return 0;
}