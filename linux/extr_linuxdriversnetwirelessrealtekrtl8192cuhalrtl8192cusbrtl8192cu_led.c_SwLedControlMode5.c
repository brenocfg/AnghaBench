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
struct TYPE_10__ {int /*<<< orphan*/  bBusyTraffic; } ;
struct mlme_priv {TYPE_1__ LinkDetectInfo; } ;
struct TYPE_12__ {void* bLedScanBlinkInProgress; void* bLedBlinkInProgress; int BlinkTimes; void* CurrLedState; int /*<<< orphan*/  BlinkTimer; void* BlinkingLedState; int /*<<< orphan*/  bLedOn; } ;
struct led_priv {TYPE_3__ SwLed1; TYPE_3__ SwLed0; } ;
struct TYPE_11__ {struct mlme_priv mlmepriv; struct led_priv ledpriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_13__ {scalar_t__ EEPROMCustomerID; } ;
typedef  TYPE_3__* PLED_871x ;
typedef  int LED_CTL_MODE ;
typedef  TYPE_4__ HAL_DATA_TYPE ;

/* Variables and functions */
 TYPE_4__* GET_HAL_DATA (TYPE_2__*) ; 
 int /*<<< orphan*/  LED_BLINK_FASTER_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_SCAN_INTERVAL_ALPHA ; 
#define  LED_CTL_LINK 134 
#define  LED_CTL_NO_LINK 133 
#define  LED_CTL_POWER_OFF 132 
#define  LED_CTL_POWER_ON 131 
#define  LED_CTL_RX 130 
#define  LED_CTL_SITE_SURVEY 129 
#define  LED_CTL_TX 128 
 void* LED_SCAN_BLINK ; 
 void* LED_TXRX_BLINK ; 
 void* RTW_LED_OFF ; 
 void* RTW_LED_ON ; 
 scalar_t__ RT_CID_819x_CAMEO ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SwLedOff (TYPE_2__*,TYPE_3__*) ; 
 void* _FALSE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 void* _TRUE ; 
 int /*<<< orphan*/  _cancel_timer_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl8712_led_c_ ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SwLedControlMode5(
	_adapter				*padapter,
	LED_CTL_MODE		LedAction
)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct led_priv	*ledpriv = &(padapter->ledpriv);
	struct mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	PLED_871x		pLed = &(ledpriv->SwLed0);

	if(pHalData->EEPROMCustomerID == RT_CID_819x_CAMEO)
		pLed = &(ledpriv->SwLed1);
	
	switch(LedAction)
	{		
		case LED_CTL_POWER_ON:
		case LED_CTL_NO_LINK:
		case LED_CTL_LINK: 	//solid blue
			pLed->CurrLedState = RTW_LED_ON;
			pLed->BlinkingLedState = RTW_LED_ON; 

			_set_timer(&(pLed->BlinkTimer), 0);
			break;

		case LED_CTL_SITE_SURVEY:
			if((pmlmepriv->LinkDetectInfo.bBusyTraffic) && (check_fwstate(pmlmepriv, _FW_LINKED)== _TRUE))
				;		 
			else if(pLed->bLedScanBlinkInProgress ==_FALSE)
			{				
				if(pLed->bLedBlinkInProgress ==_TRUE)
				{
					_cancel_timer_ex(&(pLed->BlinkTimer));
					pLed->bLedBlinkInProgress = _FALSE;
				}
				pLed->bLedScanBlinkInProgress = _TRUE;
				pLed->CurrLedState = LED_SCAN_BLINK;
				pLed->BlinkTimes = 24;
				if( pLed->bLedOn )
					pLed->BlinkingLedState = RTW_LED_OFF; 
				else
					pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_SCAN_INTERVAL_ALPHA);
			}
			break;
		
		case LED_CTL_TX:
		case LED_CTL_RX:
	 		if(pLed->bLedBlinkInProgress ==_FALSE)
	  		{
	  		  	if(pLed->CurrLedState == LED_SCAN_BLINK)
				{
					return;
				}			
				pLed->bLedBlinkInProgress = _TRUE;
				pLed->CurrLedState = LED_TXRX_BLINK;
				pLed->BlinkTimes = 2;
				if( pLed->bLedOn )
					pLed->BlinkingLedState = RTW_LED_OFF; 
				else
					pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_FASTER_INTERVAL_ALPHA);
			}
			break;				

		case LED_CTL_POWER_OFF:
			pLed->CurrLedState = RTW_LED_OFF;
			pLed->BlinkingLedState = RTW_LED_OFF; 

			if( pLed->bLedBlinkInProgress)
			{
				_cancel_timer_ex(&(pLed->BlinkTimer));
				pLed->bLedBlinkInProgress = _FALSE;
			}			
				
			SwLedOff(padapter, pLed);
			break;
			
		default:
			break;

	}

	RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("Led %d\n", pLed->CurrLedState));
}