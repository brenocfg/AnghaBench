#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pwrctrl_priv {int reg_rfps_level; } ;
struct TYPE_5__ {struct pwrctrl_priv pwrctrlpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int RT_RF_PS_LEVEL_ALWAYS_ASPM ; 
 int /*<<< orphan*/  RT_SET_PS_LEVEL (struct pwrctrl_priv*,int) ; 
 int /*<<< orphan*/  rtw_pci_enable_aspm (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_pci_update_default_setting (TYPE_1__*) ; 

__attribute__((used)) static void rtw_pci_initialize_adapter_common(_adapter *padapter)
{
	struct pwrctrl_priv	*pwrpriv = &padapter->pwrctrlpriv;

	rtw_pci_update_default_setting(padapter);

	if (pwrpriv->reg_rfps_level & RT_RF_PS_LEVEL_ALWAYS_ASPM) {
		// Always enable ASPM & Clock Req.
		rtw_pci_enable_aspm(padapter);
		RT_SET_PS_LEVEL(pwrpriv, RT_RF_PS_LEVEL_ALWAYS_ASPM);
	}

}