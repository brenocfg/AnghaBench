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
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 int /*<<< orphan*/  HW_VAR_RF_TYPE ; 
 scalar_t__ RF_1T1R ; 
 scalar_t__ RF_1T2R ; 
 int /*<<< orphan*/  rtw_hal_get_hwreg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  rtw_hal_read_rfreg (int /*<<< orphan*/ *,int,int,int) ; 

void rf_reg_dump(_adapter *padapter)
{	
	int i,j=1,path;
	u32 value;	
	u8 rf_type,path_nums = 0;
	rtw_hal_get_hwreg(padapter, HW_VAR_RF_TYPE, (u8 *)(&rf_type));
		
	DBG_871X("\n======= RF REG =======\n");
	if((RF_1T2R == rf_type) ||(RF_1T1R ==rf_type ))	
		path_nums = 1;
	else	
		path_nums = 2;
		
	for(path=0;path<path_nums;path++)
	{
		DBG_871X("\nRF_Path(%x)\n",path);
		for(i=0;i<0x100;i++)
		{								
			//value = PHY_QueryRFReg(padapter, (RF90_RADIO_PATH_E)path,i, bMaskDWord);
			value =rtw_hal_read_rfreg(padapter, path, i, 0xffffffff);
			if(j%4==1)	DBG_871X("0x%02x ",i);
			DBG_871X(" 0x%08x ",value);
			if((j++)%4==0)	DBG_871X("\n");	
		}	
	}
}