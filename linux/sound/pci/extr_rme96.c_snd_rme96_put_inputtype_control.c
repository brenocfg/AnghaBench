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
struct rme96 {int rev; int /*<<< orphan*/  lock; TYPE_3__* pci; } ;
struct TYPE_6__ {int device; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_RME_DIGI96 131 
#define  PCI_DEVICE_ID_RME_DIGI96_8 130 
#define  PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST 129 
#define  PCI_DEVICE_ID_RME_DIGI96_8_PRO 128 
 unsigned int RME96_INPUT_ANALOG ; 
 unsigned int RME96_INPUT_XLR ; 
 int /*<<< orphan*/  snd_BUG () ; 
 struct rme96* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_rme96_getinputtype (struct rme96*) ; 
 int /*<<< orphan*/  snd_rme96_setinputtype (struct rme96*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_rme96_put_inputtype_control(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	unsigned int val;
	int change, items = 3;
	
	switch (rme96->pci->device) {
	case PCI_DEVICE_ID_RME_DIGI96:
	case PCI_DEVICE_ID_RME_DIGI96_8:
		items = 3;
		break;
	case PCI_DEVICE_ID_RME_DIGI96_8_PRO:
		items = 4;
		break;
	case PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST:
		if (rme96->rev > 4) {
			items = 4;
		} else {
			items = 5;
		}
		break;
	default:
		snd_BUG();
		break;
	}
	val = ucontrol->value.enumerated.item[0] % items;
	
	/* special case for PST */
	if (rme96->pci->device == PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST && rme96->rev > 4) {
		if (val == RME96_INPUT_XLR) {
			val = RME96_INPUT_ANALOG;
		}
	}
	
	spin_lock_irq(&rme96->lock);
	change = (int)val != snd_rme96_getinputtype(rme96);
	snd_rme96_setinputtype(rme96, val);
	spin_unlock_irq(&rme96->lock);
	return change;
}