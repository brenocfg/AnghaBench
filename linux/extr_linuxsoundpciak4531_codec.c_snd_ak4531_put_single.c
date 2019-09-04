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

__attribute__((used)) static int snd_ak4531_put_single(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ak4531 *ak4531 = snd_kcontrol_chip(kcontrol);
	int reg = kcontrol->private_value & 0xff;
	int shift = (kcontrol->private_value >> 16) & 0x07;
	int mask = (kcontrol->private_value >> 24) & 0xff;
	int invert = (kcontrol->private_value >> 22) & 1;
	int change;
	int val;

	val = ucontrol->value.integer.value[0] & mask;
	if (invert) {
		val = mask - val;
	}
	val <<= shift;
	mutex_lock(&ak4531->reg_mutex);
	val = (ak4531->regs[reg] & ~(mask << shift)) | val;
	change = val != ak4531->regs[reg];
	ak4531->write(ak4531, reg, ak4531->regs[reg] = val);
	mutex_unlock(&ak4531->reg_mutex);
	return change;
}