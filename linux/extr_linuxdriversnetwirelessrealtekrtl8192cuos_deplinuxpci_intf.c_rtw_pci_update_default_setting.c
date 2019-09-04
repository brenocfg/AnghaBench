#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct pwrctrl_priv {int reg_rfps_level; void* b_support_aspm; void* b_support_backdoor; int /*<<< orphan*/  const_amdpci_aspm; } ;
struct pci_priv {int /*<<< orphan*/  pcibridge_vendor; } ;
struct dvobj_priv {int const_pci_aspm; int const_hwsw_rfoff_d3; int const_support_pciaspm; int /*<<< orphan*/  const_amdpci_aspm; struct pci_priv pcipriv; } ;
struct TYPE_4__ {struct pwrctrl_priv pwrctrlpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BRIDGE_VENDOR_INTEL ; 
 int RT_RF_LPS_LEVEL_ASPM ; 
 int RT_RF_OFF_LEVL_ASPM ; 
 int RT_RF_OFF_LEVL_CLK_REQ ; 
 int RT_RF_OFF_LEVL_HALT_NIC ; 
 int RT_RF_OFF_LEVL_PCI_D3 ; 
 int RT_RF_PS_LEVEL_ALWAYS_ASPM ; 
 void* _FALSE ; 
 void* _TRUE ; 
 struct dvobj_priv* adapter_to_dvobj (TYPE_1__*) ; 

__attribute__((used)) static void rtw_pci_update_default_setting(_adapter *padapter)
{
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);
	struct pci_priv	*pcipriv = &(pdvobjpriv->pcipriv);
	struct pwrctrl_priv	*pwrpriv = &padapter->pwrctrlpriv;

	//reset pPSC->reg_rfps_level & priv->b_support_aspm
	pwrpriv->reg_rfps_level = 0;
	pwrpriv->b_support_aspm = 0;

	// Dynamic Mechanism,
	//rtw_hal_set_def_var(pAdapter, HAL_DEF_INIT_GAIN, &(pDevice->InitGainState));

	// Update PCI ASPM setting
	pwrpriv->const_amdpci_aspm = pdvobjpriv->const_amdpci_aspm;
	switch (pdvobjpriv->const_pci_aspm) {
		case 0:		// No ASPM
			break;

		case 1:		// ASPM dynamically enabled/disable.
			pwrpriv->reg_rfps_level |= RT_RF_LPS_LEVEL_ASPM;
			break;

		case 2:		// ASPM with Clock Req dynamically enabled/disable.
			pwrpriv->reg_rfps_level |= (RT_RF_LPS_LEVEL_ASPM | RT_RF_OFF_LEVL_CLK_REQ);
			break;

		case 3:		// Always enable ASPM and Clock Req from initialization to halt.
			pwrpriv->reg_rfps_level &= ~(RT_RF_LPS_LEVEL_ASPM);
			pwrpriv->reg_rfps_level |= (RT_RF_PS_LEVEL_ALWAYS_ASPM | RT_RF_OFF_LEVL_CLK_REQ);
			break;

		case 4:		// Always enable ASPM without Clock Req from initialization to halt.
			pwrpriv->reg_rfps_level &= ~(RT_RF_LPS_LEVEL_ASPM | RT_RF_OFF_LEVL_CLK_REQ);
			pwrpriv->reg_rfps_level |= RT_RF_PS_LEVEL_ALWAYS_ASPM;
			break;
	}

	pwrpriv->reg_rfps_level |= RT_RF_OFF_LEVL_HALT_NIC;

	// Update Radio OFF setting
	switch (pdvobjpriv->const_hwsw_rfoff_d3) {
		case 1:
			if (pwrpriv->reg_rfps_level & RT_RF_LPS_LEVEL_ASPM)
				pwrpriv->reg_rfps_level |= RT_RF_OFF_LEVL_ASPM;
			break;

		case 2:
			if (pwrpriv->reg_rfps_level & RT_RF_LPS_LEVEL_ASPM)
				pwrpriv->reg_rfps_level |= RT_RF_OFF_LEVL_ASPM;
			pwrpriv->reg_rfps_level |= RT_RF_OFF_LEVL_HALT_NIC;
			break;

		case 3:
			pwrpriv->reg_rfps_level |= RT_RF_OFF_LEVL_PCI_D3;
			break;
	}

	// Update Rx 2R setting
	//pPSC->reg_rfps_level |= ((pDevice->RegLPS2RDisable) ? RT_RF_LPS_DISALBE_2R : 0);

	//
	// Set HW definition to determine if it supports ASPM.
	//
	switch (pdvobjpriv->const_support_pciaspm) {
		case 0:	// Not support ASPM.
			{
				u8	b_support_aspm = _FALSE;
				pwrpriv->b_support_aspm = b_support_aspm;
			}
			break;

		case 1:	// Support ASPM.
			{
				u8	b_support_aspm = _TRUE;
				u8	b_support_backdoor = _TRUE;

				pwrpriv->b_support_aspm = b_support_aspm;

				/*if(pAdapter->MgntInfo.CustomerID == RT_CID_TOSHIBA &&
					pcipriv->pcibridge_vendor == PCI_BRIDGE_VENDOR_AMD &&
					!pcipriv->amd_l1_patch)
					b_support_backdoor = _FALSE;*/

				pwrpriv->b_support_backdoor = b_support_backdoor;
			}
			break;

		case 2:	// Set by Chipset.
			// ASPM value set by chipset.
			if (pcipriv->pcibridge_vendor == PCI_BRIDGE_VENDOR_INTEL) {
				u8	b_support_aspm = _TRUE;
				pwrpriv->b_support_aspm = b_support_aspm;
			}
			break;

		default:
			// Do nothing. Set when finding the chipset.
			break;
	}
}