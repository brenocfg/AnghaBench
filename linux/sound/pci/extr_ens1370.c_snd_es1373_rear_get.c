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
struct TYPE_4__ {int* value; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct ensoniq {int cssr; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int ES_1373_REAR_BIT24 ; 
 int ES_1373_REAR_BIT26 ; 
 int ES_1373_REAR_BIT27 ; 
 struct ensoniq* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_es1373_rear_get(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct ensoniq *ensoniq = snd_kcontrol_chip(kcontrol);
	int val = 0;
	
	spin_lock_irq(&ensoniq->reg_lock);
	if ((ensoniq->cssr & (ES_1373_REAR_BIT27|ES_1373_REAR_BIT26|
			      ES_1373_REAR_BIT24)) == ES_1373_REAR_BIT26)
	    	val = 1;
	ucontrol->value.integer.value[0] = val;
	spin_unlock_irq(&ensoniq->reg_lock);
	return 0;
}