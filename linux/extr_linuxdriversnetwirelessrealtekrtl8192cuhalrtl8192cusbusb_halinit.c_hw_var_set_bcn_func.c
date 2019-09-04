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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  PADAPTER ;

/* Variables and functions */
 int DIS_TSF_UDT0_NORMAL_CHIP ; 
 int EN_BCN_FUNCTION ; 
 int EN_TXBCN_RPT ; 
 int /*<<< orphan*/  REG_BCN_CTRL ; 
 int rtw_read8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hw_var_set_bcn_func(PADAPTER Adapter, u8 variable, u8* val)
{
	u32 bcn_ctrl_reg;

#ifdef CONFIG_CONCURRENT_MODE
	if(Adapter->iface_type == IFACE_PORT1)
	{
		bcn_ctrl_reg = REG_BCN_CTRL_1;

		if(*((u8 *)val))
		{
			rtw_write8(Adapter, bcn_ctrl_reg, (EN_BCN_FUNCTION | EN_TXBCN_RPT));
		}
		else
		{
			rtw_write8(Adapter, bcn_ctrl_reg, rtw_read8(Adapter, bcn_ctrl_reg)&(~(EN_BCN_FUNCTION | EN_TXBCN_RPT)));
		}
	}	
	else
#endif		
	{		
		bcn_ctrl_reg = REG_BCN_CTRL;
		if(*((u8 *)val))
		{
			rtw_write8(Adapter, bcn_ctrl_reg, (EN_BCN_FUNCTION | EN_TXBCN_RPT));
		}
		else
		{
			//rtw_write8(Adapter, bcn_ctrl_reg, rtw_read8(Adapter, bcn_ctrl_reg)&(~(EN_BCN_FUNCTION | EN_TXBCN_RPT)));
			rtw_write8(Adapter, bcn_ctrl_reg, (rtw_read8(Adapter, bcn_ctrl_reg)&(~(EN_TXBCN_RPT))) | DIS_TSF_UDT0_NORMAL_CHIP);
		}
	}
	

}