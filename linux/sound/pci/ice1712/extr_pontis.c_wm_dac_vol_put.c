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
struct snd_ice1712 {int /*<<< orphan*/  gpio_mutex; } ;
struct TYPE_3__ {unsigned short* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 unsigned short DAC_MIN ; 
 int WM_DAC_ATTEN_L ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int wm_get (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  wm_put (struct snd_ice1712*,int,unsigned short) ; 
 int /*<<< orphan*/  wm_put_nocache (struct snd_ice1712*,int,unsigned short) ; 

__attribute__((used)) static int wm_dac_vol_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	unsigned short oval, nval;
	int i, idx, change = 0;

	mutex_lock(&ice->gpio_mutex);
	for (i = 0; i < 2; i++) {
		nval = ucontrol->value.integer.value[i];
		nval = (nval ? (nval + DAC_MIN) : 0) & 0xff;
		idx = WM_DAC_ATTEN_L + i;
		oval = wm_get(ice, idx) & 0xff;
		if (oval != nval) {
			wm_put(ice, idx, nval);
			wm_put_nocache(ice, idx, nval | 0x100);
			change = 1;
		}
	}
	mutex_unlock(&ice->gpio_mutex);
	return change;
}