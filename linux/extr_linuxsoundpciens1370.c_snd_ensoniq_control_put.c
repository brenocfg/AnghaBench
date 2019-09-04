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
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct ensoniq {int ctrl; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL ; 
 int /*<<< orphan*/  ES_REG (struct ensoniq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 
 struct ensoniq* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ensoniq_control_put(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_value *ucontrol)
{
	struct ensoniq *ensoniq = snd_kcontrol_chip(kcontrol);
	int mask = kcontrol->private_value;
	unsigned int nval;
	int change;
	
	nval = ucontrol->value.integer.value[0] ? mask : 0;
	spin_lock_irq(&ensoniq->reg_lock);
	change = (ensoniq->ctrl & mask) != nval;
	ensoniq->ctrl &= ~mask;
	ensoniq->ctrl |= nval;
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	spin_unlock_irq(&ensoniq->reg_lock);
	return change;
}