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
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct rme32 {int wcreg; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int RME32_WCR_SEL ; 
 struct rme32* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_rme32_get_loopback_control(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct rme32 *rme32 = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&rme32->lock);
	ucontrol->value.integer.value[0] =
	    rme32->wcreg & RME32_WCR_SEL ? 0 : 1;
	spin_unlock_irq(&rme32->lock);
	return 0;
}