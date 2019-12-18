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
 int /*<<< orphan*/  atiixp_quirks ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 struct snd_pci_quirk* snd_pci_quirk_lookup (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pci_quirk_name (struct snd_pci_quirk const*) ; 

__attribute__((used)) static int ac97_probing_bugs(struct pci_dev *pci)
{
	const struct snd_pci_quirk *q;

	q = snd_pci_quirk_lookup(pci, atiixp_quirks);
	if (q) {
		dev_dbg(&pci->dev, "atiixp quirk for %s.  Forcing codec %d\n",
			snd_pci_quirk_name(q), q->value);
		return q->value;
	}
	/* this hardware doesn't need workarounds.  Probe for codec */
	return -1;
}