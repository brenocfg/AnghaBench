#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtl_ps_ctl {int reg_rfps_level; int support_aspm; int support_backdoor; int /*<<< orphan*/  const_amdpci_aspm; } ;
struct TYPE_4__ {scalar_t__ hw_type; } ;
struct rtl_priv {TYPE_2__ rtlhal; } ;
struct TYPE_3__ {int pcibridge_vendor; } ;
struct rtl_pci_priv {TYPE_1__ ndis_adapter; } ;
struct rtl_pci {int const_pci_aspm; int const_hwsw_rfoff_d3; int const_support_pciaspm; int /*<<< orphan*/  pdev; int /*<<< orphan*/  const_amdpci_aspm; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ HARDWARE_TYPE_RTL8192SE ; 
 int PCI_BRIDGE_VENDOR_INTEL ; 
 int RT_RF_LPS_LEVEL_ASPM ; 
 int RT_RF_OFF_LEVL_ASPM ; 
 int RT_RF_OFF_LEVL_CLK_REQ ; 
 int RT_RF_OFF_LEVL_HALT_NIC ; 
 int RT_RF_OFF_LEVL_PCI_D3 ; 
 int RT_RF_PS_LEVEL_ALWAYS_ASPM ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct rtl_pci* rtl_pcidev (struct rtl_pci_priv*) ; 
 struct rtl_pci_priv* rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 

__attribute__((used)) static void _rtl_pci_update_default_setting(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 pcibridge_vendor = pcipriv->ndis_adapter.pcibridge_vendor;
	u8 init_aspm;

	ppsc->reg_rfps_level = 0;
	ppsc->support_aspm = false;

	/*Update PCI ASPM setting */
	ppsc->const_amdpci_aspm = rtlpci->const_amdpci_aspm;
	switch (rtlpci->const_pci_aspm) {
	case 0:
		/*No ASPM */
		break;

	case 1:
		/*ASPM dynamically enabled/disable. */
		ppsc->reg_rfps_level |= RT_RF_LPS_LEVEL_ASPM;
		break;

	case 2:
		/*ASPM with Clock Req dynamically enabled/disable. */
		ppsc->reg_rfps_level |= (RT_RF_LPS_LEVEL_ASPM |
					 RT_RF_OFF_LEVL_CLK_REQ);
		break;

	case 3:
		/* Always enable ASPM and Clock Req
		 * from initialization to halt.
		 */
		ppsc->reg_rfps_level &= ~(RT_RF_LPS_LEVEL_ASPM);
		ppsc->reg_rfps_level |= (RT_RF_PS_LEVEL_ALWAYS_ASPM |
					 RT_RF_OFF_LEVL_CLK_REQ);
		break;

	case 4:
		/* Always enable ASPM without Clock Req
		 * from initialization to halt.
		 */
		ppsc->reg_rfps_level &= ~(RT_RF_LPS_LEVEL_ASPM |
					  RT_RF_OFF_LEVL_CLK_REQ);
		ppsc->reg_rfps_level |= RT_RF_PS_LEVEL_ALWAYS_ASPM;
		break;
	}

	ppsc->reg_rfps_level |= RT_RF_OFF_LEVL_HALT_NIC;

	/*Update Radio OFF setting */
	switch (rtlpci->const_hwsw_rfoff_d3) {
	case 1:
		if (ppsc->reg_rfps_level & RT_RF_LPS_LEVEL_ASPM)
			ppsc->reg_rfps_level |= RT_RF_OFF_LEVL_ASPM;
		break;

	case 2:
		if (ppsc->reg_rfps_level & RT_RF_LPS_LEVEL_ASPM)
			ppsc->reg_rfps_level |= RT_RF_OFF_LEVL_ASPM;
		ppsc->reg_rfps_level |= RT_RF_OFF_LEVL_HALT_NIC;
		break;

	case 3:
		ppsc->reg_rfps_level |= RT_RF_OFF_LEVL_PCI_D3;
		break;
	}

	/*Set HW definition to determine if it supports ASPM. */
	switch (rtlpci->const_support_pciaspm) {
	case 0:
		/*Not support ASPM. */
		ppsc->support_aspm = false;
		break;
	case 1:
		/*Support ASPM. */
		ppsc->support_aspm = true;
		ppsc->support_backdoor = true;
		break;
	case 2:
		/*ASPM value set by chipset. */
		if (pcibridge_vendor == PCI_BRIDGE_VENDOR_INTEL)
			ppsc->support_aspm = true;
		break;
	default:
		pr_err("switch case %#x not processed\n",
		       rtlpci->const_support_pciaspm);
		break;
	}

	/* toshiba aspm issue, toshiba will set aspm selfly
	 * so we should not set aspm in driver
	 */
	pci_read_config_byte(rtlpci->pdev, 0x80, &init_aspm);
	if (rtlpriv->rtlhal.hw_type == HARDWARE_TYPE_RTL8192SE &&
	    init_aspm == 0x43)
		ppsc->support_aspm = false;
}