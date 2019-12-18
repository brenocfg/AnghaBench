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
struct snd_pci_quirk {int /*<<< orphan*/  subdevice; int /*<<< orphan*/  subvendor; } ;
struct azx {int /*<<< orphan*/  bus; TYPE_1__* card; int /*<<< orphan*/  pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pm_blacklist ; 
 int power_save ; 
 int /*<<< orphan*/  power_save_blacklist ; 
 int /*<<< orphan*/  snd_hda_set_power_save (int /*<<< orphan*/ *,int) ; 
 struct snd_pci_quirk* snd_pci_quirk_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_default_power_save(struct azx *chip)
{
	int val = power_save;

#ifdef CONFIG_PM
	if (pm_blacklist) {
		const struct snd_pci_quirk *q;

		q = snd_pci_quirk_lookup(chip->pci, power_save_blacklist);
		if (q && val) {
			dev_info(chip->card->dev, "device %04x:%04x is on the power_save blacklist, forcing power_save to 0\n",
				 q->subvendor, q->subdevice);
			val = 0;
		}
	}
#endif /* CONFIG_PM */
	snd_hda_set_power_save(&chip->bus, val * 1000);
}