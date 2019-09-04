#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct mlme_priv {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  rf_pwrstate; } ;
struct TYPE_10__ {TYPE_1__ pwrctrlpriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_11__ {scalar_t__ BlinkingLedState; int CurrLedState; void* bLedWPSBlinkInProgress; int /*<<< orphan*/  BlinkTimer; int /*<<< orphan*/  bLedOn; void* bLedBlinkInProgress; int /*<<< orphan*/  BlinkTimes; void* bLedScanBlinkInProgress; TYPE_2__* padapter; } ;
typedef  TYPE_3__* PLED_871x ;

/* Variables and functions */
 int /*<<< orphan*/  LED_BLINK_FASTER_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_SCAN_INTERVAL_ALPHA ; 
#define  LED_BLINK_WPS 131 
#define  LED_BLINK_WPS_STOP 130 
 int /*<<< orphan*/  LED_BLINK_WPS_SUCESS_INTERVAL_ALPHA ; 
#define  LED_SCAN_BLINK 129 
#define  LED_TXRX_BLINK 128 
 void* RTW_LED_OFF ; 
 scalar_t__ RTW_LED_ON ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SwLedOff (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  SwLedOn (TYPE_2__*,TYPE_3__*) ; 
 void* _FALSE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 void* _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl8712_led_c_ ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rf_on ; 

__attribute__((used)) static void
SwLedBlink3(
	PLED_871x			pLed
	)
{
	_adapter			*padapter = pLed->padapter;
	struct mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	u8				bStopBlinking = _FALSE;

	// Change LED according to BlinkingLedState specified.
	if( pLed->BlinkingLedState == RTW_LED_ON ) 
	{
		SwLedOn(padapter, pLed);
		RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("Blinktimes (%d): turn on\n", pLed->BlinkTimes));
	}
	else 
	{
		if(pLed->CurrLedState != LED_BLINK_WPS_STOP)
			SwLedOff(padapter, pLed);
		RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("Blinktimes (%d): turn off\n", pLed->BlinkTimes));
	}	

	switch(pLed->CurrLedState)
	{			
		case LED_SCAN_BLINK:
			pLed->BlinkTimes--;
			if( pLed->BlinkTimes == 0 )
			{
				bStopBlinking = _TRUE;
			}
			
			if(bStopBlinking)
			{
				if( padapter->pwrctrlpriv.rf_pwrstate != rf_on )
				{
					SwLedOff(padapter, pLed);
				}
				else if(check_fwstate(pmlmepriv, _FW_LINKED)== _TRUE)
				{
					pLed->CurrLedState = RTW_LED_ON;
					pLed->BlinkingLedState = RTW_LED_ON;				
					if( !pLed->bLedOn )
						SwLedOn(padapter, pLed);

					RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("CurrLedState %d\n", pLed->CurrLedState));					
				}
				else if(check_fwstate(pmlmepriv, _FW_LINKED)== _FALSE)
				{
					pLed->CurrLedState = RTW_LED_OFF;
					pLed->BlinkingLedState = RTW_LED_OFF;									
					if( pLed->bLedOn )
						SwLedOff(padapter, pLed);

					RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("CurrLedState %d\n", pLed->CurrLedState));					
				}
				pLed->bLedScanBlinkInProgress = _FALSE;
			}
			else
			{
				if( padapter->pwrctrlpriv.rf_pwrstate != rf_on )
				{
					SwLedOff(padapter, pLed);
				}
				else
				{
				 	if( pLed->bLedOn )
						pLed->BlinkingLedState = RTW_LED_OFF; 
					else
						pLed->BlinkingLedState = RTW_LED_ON;
					_set_timer(&(pLed->BlinkTimer), LED_BLINK_SCAN_INTERVAL_ALPHA);
				}
			}
			break;

		case LED_TXRX_BLINK:
			pLed->BlinkTimes--;
			if( pLed->BlinkTimes == 0 )
			{
				bStopBlinking = _TRUE;
			}
			if(bStopBlinking)
			{
				if( padapter->pwrctrlpriv.rf_pwrstate != rf_on )
				{
					SwLedOff(padapter, pLed);
				}
				else if(check_fwstate(pmlmepriv, _FW_LINKED)== _TRUE)
				{
					pLed->CurrLedState = RTW_LED_ON;
					pLed->BlinkingLedState = RTW_LED_ON;
				
					if( !pLed->bLedOn )
						SwLedOn(padapter, pLed);

					RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("CurrLedState %d\n", pLed->CurrLedState));					
				}
				else if(check_fwstate(pmlmepriv, _FW_LINKED)== _FALSE)
				{
					pLed->CurrLedState = RTW_LED_OFF;
					pLed->BlinkingLedState = RTW_LED_OFF;					
				
					if( pLed->bLedOn )
						SwLedOff(padapter, pLed);


					RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("CurrLedState %d\n", pLed->CurrLedState));					
				}
				pLed->bLedBlinkInProgress = _FALSE;	
			}
			else
			{
				if( padapter->pwrctrlpriv.rf_pwrstate != rf_on )
				{
					SwLedOff(padapter, pLed);
				}
				else
				{
					if( pLed->bLedOn )
						pLed->BlinkingLedState = RTW_LED_OFF; 
					else
						pLed->BlinkingLedState = RTW_LED_ON;
					_set_timer(&(pLed->BlinkTimer), LED_BLINK_FASTER_INTERVAL_ALPHA);
				}
			}
			break;

		case LED_BLINK_WPS:
			if( pLed->bLedOn )
				pLed->BlinkingLedState = RTW_LED_OFF; 
			else
				pLed->BlinkingLedState = RTW_LED_ON;
			_set_timer(&(pLed->BlinkTimer), LED_BLINK_SCAN_INTERVAL_ALPHA);
			break;

		case LED_BLINK_WPS_STOP:	//WPS success
			if(pLed->BlinkingLedState == RTW_LED_ON)
			{
				pLed->BlinkingLedState = RTW_LED_OFF;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_WPS_SUCESS_INTERVAL_ALPHA);
				bStopBlinking = _FALSE;
			}
			else
			{
				bStopBlinking = _TRUE;				
			}
			
			if(bStopBlinking)
			{
				if( padapter->pwrctrlpriv.rf_pwrstate != rf_on )
				{
					SwLedOff(padapter, pLed);
				}
				else 
				{
					pLed->CurrLedState = RTW_LED_ON;
					pLed->BlinkingLedState = RTW_LED_ON; 
					SwLedOn(padapter, pLed);
					RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("CurrLedState %d\n", pLed->CurrLedState));					
				}
				pLed->bLedWPSBlinkInProgress = _FALSE;	
			}		
			break;
			
					
		default:
			break;
	}

}