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
struct snd_ice1712 {int /*<<< orphan*/  reg_lock; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICEMT (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RATE ; 
 int inb (int /*<<< orphan*/ ) ; 
 scalar_t__ is_spdif_master (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ice1712_pro_internal_clock_get(struct snd_kcontrol *kcontrol,
					      struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	static const unsigned char xlate[16] = {
		9, 6, 3, 1, 7, 4, 0, 12, 8, 5, 2, 11, 255, 255, 255, 10
	};
	unsigned char val;

	spin_lock_irq(&ice->reg_lock);
	if (is_spdif_master(ice)) {
		ucontrol->value.enumerated.item[0] = 13;
	} else {
		val = xlate[inb(ICEMT(ice, RATE)) & 15];
		if (val == 255) {
			snd_BUG();
			val = 0;
		}
		ucontrol->value.enumerated.item[0] = val;
	}
	spin_unlock_irq(&ice->reg_lock);
	return 0;
}