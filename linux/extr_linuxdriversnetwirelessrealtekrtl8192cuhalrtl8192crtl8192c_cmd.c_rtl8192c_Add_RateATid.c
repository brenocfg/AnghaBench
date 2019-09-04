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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ fw_ractrl; } ;
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  TYPE_1__ HAL_DATA_TYPE ;

/* Variables and functions */
 int BIT (int) ; 
 TYPE_1__* GET_HAL_DATA (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_INIDATA_RATE_SEL ; 
 scalar_t__ _FALSE ; 
 scalar_t__ _TRUE ; 
 int get_highest_rate_idx (int) ; 
 int /*<<< orphan*/  rtl8192c_set_raid_cmd (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtw_write8 (int /*<<< orphan*/ ,scalar_t__,int) ; 

void rtl8192c_Add_RateATid(PADAPTER pAdapter, u32 bitmap, u8 arg)
{	
	
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
		
	if(pHalData->fw_ractrl == _TRUE)
	{
		rtl8192c_set_raid_cmd(pAdapter, bitmap, arg);
	}
	else
	{
		u8 macid, init_rate, shortGIrate=_FALSE;

		init_rate = get_highest_rate_idx(bitmap&0x0fffffff)&0x3f;
		
		macid = arg&0x1f;
		
		shortGIrate = (arg&BIT(5)) ? _TRUE:_FALSE;
		
		if (shortGIrate==_TRUE)
			init_rate |= BIT(6);

		rtw_write8(pAdapter, (REG_INIDATA_RATE_SEL+macid), (u8)init_rate);		
	}

}