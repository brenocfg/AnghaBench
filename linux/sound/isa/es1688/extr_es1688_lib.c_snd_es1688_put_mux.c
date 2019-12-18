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
struct snd_es1688 {int /*<<< orphan*/  reg_lock; } ;
struct TYPE_4__ {int* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ES1688_REC_DEV ; 
 unsigned char snd_es1688_mixer_read (struct snd_es1688*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es1688_mixer_write (struct snd_es1688*,int /*<<< orphan*/ ,unsigned char) ; 
 struct snd_es1688* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_es1688_put_mux(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_es1688 *chip = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	unsigned char oval, nval;
	int change;
	
	if (ucontrol->value.enumerated.item[0] > 8)
		return -EINVAL;
	spin_lock_irqsave(&chip->reg_lock, flags);
	oval = snd_es1688_mixer_read(chip, ES1688_REC_DEV);
	nval = (ucontrol->value.enumerated.item[0] & 7) | (oval & ~15);
	change = nval != oval;
	if (change)
		snd_es1688_mixer_write(chip, ES1688_REC_DEV, nval);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return change;
}