#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_info {int dummy; } ;
struct rme96 {int rev; TYPE_1__* pci; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PCI_DEVICE_ID_RME_DIGI96 131 
#define  PCI_DEVICE_ID_RME_DIGI96_8 130 
#define  PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST 129 
#define  PCI_DEVICE_ID_RME_DIGI96_8_PRO 128 
 int /*<<< orphan*/  snd_BUG () ; 
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int,char const**) ; 
 struct rme96* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int
snd_rme96_info_inputtype_control(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
	static const char * const _texts[5] = {
		"Optical", "Coaxial", "Internal", "XLR", "Analog"
	};
	struct rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	const char *texts[5] = {
		_texts[0], _texts[1], _texts[2], _texts[3], _texts[4]
	};
	int num_items;
	
	switch (rme96->pci->device) {
	case PCI_DEVICE_ID_RME_DIGI96:
	case PCI_DEVICE_ID_RME_DIGI96_8:
		num_items = 3;
		break;
	case PCI_DEVICE_ID_RME_DIGI96_8_PRO:
		num_items = 4;
		break;
	case PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST:
		if (rme96->rev > 4) {
			/* PST */
			num_items = 4;
			texts[3] = _texts[4]; /* Analog instead of XLR */
		} else {
			/* PAD */
			num_items = 5;
		}
		break;
	default:
		snd_BUG();
		return -EINVAL;
	}
	return snd_ctl_enum_info(uinfo, 1, num_items, texts);
}