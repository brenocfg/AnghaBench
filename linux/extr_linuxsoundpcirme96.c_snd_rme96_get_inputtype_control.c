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
struct TYPE_5__ {unsigned int* item; } ;
struct TYPE_6__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct rme96 {int rev; int /*<<< orphan*/  lock; TYPE_1__* pci; } ;
struct TYPE_4__ {int device; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_RME_DIGI96 131 
#define  PCI_DEVICE_ID_RME_DIGI96_8 130 
#define  PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST 129 
#define  PCI_DEVICE_ID_RME_DIGI96_8_PRO 128 
 unsigned int RME96_INPUT_ANALOG ; 
 unsigned int RME96_INPUT_XLR ; 
 int /*<<< orphan*/  snd_BUG () ; 
 struct rme96* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned int snd_rme96_getinputtype (struct rme96*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_rme96_get_inputtype_control(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	unsigned int items = 3;
	
	spin_lock_irq(&rme96->lock);
	ucontrol->value.enumerated.item[0] = snd_rme96_getinputtype(rme96);
	
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
			/* for handling PST case, (INPUT_ANALOG is moved to INPUT_XLR */
			if (ucontrol->value.enumerated.item[0] == RME96_INPUT_ANALOG) {
				ucontrol->value.enumerated.item[0] = RME96_INPUT_XLR;
			}
			items = 4;
		} else {
			items = 5;
		}
		break;
	default:
		snd_BUG();
		break;
	}
	if (ucontrol->value.enumerated.item[0] >= items) {
		ucontrol->value.enumerated.item[0] = items - 1;
	}
	
	spin_unlock_irq(&rme96->lock);
	return 0;
}