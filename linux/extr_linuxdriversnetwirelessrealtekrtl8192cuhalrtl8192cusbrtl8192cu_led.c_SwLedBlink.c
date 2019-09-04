#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct mlme_priv {int dummy; } ;
struct TYPE_8__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;
struct TYPE_9__ {scalar_t__ BlinkingLedState; scalar_t__ BlinkTimes; int CurrLedState; scalar_t__ bLedOn; int /*<<< orphan*/  BlinkTimer; scalar_t__ bLedBlinkInProgress; TYPE_1__* padapter; } ;
typedef  TYPE_2__* PLED_871x ;

/* Variables and functions */
 int /*<<< orphan*/  LED_BLINK_LONG_INTERVAL ; 
#define  LED_BLINK_NORMAL 131 
 int /*<<< orphan*/  LED_BLINK_NORMAL_INTERVAL ; 
#define  LED_BLINK_SLOWLY 130 
 int /*<<< orphan*/  LED_BLINK_SLOWLY_INTERVAL ; 
#define  LED_BLINK_StartToBlink 129 
#define  LED_BLINK_WPS 128 
 scalar_t__ RTW_LED_OFF ; 
 scalar_t__ RTW_LED_ON ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SwLedOff (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SwLedOn (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 scalar_t__ _FALSE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl8712_led_c_ ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SwLedBlink(
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
		SwLedOff(padapter, pLed);
		RT_TRACE(_module_rtl8712_led_c_,_drv_info_,( "Blinktimes (%d): turn off\n", pLed->BlinkTimes));
	}

	// Determine if we shall change LED state again.
	pLed->BlinkTimes--;
	switch(pLed->CurrLedState)
	{

	case LED_BLINK_NORMAL: 
		if(pLed->BlinkTimes == 0)
		{
			bStopBlinking = _TRUE;
		}
		break;
		
	case LED_BLINK_StartToBlink:
		if( check_fwstate(pmlmepriv, _FW_LINKED) && check_fwstate(pmlmepriv, WIFI_STATION_STATE) )
		{
			bStopBlinking = _TRUE;
		}
		if( check_fwstate(pmlmepriv, _FW_LINKED) &&
			(check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) || check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) )
		{
			bStopBlinking = _TRUE;
		}
		else if(pLed->BlinkTimes == 0)
		{
			bStopBlinking = _TRUE;
		}
		break;

	case LED_BLINK_WPS:
		if( pLed->BlinkTimes == 0 )
		{
			bStopBlinking = _TRUE;
		}
		break;


	default:
		bStopBlinking = _TRUE;
		break;
			
	}
	
	if(bStopBlinking)
	{
		//if( padapter->pwrctrlpriv.cpwm >= PS_STATE_S2)
		if(0)
		{
			SwLedOff(padapter, pLed);
		}
		else if( (check_fwstate(pmlmepriv, _FW_LINKED)== _TRUE) && (pLed->bLedOn == _FALSE))
		{
			SwLedOn(padapter, pLed);
		}
		else if( (check_fwstate(pmlmepriv, _FW_LINKED)== _TRUE) &&  pLed->bLedOn == _TRUE)
		{
			SwLedOff(padapter, pLed);
		}

		pLed->BlinkTimes = 0;
		pLed->bLedBlinkInProgress = _FALSE;
	}
	else
	{
		// Assign LED state to toggle.
		if( pLed->BlinkingLedState == RTW_LED_ON ) 
			pLed->BlinkingLedState = RTW_LED_OFF;
		else 
			pLed->BlinkingLedState = RTW_LED_ON;

		// Schedule a timer to toggle LED state. 
		switch( pLed->CurrLedState )
		{
		case LED_BLINK_NORMAL:
			_set_timer(&(pLed->BlinkTimer), LED_BLINK_NORMAL_INTERVAL);
			break;
		
		case LED_BLINK_SLOWLY:
		case LED_BLINK_StartToBlink:
			_set_timer(&(pLed->BlinkTimer), LED_BLINK_SLOWLY_INTERVAL);
			break;

		case LED_BLINK_WPS:
			{
				if( pLed->BlinkingLedState == RTW_LED_ON )
					_set_timer(&(pLed->BlinkTimer), LED_BLINK_LONG_INTERVAL);
				else
					_set_timer(&(pLed->BlinkTimer), LED_BLINK_LONG_INTERVAL);
			}
			break;

		default:
			_set_timer(&(pLed->BlinkTimer), LED_BLINK_SLOWLY_INTERVAL);
			break;
		}
	}
}