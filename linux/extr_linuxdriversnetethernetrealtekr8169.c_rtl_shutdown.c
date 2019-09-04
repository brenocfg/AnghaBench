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
struct rtl8169_private {scalar_t__ saved_wolopts; } ;
struct pci_dev {int dummy; } ;
struct net_device {int /*<<< orphan*/  perm_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 scalar_t__ SYSTEM_POWER_OFF ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_wake_from_d3 (struct pci_dev*,int) ; 
 int /*<<< orphan*/  rtl8169_hw_reset (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8169_net_suspend (struct net_device*) ; 
 int /*<<< orphan*/  rtl_rar_set (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_wol_shutdown_quirk (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_wol_suspend_quirk (struct rtl8169_private*) ; 
 scalar_t__ system_state ; 

__attribute__((used)) static void rtl_shutdown(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct rtl8169_private *tp = netdev_priv(dev);

	rtl8169_net_suspend(dev);

	/* Restore original MAC address */
	rtl_rar_set(tp, dev->perm_addr);

	rtl8169_hw_reset(tp);

	if (system_state == SYSTEM_POWER_OFF) {
		if (tp->saved_wolopts) {
			rtl_wol_suspend_quirk(tp);
			rtl_wol_shutdown_quirk(tp);
		}

		pci_wake_from_d3(pdev, true);
		pci_set_power_state(pdev, PCI_D3hot);
	}
}