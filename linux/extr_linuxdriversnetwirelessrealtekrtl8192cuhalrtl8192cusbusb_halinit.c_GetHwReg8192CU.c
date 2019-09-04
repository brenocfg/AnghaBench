#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_10__ {int DMFlag; } ;
struct TYPE_13__ {int rf_type; int /*<<< orphan*/  EEPROMPID; int /*<<< orphan*/  EEPROMVID; int /*<<< orphan*/  EfuseUsedBytes; TYPE_1__ dmpriv; int /*<<< orphan*/  BasicRateSet; } ;
struct TYPE_11__ {int /*<<< orphan*/  rf_pwrstate; } ;
struct TYPE_12__ {TYPE_2__ pwrctrlpriv; } ;
typedef  TYPE_3__* PADAPTER ;
typedef  TYPE_4__ HAL_DATA_TYPE ;

/* Variables and functions */
 int BIT0 ; 
 TYPE_4__* GET_HAL_DATA (TYPE_3__*) ; 
#define  HW_VAR_BASIC_RATE 136 
#define  HW_VAR_BCN_VALID 135 
#define  HW_VAR_DM_FLAG 134 
#define  HW_VAR_EFUSE_BYTES 133 
#define  HW_VAR_FWLPS_RF_ON 132 
#define  HW_VAR_PID 131 
#define  HW_VAR_RF_TYPE 130 
#define  HW_VAR_TXPAUSE 129 
#define  HW_VAR_VID 128 
 int /*<<< orphan*/  REG_RCR ; 
 int /*<<< orphan*/  REG_TDECTRL ; 
 int /*<<< orphan*/  REG_TXPAUSE ; 
 int _FALSE ; 
 int _TRUE ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  rf_off ; 
 int rtw_read32 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int rtw_read8 (TYPE_3__*,int /*<<< orphan*/ ) ; 

void GetHwReg8192CU(PADAPTER Adapter, u8 variable, u8* val)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(Adapter);

_func_enter_;

	switch(variable)
	{
		case HW_VAR_BASIC_RATE:
			*((u16 *)(val)) = pHalData->BasicRateSet;
		case HW_VAR_TXPAUSE:
			val[0] = rtw_read8(Adapter, REG_TXPAUSE);
			break;
		case HW_VAR_BCN_VALID:
			//BCN_VALID, BIT16 of REG_TDECTRL = BIT0 of REG_TDECTRL+2
			val[0] = (BIT0 & rtw_read8(Adapter, REG_TDECTRL+2))?_TRUE:_FALSE;
			break;
		case HW_VAR_DM_FLAG:
			val[0] = pHalData->dmpriv.DMFlag;
			break;
		case HW_VAR_RF_TYPE:
			val[0] = pHalData->rf_type;
			break;
		case HW_VAR_FWLPS_RF_ON:
			{
				//When we halt NIC, we should check if FW LPS is leave.
				u32	valRCR;
				
				if(Adapter->pwrctrlpriv.rf_pwrstate == rf_off)
				{
					// If it is in HW/SW Radio OFF or IPS state, we do not check Fw LPS Leave,
					// because Fw is unload.
					val[0] = _TRUE;
				}
				else
				{
					valRCR = rtw_read32(Adapter, REG_RCR);
					valRCR &= 0x00070000;
					if(valRCR)
						val[0] = _FALSE;
					else
						val[0] = _TRUE;
				}
			}
			break;
#ifdef CONFIG_ANTENNA_DIVERSITY
		case HW_VAR_CURRENT_ANTENNA:
			val[0] = pHalData->CurAntenna;
			break;
#endif
		case HW_VAR_EFUSE_BYTES: // To get EFUE total used bytes, added by Roger, 2008.12.22.
			*((u16 *)(val)) = pHalData->EfuseUsedBytes;	
			break;
		case HW_VAR_VID:
			*((u16 *)(val)) = pHalData->EEPROMVID;
			break;
		case HW_VAR_PID:
			*((u16 *)(val)) = pHalData->EEPROMPID;
			break;
		default:
			break;
	}

_func_exit_;
}