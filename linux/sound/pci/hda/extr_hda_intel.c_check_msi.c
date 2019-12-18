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
struct snd_pci_quirk {int value; int /*<<< orphan*/  subdevice; int /*<<< orphan*/  subvendor; } ;
struct azx {int msi; int driver_caps; TYPE_1__* card; int /*<<< orphan*/  pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AZX_DCAPS_NO_MSI ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ enable_msi ; 
 int /*<<< orphan*/  msi_black_list ; 
 struct snd_pci_quirk* snd_pci_quirk_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_msi(struct azx *chip)
{
	const struct snd_pci_quirk *q;

	if (enable_msi >= 0) {
		chip->msi = !!enable_msi;
		return;
	}
	chip->msi = 1;	/* enable MSI as default */
	q = snd_pci_quirk_lookup(chip->pci, msi_black_list);
	if (q) {
		dev_info(chip->card->dev,
			 "msi for device %04x:%04x set to %d\n",
			 q->subvendor, q->subdevice, q->value);
		chip->msi = q->value;
		return;
	}

	/* NVidia chipsets seem to cause troubles with MSI */
	if (chip->driver_caps & AZX_DCAPS_NO_MSI) {
		dev_info(chip->card->dev, "Disabling MSI\n");
		chip->msi = 0;
	}
}