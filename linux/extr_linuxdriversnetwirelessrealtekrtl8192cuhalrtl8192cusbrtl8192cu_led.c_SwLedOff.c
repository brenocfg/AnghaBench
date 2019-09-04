#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_10__ {scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_12__ {scalar_t__ BoardType; scalar_t__ bLedOpenDrain; } ;
struct TYPE_11__ {int LedPin; int /*<<< orphan*/  bLedOn; } ;
typedef  TYPE_2__* PLED_871x ;
typedef  TYPE_3__ HAL_DATA_TYPE ;

/* Variables and functions */
 int BIT1 ; 
 int BIT3 ; 
 int BIT5 ; 
 int BIT6 ; 
 scalar_t__ BOARD_MINICARD ; 
 scalar_t__ BOARD_USB_COMBO ; 
 scalar_t__ BOARD_USB_SOLO ; 
 TYPE_3__* GET_HAL_DATA (TYPE_1__*) ; 
#define  LED_PIN_GPIO0 130 
#define  LED_PIN_LED0 129 
#define  LED_PIN_LED1 128 
 int /*<<< orphan*/  REG_LEDCFG0 ; 
 int /*<<< orphan*/  REG_LEDCFG1 ; 
 int /*<<< orphan*/  REG_LEDCFG2 ; 
 int /*<<< orphan*/  REG_MAC_PINMUX_CFG ; 
 int /*<<< orphan*/  _FALSE ; 
 scalar_t__ _TRUE ; 
 int rtw_read8 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
SwLedOff(
	_adapter			*padapter, 
	PLED_871x		pLed
)
{
	u8	LedCfg;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);

	if((padapter->bSurpriseRemoved == _TRUE) || ( padapter->bDriverStopped == _TRUE))	
	{
		goto exit;
	}

	if( 	(BOARD_MINICARD == pHalData->BoardType )||
		(BOARD_USB_SOLO == pHalData->BoardType)||
		(BOARD_USB_COMBO == pHalData->BoardType))
	{
		LedCfg = rtw_read8(padapter, REG_LEDCFG2);//0x4E

		switch(pLed->LedPin)
		{

			case LED_PIN_GPIO0:
				break;

			case LED_PIN_LED0:
				if(BOARD_USB_COMBO == pHalData->BoardType)
				{
					LedCfg &= 0x90; // Set to software control.				
					rtw_write8(padapter, REG_LEDCFG2, (LedCfg|BIT3));				
					LedCfg = rtw_read8(padapter, REG_MAC_PINMUX_CFG);
					LedCfg &= 0xFE;
					rtw_write8(padapter, REG_MAC_PINMUX_CFG, LedCfg);									
				}
				else
				{
					LedCfg &= 0xf0; // Set to software control.
					if(pHalData->bLedOpenDrain == _TRUE) // Open-drain arrangement for controlling the LED
						rtw_write8(padapter, REG_LEDCFG2, (LedCfg|BIT1|BIT5|BIT6));
					else
						rtw_write8(padapter, REG_LEDCFG2, (LedCfg|BIT3|BIT5|BIT6));
				}
				break;

			case LED_PIN_LED1:
				LedCfg &= 0x0f; // Set to software control.
				rtw_write8(padapter, REG_LEDCFG2, (LedCfg|BIT3));
				break;

			default:
				break;
		}
	}
	else
	{
		switch(pLed->LedPin)
		{
			case LED_PIN_GPIO0:
				break;

			case LED_PIN_LED0:
#ifdef CONFIG_SW_ANTENNA_DIVERSITY
				if(pHalData->AntDivCfg)
				{
					LedCfg = rtw_read8(padapter, REG_LEDCFG2);
					LedCfg &= 0xe0; // Set to software control. 			
					rtw_write8(padapter, REG_LEDCFG2, (LedCfg|BIT3|BIT7|BIT6|BIT5));
					//RT_TRACE(COMP_LED, DBG_LOUD, ("SwLedOff LED0 0x%x\n", PlatformEFIORead4Byte(Adapter, REG_LEDCFG2)));
				}
				else
#endif
				{
					LedCfg = rtw_read8(padapter, REG_LEDCFG0);
					LedCfg &= 0x70; // Set to software control. 			
					rtw_write8(padapter, REG_LEDCFG0, (LedCfg|BIT3));
					//RT_TRACE(COMP_LED, DBG_LOUD, ("SwLedOff LED0 0x%lx\n", PlatformEFIORead4Byte(Adapter, REG_LEDCFG0)));
				}
				break;

			case LED_PIN_LED1:
				LedCfg = rtw_read8(padapter, (REG_LEDCFG1));
				LedCfg &= 0x70; // Set to software control.
				rtw_write8(padapter,  (REG_LEDCFG1), (LedCfg|BIT3));
				//RT_TRACE(COMP_LED, DBG_LOUD, ("SwLedOff LED1 0x%lx\n", PlatformEFIORead4Byte(Adapter, REG_LEDCFG0)));
				break;

			default:
				break;
		}
	}

exit:
	pLed->bLedOn = _FALSE;
	
}