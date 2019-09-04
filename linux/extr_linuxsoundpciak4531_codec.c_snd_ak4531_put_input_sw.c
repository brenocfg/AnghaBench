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
struct snd_ak4531 {int* regs; int /*<<< orphan*/  reg_mutex; int /*<<< orphan*/  (* write ) (struct snd_ak4531*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_ak4531* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  stub1 (struct snd_ak4531*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct snd_ak4531*,int,int) ; 

__attribute__((used)) static int snd_ak4531_put_input_sw(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ak4531 *ak4531 = snd_kcontrol_chip(kcontrol);
	int reg1 = kcontrol->private_value & 0xff;
	int reg2 = (kcontrol->private_value >> 8) & 0xff;
	int left_shift = (kcontrol->private_value >> 16) & 0x0f;
	int right_shift = (kcontrol->private_value >> 24) & 0x0f;
	int change;
	int val1, val2;

	mutex_lock(&ak4531->reg_mutex);
	val1 = ak4531->regs[reg1] & ~((1 << left_shift) | (1 << right_shift));
	val2 = ak4531->regs[reg2] & ~((1 << left_shift) | (1 << right_shift));
	val1 |= (ucontrol->value.integer.value[0] & 1) << left_shift;
	val2 |= (ucontrol->value.integer.value[1] & 1) << left_shift;
	val1 |= (ucontrol->value.integer.value[2] & 1) << right_shift;
	val2 |= (ucontrol->value.integer.value[3] & 1) << right_shift;
	change = val1 != ak4531->regs[reg1] || val2 != ak4531->regs[reg2];
	ak4531->write(ak4531, reg1, ak4531->regs[reg1] = val1);
	ak4531->write(ak4531, reg2, ak4531->regs[reg2] = val2);
	mutex_unlock(&ak4531->reg_mutex);
	return change;
}