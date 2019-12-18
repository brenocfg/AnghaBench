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
typedef  int u32 ;
typedef  int u16 ;
struct mdev_state {int* bar_mask; int* vconfig; int /*<<< orphan*/  mdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  PCI_BASE_ADDRESS_0 129 
#define  PCI_BASE_ADDRESS_2 128 
 int PCI_BASE_ADDRESS_MEM_MASK ; 
 int /*<<< orphan*/  STORE_LE32 (int*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int) ; 
 struct device* mdev_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_pci_cfg_write(struct mdev_state *mdev_state, u16 offset,
				 char *buf, u32 count)
{
	struct device *dev = mdev_dev(mdev_state->mdev);
	int index = (offset - PCI_BASE_ADDRESS_0) / 0x04;
	u32 cfg_addr;

	switch (offset) {
	case PCI_BASE_ADDRESS_0:
	case PCI_BASE_ADDRESS_2:
		cfg_addr = *(u32 *)buf;

		if (cfg_addr == 0xffffffff) {
			cfg_addr = (cfg_addr & mdev_state->bar_mask[index]);
		} else {
			cfg_addr &= PCI_BASE_ADDRESS_MEM_MASK;
			if (cfg_addr)
				dev_info(dev, "BAR #%d @ 0x%x\n",
					 index, cfg_addr);
		}

		cfg_addr |= (mdev_state->vconfig[offset] &
			     ~PCI_BASE_ADDRESS_MEM_MASK);
		STORE_LE32(&mdev_state->vconfig[offset], cfg_addr);
		break;
	}
}