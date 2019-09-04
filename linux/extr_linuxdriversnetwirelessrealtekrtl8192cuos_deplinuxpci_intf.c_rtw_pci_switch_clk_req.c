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
typedef  int /*<<< orphan*/  u8 ;
struct dvobj_priv {int /*<<< orphan*/  ppcidev; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw_init_completed; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int) ; 
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _SUCCESS ; 
 struct dvobj_priv* adapter_to_dvobj (TYPE_1__*) ; 
 int pci_write_config_byte (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 rtw_pci_switch_clk_req(_adapter *padapter, u8 value)
{
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);
	u8	buffer, bresult = _SUCCESS;
	int	error;

	buffer = value;

	if(!padapter->hw_init_completed)
		return bresult;

	error = pci_write_config_byte(pdvobjpriv->ppcidev, 0x81, value);

	if(error != 0)
	{
		bresult = _FALSE;
		DBG_871X("rtw_pci_switch_clk_req error (%d)\n",error);
	}

	return bresult;
}