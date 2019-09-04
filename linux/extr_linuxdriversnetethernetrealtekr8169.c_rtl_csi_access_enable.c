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
typedef  int u32 ;
struct rtl8169_private {int /*<<< orphan*/  dev; struct pci_dev* pci_dev; } ;
struct pci_dev {int cfg_size; } ;

/* Variables and functions */
 scalar_t__ PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  netdev_notice_once (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_write_config_byte (struct pci_dev*,int,int) ; 
 int rtl_csi_read (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_csi_write (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static void rtl_csi_access_enable(struct rtl8169_private *tp, u8 val)
{
	struct pci_dev *pdev = tp->pci_dev;
	u32 csi;

	/* According to Realtek the value at config space address 0x070f
	 * controls the L0s/L1 entrance latency. We try standard ECAM access
	 * first and if it fails fall back to CSI.
	 */
	if (pdev->cfg_size > 0x070f &&
	    pci_write_config_byte(pdev, 0x070f, val) == PCIBIOS_SUCCESSFUL)
		return;

	netdev_notice_once(tp->dev,
		"No native access to PCI extended config space, falling back to CSI\n");
	csi = rtl_csi_read(tp, 0x070c) & 0x00ffffff;
	rtl_csi_write(tp, 0x070c, csi | val << 24);
}