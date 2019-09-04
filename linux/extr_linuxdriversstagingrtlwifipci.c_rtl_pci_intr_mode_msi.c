#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtl_priv {int dummy; } ;
struct rtl_pci_priv {int dummy; } ;
struct rtl_pci {int using_msi; TYPE_1__* pdev; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int COMP_INIT ; 
 int COMP_INTR ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _rtl_pci_interrupt ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_1__*) ; 
 int pci_enable_msi (TYPE_1__*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_hw*) ; 
 struct rtl_pci* rtl_pcidev (struct rtl_pci_priv*) ; 
 struct rtl_pci_priv* rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static int rtl_pci_intr_mode_msi(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(pcipriv);
	int ret;

	ret = pci_enable_msi(rtlpci->pdev);
	if (ret < 0)
		return ret;

	ret = request_irq(rtlpci->pdev->irq, &_rtl_pci_interrupt,
			  IRQF_SHARED, KBUILD_MODNAME, hw);
	if (ret < 0) {
		pci_disable_msi(rtlpci->pdev);
		return ret;
	}

	rtlpci->using_msi = true;

	RT_TRACE(rtlpriv, COMP_INIT | COMP_INTR, DBG_DMESG,
		 "MSI Interrupt Mode!\n");
	return 0;
}