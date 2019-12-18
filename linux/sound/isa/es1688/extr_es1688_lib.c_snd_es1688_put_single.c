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
struct snd_es1688 {int /*<<< orphan*/  reg_lock; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 unsigned char snd_es1688_mixer_read (struct snd_es1688*,int) ; 
 int /*<<< orphan*/  snd_es1688_mixer_write (struct snd_es1688*,int,unsigned char) ; 
 struct snd_es1688* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_es1688_put_single(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_es1688 *chip = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	int reg = kcontrol->private_value & 0xff;
	int shift = (kcontrol->private_value >> 8) & 0xff;
	int mask = (kcontrol->private_value >> 16) & 0xff;
	int invert = (kcontrol->private_value >> 24) & 0xff;
	int change;
	unsigned char oval, nval;
	
	nval = (ucontrol->value.integer.value[0] & mask);
	if (invert)
		nval = mask - nval;
	nval <<= shift;
	spin_lock_irqsave(&chip->reg_lock, flags);
	oval = snd_es1688_mixer_read(chip, reg);
	nval = (oval & ~(mask << shift)) | nval;
	change = nval != oval;
	if (change)
		snd_es1688_mixer_write(chip, reg, nval);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return change;
}