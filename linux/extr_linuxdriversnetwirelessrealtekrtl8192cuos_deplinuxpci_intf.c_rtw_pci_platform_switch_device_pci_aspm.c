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
struct dvobj_priv {int /*<<< orphan*/  ppcidev; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int) ; 
 int _FALSE ; 
 int _SUCCESS ; 
 struct dvobj_priv* adapter_to_dvobj (int /*<<< orphan*/ *) ; 
 int pci_write_config_byte (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u8 rtw_pci_platform_switch_device_pci_aspm(_adapter *padapter, u8 value)
{
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);
	u8	bresult = _SUCCESS;
	int	error;

	value |= 0x40;

	error = pci_write_config_byte(pdvobjpriv->ppcidev, 0x80, value);

	if(error != 0)
	{
		bresult = _FALSE;
		DBG_871X("rtw_pci_platform_switch_device_pci_aspm error (%d)\n",error);
	}

	return bresult;
}