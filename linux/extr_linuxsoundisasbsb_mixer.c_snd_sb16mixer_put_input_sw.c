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
struct snd_sb {int /*<<< orphan*/  mixer_lock; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 struct snd_sb* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned char snd_sbmixer_read (struct snd_sb*,int) ; 
 int /*<<< orphan*/  snd_sbmixer_write (struct snd_sb*,int,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_sb16mixer_put_input_sw(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_sb *sb = snd_kcontrol_chip(kcontrol);
	unsigned long flags;
	int reg1 = kcontrol->private_value & 0xff;
	int reg2 = (kcontrol->private_value >> 8) & 0xff;
	int left_shift = (kcontrol->private_value >> 16) & 0x0f;
	int right_shift = (kcontrol->private_value >> 24) & 0x0f;
	int change;
	unsigned char val1, val2, oval1, oval2;

	spin_lock_irqsave(&sb->mixer_lock, flags);
	oval1 = snd_sbmixer_read(sb, reg1);
	oval2 = snd_sbmixer_read(sb, reg2);
	val1 = oval1 & ~((1 << left_shift) | (1 << right_shift));
	val2 = oval2 & ~((1 << left_shift) | (1 << right_shift));
	val1 |= (ucontrol->value.integer.value[0] & 1) << left_shift;
	val2 |= (ucontrol->value.integer.value[1] & 1) << left_shift;
	val1 |= (ucontrol->value.integer.value[2] & 1) << right_shift;
	val2 |= (ucontrol->value.integer.value[3] & 1) << right_shift;
	change = val1 != oval1 || val2 != oval2;
	if (change) {
		snd_sbmixer_write(sb, reg1, val1);
		snd_sbmixer_write(sb, reg2, val2);
	}
	spin_unlock_irqrestore(&sb->mixer_lock, flags);
	return change;
}