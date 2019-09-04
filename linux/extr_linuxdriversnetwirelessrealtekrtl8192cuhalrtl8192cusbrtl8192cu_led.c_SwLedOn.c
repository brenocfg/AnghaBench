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
struct TYPE_12__ {scalar_t__ BoardType; } ;
struct TYPE_11__ {int LedPin; scalar_t__ bLedOn; } ;
typedef  TYPE_2__* PLED_871x ;
typedef  TYPE_3__ HAL_DATA_TYPE ;

/* Variables and functions */
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
 scalar_t__ _TRUE ; 
 int rtw_read8 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
SwLedOn(
	_adapter			*padapter, 
	PLED_871x		pLed
)
{
	u8	LedCfg;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);

	if( (padapter->bSurpriseRemoved == _TRUE) || ( padapter->bDriverStopped == _TRUE))
	{
		return;
	}

	if( 	(BOARD_MINICARD == pHalData->BoardType )||
		(BOARD_USB_SOLO == pHalData->BoardType)||
		(BOARD_USB_COMBO == pHalData->BoardType))
	{
		LedCfg = rtw_read8(padapter, REG_LEDCFG2);
		switch(pLed->LedPin)
		{	
			case LED_PIN_GPIO0:
				break;

			case LED_PIN_LED0:
				rtw_write8(padapter, REG_LEDCFG2, (LedCfg&0xf0)|BIT5|BIT6); // SW control led0 on.
				break;

			case LED_PIN_LED1:
				rtw_write8(padapter, REG_LEDCFG2, (LedCfg&0x0f)|BIT5); // SW control led1 on.
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
					rtw_write8(padapter, REG_LEDCFG2, (LedCfg&0xe0)|BIT7|BIT6|BIT5); // SW control led0 on.
					//RT_TRACE(COMP_LED, DBG_LOUD, ("SwLedOn LED0 0x%x\n", PlatformEFIORead4Byte(Adapter, REG_LEDCFG2)));
				}
				else
#endif
				{
					LedCfg = rtw_read8(padapter, REG_LEDCFG0);
					rtw_write8(padapter,REG_LEDCFG0, LedCfg&0x70); // SW control led0 on.
					//RT_TRACE(COMP_LED, DBG_LOUD, ("SwLedOn LED0 0x%lx\n", PlatformEFIORead4Byte(Adapter, REG_LEDCFG0)));
				}
				break;

			case LED_PIN_LED1:
				LedCfg = rtw_read8(padapter,(REG_LEDCFG1));
				rtw_write8(padapter,(REG_LEDCFG1), LedCfg&0x70); // SW control led1 on.
				//RT_TRACE(COMP_LED, DBG_LOUD, ("SwLedOn LED1 0x%lx\n", PlatformEFIORead4Byte(Adapter, REG_LEDCFG0)));
			
				break;

			default:
				break;
		}
	}
	pLed->bLedOn = _TRUE;
	
}