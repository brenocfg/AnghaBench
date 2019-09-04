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
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  REG_APS_FSMCO ; 
 int /*<<< orphan*/  REG_RSV_CTRL ; 
 int /*<<< orphan*/  rtw_write16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8192cu_hw_power_down(_adapter *padapter)
{
	// 2010/-8/09 MH For power down module, we need to enable register block contrl reg at 0x1c.
	// Then enable power down control bit of register 0x04 BIT4 and BIT15 as 1.
		
	// Enable register area 0x0-0xc.
	rtw_write8(padapter,REG_RSV_CTRL, 0x0);			
	rtw_write16(padapter, REG_APS_FSMCO, 0x8812);
}