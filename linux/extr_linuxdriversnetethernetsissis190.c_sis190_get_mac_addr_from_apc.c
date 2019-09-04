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
typedef  int u8 ;
typedef  int u16 ;
struct sis190_private {int dummy; } ;
struct pci_dev {int dummy; } ;
struct net_device {void** dev_addr; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int const*) ; 
 int EIO ; 
 unsigned int ETH_ALEN ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_SI ; 
 void* inb (int) ; 
 struct sis190_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_probe (struct sis190_private*) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis190_set_rgmii (struct sis190_private*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sis190_get_mac_addr_from_apc(struct pci_dev *pdev,
					struct net_device *dev)
{
	static const u16 ids[] = { 0x0965, 0x0966, 0x0968 };
	struct sis190_private *tp = netdev_priv(dev);
	struct pci_dev *isa_bridge;
	u8 reg, tmp8;
	unsigned int i;

	if (netif_msg_probe(tp))
		pr_info("%s: Read MAC address from APC\n", pci_name(pdev));

	for (i = 0; i < ARRAY_SIZE(ids); i++) {
		isa_bridge = pci_get_device(PCI_VENDOR_ID_SI, ids[i], NULL);
		if (isa_bridge)
			break;
	}

	if (!isa_bridge) {
		if (netif_msg_probe(tp))
			pr_info("%s: Can not find ISA bridge\n",
				pci_name(pdev));
		return -EIO;
	}

	/* Enable port 78h & 79h to access APC Registers. */
	pci_read_config_byte(isa_bridge, 0x48, &tmp8);
	reg = (tmp8 & ~0x02);
	pci_write_config_byte(isa_bridge, 0x48, reg);
	udelay(50);
	pci_read_config_byte(isa_bridge, 0x48, &reg);

        for (i = 0; i < ETH_ALEN; i++) {
                outb(0x9 + i, 0x78);
                dev->dev_addr[i] = inb(0x79);
        }

	outb(0x12, 0x78);
	reg = inb(0x79);

	sis190_set_rgmii(tp, reg);

	/* Restore the value to ISA Bridge */
	pci_write_config_byte(isa_bridge, 0x48, tmp8);
	pci_dev_put(isa_bridge);

	return 0;
}