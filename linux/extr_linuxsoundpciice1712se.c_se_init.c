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
struct TYPE_3__ {int /*<<< orphan*/  set_pro_rate; } ;
struct TYPE_4__ {scalar_t__ subvendor; } ;
struct snd_ice1712 {int num_total_dacs; int num_total_adcs; int vt1720; TYPE_1__ gpio; TYPE_2__ eeprom; struct se_spec* spec; } ;
struct se_spec {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ VT1724_SUBDEVICE_SE200PCI ; 
 scalar_t__ VT1724_SUBDEVICE_SE90PCI ; 
 struct se_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se200pci_WM8740_init (struct snd_ice1712*) ; 
 int /*<<< orphan*/  se200pci_WM8766_init (struct snd_ice1712*) ; 
 int /*<<< orphan*/  se200pci_WM8776_init (struct snd_ice1712*) ; 
 int /*<<< orphan*/  se200pci_set_pro_rate ; 

__attribute__((used)) static int se_init(struct snd_ice1712 *ice)
{
	struct se_spec *spec;

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	ice->spec = spec;

	if (ice->eeprom.subvendor == VT1724_SUBDEVICE_SE90PCI) {
		ice->num_total_dacs = 2;
		ice->num_total_adcs = 0;
		ice->vt1720 = 1;
		return 0;

	} else if (ice->eeprom.subvendor == VT1724_SUBDEVICE_SE200PCI) {
		ice->num_total_dacs = 8;
		ice->num_total_adcs = 2;
		se200pci_WM8740_init(ice);
		se200pci_WM8766_init(ice);
		se200pci_WM8776_init(ice);
		ice->gpio.set_pro_rate = se200pci_set_pro_rate;
		return 0;
	}

	return -ENOENT;
}