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
 int VIA_DXS_48K ; 
 int VIA_DXS_SRC ; 
 int VIA_REV_8235 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dxs_whitelist ; 
 struct snd_pci_quirk* snd_pci_quirk_lookup (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pci_quirk_name (struct snd_pci_quirk const*) ; 

__attribute__((used)) static int check_dxs_list(struct pci_dev *pci, int revision)
{
	const struct snd_pci_quirk *w;

	w = snd_pci_quirk_lookup(pci, dxs_whitelist);
	if (w) {
		dev_dbg(&pci->dev, "DXS white list for %s found\n",
			    snd_pci_quirk_name(w));
		return w->value;
	}

	/* for newer revision, default to DXS_SRC */
	if (revision >= VIA_REV_8235)
		return VIA_DXS_SRC;

	/*
	 * not detected, try 48k rate only to be sure.
	 */
	dev_info(&pci->dev, "Assuming DXS channels with 48k fixed sample rate.\n");
	dev_info(&pci->dev, "         Please try dxs_support=5 option\n");
	dev_info(&pci->dev, "         and report if it works on your machine.\n");
	dev_info(&pci->dev, "         For more details, read ALSA-Configuration.txt.\n");
	return VIA_DXS_48K;
}