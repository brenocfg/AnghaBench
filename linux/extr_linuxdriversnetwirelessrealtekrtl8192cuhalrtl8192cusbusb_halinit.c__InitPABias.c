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
typedef  int /*<<< orphan*/  _adapter ;
struct TYPE_3__ {int /*<<< orphan*/  VersionID; } ;
typedef  TYPE_1__ HAL_DATA_TYPE ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int BIT0 ; 
 int BIT1 ; 
 int BIT4 ; 
 int EFUSE_Read1Byte (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* GET_HAL_DATA (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_92C_SERIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_SetRFReg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  RF_PATH_A ; 
 int /*<<< orphan*/  RF_PATH_B ; 
 int rtw_read8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtw_write8 (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void _InitPABias(_adapter *padapter)
{
	HAL_DATA_TYPE		*pHalData	= GET_HAL_DATA(padapter);
	u8			pa_setting;
	BOOLEAN		is92C = IS_92C_SERIAL(pHalData->VersionID);
	
	//FIXED PA current issue
	//efuse_one_byte_read(padapter, 0x1FA, &pa_setting);
	pa_setting = EFUSE_Read1Byte(padapter, 0x1FA);

	//RT_TRACE(COMP_INIT, DBG_LOUD, ("_InitPABias 0x1FA 0x%x \n",pa_setting));

	if(!(pa_setting & BIT0))
	{
		PHY_SetRFReg(padapter, RF_PATH_A, 0x15, 0x0FFFFF, 0x0F406);
		PHY_SetRFReg(padapter, RF_PATH_A, 0x15, 0x0FFFFF, 0x4F406);		
		PHY_SetRFReg(padapter, RF_PATH_A, 0x15, 0x0FFFFF, 0x8F406);		
		PHY_SetRFReg(padapter, RF_PATH_A, 0x15, 0x0FFFFF, 0xCF406);		
		//RT_TRACE(COMP_INIT, DBG_LOUD, ("PA BIAS path A\n"));
	}	

	if(!(pa_setting & BIT1) && is92C)
	{
		PHY_SetRFReg(padapter,RF_PATH_B, 0x15, 0x0FFFFF, 0x0F406);
		PHY_SetRFReg(padapter,RF_PATH_B, 0x15, 0x0FFFFF, 0x4F406);		
		PHY_SetRFReg(padapter,RF_PATH_B, 0x15, 0x0FFFFF, 0x8F406);		
		PHY_SetRFReg(padapter,RF_PATH_B, 0x15, 0x0FFFFF, 0xCF406);
		//RT_TRACE(COMP_INIT, DBG_LOUD, ("PA BIAS path B\n"));	
	}

	if(!(pa_setting & BIT4))
	{
		pa_setting = rtw_read8(padapter, 0x16);
		pa_setting &= 0x0F;
		rtw_write8(padapter, 0x16, pa_setting | 0x90);		
	}
}