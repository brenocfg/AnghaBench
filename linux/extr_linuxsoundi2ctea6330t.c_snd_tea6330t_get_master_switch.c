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
struct tea6330t {scalar_t__* regs; int /*<<< orphan*/  bus; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 size_t TEA6330T_SADDR_VOLUME_LEFT ; 
 size_t TEA6330T_SADDR_VOLUME_RIGHT ; 
 int /*<<< orphan*/  snd_i2c_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_i2c_unlock (int /*<<< orphan*/ ) ; 
 struct tea6330t* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_tea6330t_get_master_switch(struct snd_kcontrol *kcontrol,
					  struct snd_ctl_elem_value *ucontrol)
{
	struct tea6330t *tea = snd_kcontrol_chip(kcontrol);
	
	snd_i2c_lock(tea->bus);
	ucontrol->value.integer.value[0] = tea->regs[TEA6330T_SADDR_VOLUME_LEFT] == 0 ? 0 : 1;
	ucontrol->value.integer.value[1] = tea->regs[TEA6330T_SADDR_VOLUME_RIGHT] == 0 ? 0 : 1;
	snd_i2c_unlock(tea->bus);
	return 0;
}