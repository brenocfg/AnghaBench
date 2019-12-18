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
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct cmipci_sb_reg {int mask; int left_shift; int right_shift; scalar_t__ left_reg; scalar_t__ right_reg; scalar_t__ stereo; scalar_t__ invert; } ;
struct cmipci {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmipci_sb_reg_decode (struct cmipci_sb_reg*,int /*<<< orphan*/ ) ; 
 int snd_cmipci_mixer_read (struct cmipci*,scalar_t__) ; 
 int /*<<< orphan*/  snd_cmipci_mixer_write (struct cmipci*,scalar_t__,int) ; 
 struct cmipci* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cmipci_put_volume(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct cmipci *cm = snd_kcontrol_chip(kcontrol);
	struct cmipci_sb_reg reg;
	int change;
	int left, right, oleft, oright;

	cmipci_sb_reg_decode(&reg, kcontrol->private_value);
	left = ucontrol->value.integer.value[0] & reg.mask;
	if (reg.invert)
		left = reg.mask - left;
	left <<= reg.left_shift;
	if (reg.stereo) {
		right = ucontrol->value.integer.value[1] & reg.mask;
		if (reg.invert)
			right = reg.mask - right;
		right <<= reg.right_shift;
	} else
		right = 0;
	spin_lock_irq(&cm->reg_lock);
	oleft = snd_cmipci_mixer_read(cm, reg.left_reg);
	left |= oleft & ~(reg.mask << reg.left_shift);
	change = left != oleft;
	if (reg.stereo) {
		if (reg.left_reg != reg.right_reg) {
			snd_cmipci_mixer_write(cm, reg.left_reg, left);
			oright = snd_cmipci_mixer_read(cm, reg.right_reg);
		} else
			oright = left;
		right |= oright & ~(reg.mask << reg.right_shift);
		change |= right != oright;
		snd_cmipci_mixer_write(cm, reg.right_reg, right);
	} else
		snd_cmipci_mixer_write(cm, reg.left_reg, left);
	spin_unlock_irq(&cm->reg_lock);
	return change;
}