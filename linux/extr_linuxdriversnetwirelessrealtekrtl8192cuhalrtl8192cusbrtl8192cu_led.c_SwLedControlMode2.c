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
struct TYPE_13__ {void* bLedScanBlinkInProgress; void* bLedBlinkInProgress; int BlinkTimes; void* bLedWPSBlinkInProgress; void* CurrLedState; int /*<<< orphan*/  BlinkTimer; void* BlinkingLedState; int /*<<< orphan*/  bLedOn; } ;
struct led_priv {TYPE_4__ SwLed0; } ;
struct TYPE_11__ {int /*<<< orphan*/  rf_pwrstate; } ;
struct TYPE_12__ {TYPE_2__ pwrctrlpriv; struct mlme_priv mlmepriv; struct led_priv ledpriv; } ;
typedef  TYPE_3__ _adapter ;
typedef  TYPE_4__* PLED_871x ;
typedef  int LED_CTL_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  IS_LED_BLINKING (TYPE_4__*) ; 
 int /*<<< orphan*/  IS_LED_WPS_BLINKING (TYPE_4__*) ; 
 int /*<<< orphan*/  LED_BLINK_FASTER_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_SCAN_INTERVAL_ALPHA ; 
#define  LED_CTL_LINK 138 
#define  LED_CTL_NO_LINK 137 
#define  LED_CTL_POWER_OFF 136 
#define  LED_CTL_RX 135 
#define  LED_CTL_SITE_SURVEY 134 
#define  LED_CTL_START_TO_LINK 133 
#define  LED_CTL_START_WPS 132 
#define  LED_CTL_START_WPS_BOTTON 131 
#define  LED_CTL_STOP_WPS 130 
#define  LED_CTL_STOP_WPS_FAIL 129 
#define  LED_CTL_TX 128 
 void* LED_SCAN_BLINK ; 
 void* LED_TXRX_BLINK ; 
 void* RTW_LED_OFF ; 
 void* RTW_LED_ON ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SwLedOff (TYPE_3__*,TYPE_4__*) ; 
 void* _FALSE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 void* _TRUE ; 
 int /*<<< orphan*/  _cancel_timer_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl8712_led_c_ ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rf_on ; 

__attribute__((used)) static void
SwLedControlMode2(
	_adapter				*padapter,
	LED_CTL_MODE		LedAction
)
{
	struct led_priv	*ledpriv = &(padapter->ledpriv);
	struct mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	PLED_871x 		pLed = &(ledpriv->SwLed0);
	
	switch(LedAction)
	{		
		case LED_CTL_SITE_SURVEY:
			 if(pmlmepriv->LinkDetectInfo.bBusyTraffic)
			 	;		 
			 else if(pLed->bLedScanBlinkInProgress ==_FALSE)
			 {
			 	if(IS_LED_WPS_BLINKING(pLed))
					return;
			 
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
	 		if((pLed->bLedBlinkInProgress ==_FALSE) && (check_fwstate(pmlmepriv, _FW_LINKED)== _TRUE))
	  		{
	  		  	if(pLed->CurrLedState == LED_SCAN_BLINK || IS_LED_WPS_BLINKING(pLed))
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

		case LED_CTL_LINK:
			pLed->CurrLedState = RTW_LED_ON;
			pLed->BlinkingLedState = RTW_LED_ON;
			if( pLed->bLedBlinkInProgress)
			{
				_cancel_timer_ex(&(pLed->BlinkTimer));
				pLed->bLedBlinkInProgress = _FALSE;
			}
			if( pLed->bLedScanBlinkInProgress)
			{
				_cancel_timer_ex(&(pLed->BlinkTimer));
				pLed->bLedScanBlinkInProgress = _FALSE;
			}			

			_set_timer(&(pLed->BlinkTimer), 0);
			break;			

		case LED_CTL_START_WPS: //wait until xinpin finish
		case LED_CTL_START_WPS_BOTTON:		
			if(pLed->bLedWPSBlinkInProgress ==_FALSE)
			{
				if(pLed->bLedBlinkInProgress ==_TRUE)
				{
					_cancel_timer_ex(&(pLed->BlinkTimer));
					pLed->bLedBlinkInProgress = _FALSE;
				}
				if(pLed->bLedScanBlinkInProgress ==_TRUE)
				{
					_cancel_timer_ex(&(pLed->BlinkTimer));
					pLed->bLedScanBlinkInProgress = _FALSE;
				}				
				pLed->bLedWPSBlinkInProgress = _TRUE;
				pLed->CurrLedState = RTW_LED_ON;
				pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), 0);
			 }			
			break;
			
		case LED_CTL_STOP_WPS:
			pLed->bLedWPSBlinkInProgress = _FALSE;
			if(padapter->pwrctrlpriv.rf_pwrstate != rf_on)
			{
				SwLedOff(padapter, pLed);
			}
			else
			{
				pLed->CurrLedState = RTW_LED_ON;
				pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), 0);
				RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("CurrLedState %d\n", pLed->CurrLedState));
			}
			break;
			
		case LED_CTL_STOP_WPS_FAIL:			
			pLed->bLedWPSBlinkInProgress = _FALSE;			
			if(padapter->pwrctrlpriv.rf_pwrstate != rf_on)
			{
				SwLedOff(padapter, pLed);
			}
			else 
			{
				pLed->CurrLedState = RTW_LED_OFF;
				pLed->BlinkingLedState = RTW_LED_OFF;
				_set_timer(&(pLed->BlinkTimer), 0);
				RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("CurrLedState %d\n", pLed->CurrLedState)); 				
			}	
			break;				

		case LED_CTL_START_TO_LINK: 
		case LED_CTL_NO_LINK:
			if(!IS_LED_BLINKING(pLed))
			{
				pLed->CurrLedState = RTW_LED_OFF;
				pLed->BlinkingLedState = RTW_LED_OFF;
				_set_timer(&(pLed->BlinkTimer), 0);
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
			if( pLed->bLedScanBlinkInProgress)
			{
				_cancel_timer_ex(&(pLed->BlinkTimer));
				pLed->bLedScanBlinkInProgress = _FALSE;
			}			
			if( pLed->bLedWPSBlinkInProgress )
			{
				_cancel_timer_ex(&(pLed->BlinkTimer));
				pLed->bLedWPSBlinkInProgress = _FALSE;
			}

			_set_timer(&(pLed->BlinkTimer), 0);
			break;
			
		default:
			break;

	}

	RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("CurrLedState %d\n", pLed->CurrLedState));
}