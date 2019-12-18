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
struct snd_es18xx {scalar_t__ port; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int ES18XX_FL_INVERT ; 
 int ES18XX_FL_PMPORT ; 
 scalar_t__ ES18XX_PM ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 unsigned char snd_es18xx_reg_bits (struct snd_es18xx*,int,int,unsigned char) ; 
 struct snd_es18xx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_es18xx_put_single(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	int reg = kcontrol->private_value & 0xff;
	int shift = (kcontrol->private_value >> 8) & 0xff;
	int mask = (kcontrol->private_value >> 16) & 0xff;
	int invert = (kcontrol->private_value >> 24) & ES18XX_FL_INVERT;
	int pm_port = (kcontrol->private_value >> 24) & ES18XX_FL_PMPORT;
	unsigned char val;
	
	val = (ucontrol->value.integer.value[0] & mask);
	if (invert)
		val = mask - val;
	mask <<= shift;
	val <<= shift;
	if (pm_port) {
		unsigned char cur = inb(chip->port + ES18XX_PM);

		if ((cur & mask) == val)
			return 0;
		outb((cur & ~mask) | val, chip->port + ES18XX_PM);
		return 1;
	}

	return snd_es18xx_reg_bits(chip, reg, mask, val) != val;
}