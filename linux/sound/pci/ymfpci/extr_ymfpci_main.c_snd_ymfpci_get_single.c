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
struct snd_ymfpci {int dummy; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
#define  YDSXGR_SPDIFINCTRL 129 
#define  YDSXGR_SPDIFOUTCTRL 128 
 struct snd_ymfpci* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned int snd_ymfpci_readl (struct snd_ymfpci*,int) ; 

__attribute__((used)) static int snd_ymfpci_get_single(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	int reg = kcontrol->private_value & 0xffff;
	unsigned int shift = (kcontrol->private_value >> 16) & 0xff;
	unsigned int mask = 1;
	
	switch (reg) {
	case YDSXGR_SPDIFOUTCTRL: break;
	case YDSXGR_SPDIFINCTRL: break;
	default: return -EINVAL;
	}
	ucontrol->value.integer.value[0] =
		(snd_ymfpci_readl(chip, reg) >> shift) & mask;
	return 0;
}