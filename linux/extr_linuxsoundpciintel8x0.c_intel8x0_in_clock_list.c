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
struct snd_pci_quirk {int /*<<< orphan*/  value; } ;
struct pci_dev {int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; } ;
struct intel8x0 {TYPE_2__* ac97_bus; TYPE_1__* card; struct pci_dev* pci; } ;
struct TYPE_4__ {int /*<<< orphan*/  clock; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel8x0_clock_list ; 
 struct snd_pci_quirk* snd_pci_quirk_lookup (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel8x0_in_clock_list(struct intel8x0 *chip)
{
	struct pci_dev *pci = chip->pci;
	const struct snd_pci_quirk *wl;

	wl = snd_pci_quirk_lookup(pci, intel8x0_clock_list);
	if (!wl)
		return 0;
	dev_info(chip->card->dev, "white list rate for %04x:%04x is %i\n",
	       pci->subsystem_vendor, pci->subsystem_device, wl->value);
	chip->ac97_bus->clock = wl->value;
	return 1;
}