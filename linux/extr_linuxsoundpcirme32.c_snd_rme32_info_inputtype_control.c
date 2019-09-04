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
struct rme32 {TYPE_1__* pci; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PCI_DEVICE_ID_RME_DIGI32 130 
#define  PCI_DEVICE_ID_RME_DIGI32_8 129 
#define  PCI_DEVICE_ID_RME_DIGI32_PRO 128 
 int /*<<< orphan*/  snd_BUG () ; 
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int,char const* const*) ; 
 struct rme32* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int
snd_rme32_info_inputtype_control(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_info *uinfo)
{
	struct rme32 *rme32 = snd_kcontrol_chip(kcontrol);
	static const char * const texts[4] = {
		"Optical", "Coaxial", "Internal", "XLR"
	};
	int num_items;

	switch (rme32->pci->device) {
	case PCI_DEVICE_ID_RME_DIGI32:
	case PCI_DEVICE_ID_RME_DIGI32_8:
		num_items = 3;
		break;
	case PCI_DEVICE_ID_RME_DIGI32_PRO:
		num_items = 4;
		break;
	default:
		snd_BUG();
		return -EINVAL;
	}
	return snd_ctl_enum_info(uinfo, 1, num_items, texts);
}