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
 unsigned short PCM_MIN ; 
 int /*<<< orphan*/  WM_DAC_DIG_MASTER_ATTEN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int wm_get (struct snd_ice1712*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm_pcm_vol_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	unsigned short val;

	mutex_lock(&ice->gpio_mutex);
	val = wm_get(ice, WM_DAC_DIG_MASTER_ATTEN) & 0xff;
	val = val > PCM_MIN ? (val - PCM_MIN) : 0;
	ucontrol->value.integer.value[0] = val;
	mutex_unlock(&ice->gpio_mutex);
	return 0;
}