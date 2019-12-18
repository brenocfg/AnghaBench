#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_korg1212 {int /*<<< orphan*/  lock; TYPE_3__* sharedBufferPtr; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_4__ {int /*<<< orphan*/ * item; } ;
struct TYPE_5__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/ * routeData; } ;

/* Variables and functions */
 struct snd_korg1212* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_korg1212_control_route_get(struct snd_kcontrol *kcontrol,
					  struct snd_ctl_elem_value *u)
{
	struct snd_korg1212 *korg1212 = snd_kcontrol_chip(kcontrol);
        int i;

	spin_lock_irq(&korg1212->lock);

	i = kcontrol->private_value;
	u->value.enumerated.item[0] = korg1212->sharedBufferPtr->routeData[i];

	if (i >= 8) 
		u->value.enumerated.item[1] = korg1212->sharedBufferPtr->routeData[i+1];

        spin_unlock_irq(&korg1212->lock);

        return 0;
}