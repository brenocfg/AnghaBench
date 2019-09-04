#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * value; } ;
struct TYPE_6__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_7__ {int /*<<< orphan*/  swap_mic_linein; } ;
struct TYPE_8__ {TYPE_3__ ad18xx; } ;
struct snd_ac97 {TYPE_4__ spec; } ;

/* Variables and functions */
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ac97_ad1986_miclisel_get(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);

	ucontrol->value.integer.value[0] = ac97->spec.ad18xx.swap_mic_linein;
	return 0;
}