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
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM_DAC_CTRL1 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned short wm_get (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm_put (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  wm_put_nocache (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static int wm_chswap_put(struct snd_kcontrol *kcontrol,
			 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	unsigned short val, oval;
	int change = 0;

	mutex_lock(&ice->gpio_mutex);
	oval = wm_get(ice, WM_DAC_CTRL1);
	val = oval & 0x0f;
	if (ucontrol->value.integer.value[0])
		val |= 0x60;
	else
		val |= 0x90;
	if (val != oval) {
		wm_put(ice, WM_DAC_CTRL1, val);
		wm_put_nocache(ice, WM_DAC_CTRL1, val);
		change = 1;
	}
	mutex_unlock(&ice->gpio_mutex);
	return change;
}