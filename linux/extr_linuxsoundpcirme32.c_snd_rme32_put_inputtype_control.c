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
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int* item; } ;
struct TYPE_5__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct rme32 {int /*<<< orphan*/  lock; TYPE_3__* pci; } ;
struct TYPE_6__ {int device; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_RME_DIGI32 130 
#define  PCI_DEVICE_ID_RME_DIGI32_8 129 
#define  PCI_DEVICE_ID_RME_DIGI32_PRO 128 
 int /*<<< orphan*/  snd_BUG () ; 
 struct rme32* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 scalar_t__ snd_rme32_getinputtype (struct rme32*) ; 
 int /*<<< orphan*/  snd_rme32_setinputtype (struct rme32*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_rme32_put_inputtype_control(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct rme32 *rme32 = snd_kcontrol_chip(kcontrol);
	unsigned int val;
	int change, items = 3;

	switch (rme32->pci->device) {
	case PCI_DEVICE_ID_RME_DIGI32:
	case PCI_DEVICE_ID_RME_DIGI32_8:
		items = 3;
		break;
	case PCI_DEVICE_ID_RME_DIGI32_PRO:
		items = 4;
		break;
	default:
		snd_BUG();
		break;
	}
	val = ucontrol->value.enumerated.item[0] % items;

	spin_lock_irq(&rme32->lock);
	change = val != (unsigned int)snd_rme32_getinputtype(rme32);
	snd_rme32_setinputtype(rme32, val);
	spin_unlock_irq(&rme32->lock);
	return change;
}