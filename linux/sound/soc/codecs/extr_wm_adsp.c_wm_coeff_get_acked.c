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
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */

__attribute__((used)) static int wm_coeff_get_acked(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *ucontrol)
{
	/*
	 * Although it's not useful to read an acked control, we must satisfy
	 * user-side assumptions that all controls are readable and that a
	 * write of the same value should be filtered out (it's valid to send
	 * the same event number again to the firmware). We therefore return 0,
	 * meaning "no event" so valid event numbers will always be a change
	 */
	ucontrol->value.integer.value[0] = 0;

	return 0;
}