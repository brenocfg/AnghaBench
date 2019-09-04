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
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
#define  SCR_AIN12_LINE 130 
#define  SCR_AIN12_LOWCUT 129 
#define  SCR_AIN12_MIC 128 
 unsigned int SCR_AIN12_SEL0 ; 
 unsigned int SCR_AIN12_SEL1 ; 
 unsigned int SCR_RELAY ; 
 unsigned int get_scr (struct snd_ice1712*) ; 
 int /*<<< orphan*/  set_scr (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int qtet_ain12_sw_put(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	unsigned int old, new, tmp, masked_old;
	old = new = get_scr(ice);
	masked_old = old & (SCR_AIN12_SEL1 | SCR_AIN12_SEL0);
	tmp = ucontrol->value.integer.value[0];
	if (tmp == 2)
		tmp = 3;	/* binary 10 is not supported */
	tmp <<= 4;	/* shifting to SCR_AIN12_SEL0 */
	if (tmp != masked_old) {
		/* change requested */
		switch (tmp) {
		case SCR_AIN12_LINE:
			new = old & ~(SCR_AIN12_SEL1 | SCR_AIN12_SEL0);
			set_scr(ice, new);
			/* turn off relay */
			new &= ~SCR_RELAY;
			set_scr(ice, new);
			break;
		case SCR_AIN12_MIC:
			/* turn on relay */
			new = old | SCR_RELAY;
			set_scr(ice, new);
			new = (new & ~SCR_AIN12_SEL1) | SCR_AIN12_SEL0;
			set_scr(ice, new);
			break;
		case SCR_AIN12_LOWCUT:
			/* turn on relay */
			new = old | SCR_RELAY;
			set_scr(ice, new);
			new |= SCR_AIN12_SEL1 | SCR_AIN12_SEL0;
			set_scr(ice, new);
			break;
		default:
			snd_BUG();
		}
		return 1;
	}
	/* no change */
	return 0;
}