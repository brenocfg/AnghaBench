#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_pci_quirk {int value; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct snd_pci_quirk* snd_pci_quirk_lookup (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pci_quirk_name (struct snd_pci_quirk const*) ; 
 int /*<<< orphan*/  spdif_aclink_defaults ; 

__attribute__((used)) static int check_default_spdif_aclink(struct pci_dev *pci)
{
	const struct snd_pci_quirk *w;

	w = snd_pci_quirk_lookup(pci, spdif_aclink_defaults);
	if (w) {
		if (w->value)
			dev_dbg(&pci->dev,
				"Using SPDIF over AC-Link for %s\n",
				    snd_pci_quirk_name(w));
		else
			dev_dbg(&pci->dev,
				"Using integrated SPDIF DMA for %s\n",
				    snd_pci_quirk_name(w));
		return w->value;
	}
	return 0;
}