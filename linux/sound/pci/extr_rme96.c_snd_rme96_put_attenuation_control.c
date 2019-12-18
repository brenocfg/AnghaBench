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
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct rme96 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct rme96* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_rme96_getattenuation (struct rme96*) ; 
 int /*<<< orphan*/  snd_rme96_setattenuation (struct rme96*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_rme96_put_attenuation_control(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	unsigned int val;
	int change;
	
	val = ucontrol->value.enumerated.item[0] % 4;
	spin_lock_irq(&rme96->lock);

	change = (int)val != snd_rme96_getattenuation(rme96);
	snd_rme96_setattenuation(rme96, val);
	spin_unlock_irq(&rme96->lock);
	return change;
}