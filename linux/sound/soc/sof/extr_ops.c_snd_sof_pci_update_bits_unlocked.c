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
typedef  unsigned int u32 ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,unsigned int,unsigned int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
bool snd_sof_pci_update_bits_unlocked(struct snd_sof_dev *sdev, u32 offset,
				      u32 mask, u32 value)
{
	struct pci_dev *pci = to_pci_dev(sdev->dev);
	unsigned int old, new;
	u32 ret = 0;

	pci_read_config_dword(pci, offset, &ret);
	old = ret;
	dev_dbg(sdev->dev, "Debug PCIR: %8.8x at  %8.8x\n", old & mask, offset);

	new = (old & ~mask) | (value & mask);

	if (old == new)
		return false;

	pci_write_config_dword(pci, offset, new);
	dev_dbg(sdev->dev, "Debug PCIW: %8.8x at  %8.8x\n", value,
		offset);

	return true;
}