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
struct snd_kcontrol {int private_value; } ;
struct TYPE_5__ {int /*<<< orphan*/  max; scalar_t__ min; } ;
struct TYPE_6__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_info {TYPE_2__ value; int /*<<< orphan*/  count; int /*<<< orphan*/  type; } ;
struct lola {TYPE_4__* pin; } ;
struct TYPE_8__ {TYPE_3__* pins; int /*<<< orphan*/  num_pins; } ;
struct TYPE_7__ {int /*<<< orphan*/  amp_num_steps; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
 struct lola* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int lola_analog_vol_info(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_info *uinfo)
{
	struct lola *chip = snd_kcontrol_chip(kcontrol);
	int dir = kcontrol->private_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = chip->pin[dir].num_pins;
	uinfo->value.integer.min = 0;
	uinfo->value.integer.max = chip->pin[dir].pins[0].amp_num_steps;
	return 0;
}