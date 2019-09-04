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
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_cs46xx {int dummy; } ;

/* Variables and functions */
 unsigned int snd_cs46xx_peek (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  snd_cs46xx_poke (struct snd_cs46xx*,int,unsigned int) ; 
 struct snd_cs46xx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_cs46xx_vol_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	int reg = kcontrol->private_value;
	unsigned int val = ((0xffff - ucontrol->value.integer.value[0]) << 16 | 
			    (0xffff - ucontrol->value.integer.value[1]));
	unsigned int old = snd_cs46xx_peek(chip, reg);
	int change = (old != val);

	if (change) {
		snd_cs46xx_poke(chip, reg, val);
	}

	return change;
}