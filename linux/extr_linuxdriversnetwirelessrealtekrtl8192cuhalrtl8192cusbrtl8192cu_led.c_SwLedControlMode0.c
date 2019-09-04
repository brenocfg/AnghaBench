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
struct TYPE_9__ {void* bLedBlinkInProgress; void* CurrLedState; int BlinkTimes; int /*<<< orphan*/  BlinkTimer; void* BlinkingLedState; int /*<<< orphan*/  bLedOn; } ;
struct led_priv {TYPE_2__ SwLed1; } ;
struct TYPE_8__ {struct led_priv ledpriv; } ;
typedef  TYPE_1__ _adapter ;
typedef  TYPE_2__* PLED_871x ;
typedef  int LED_CTL_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  LED_BLINK_LONG_INTERVAL ; 
 void* LED_BLINK_NORMAL ; 
 int /*<<< orphan*/  LED_BLINK_NORMAL_INTERVAL ; 
 int /*<<< orphan*/  LED_BLINK_SLOWLY_INTERVAL ; 
 void* LED_BLINK_StartToBlink ; 
 void* LED_BLINK_WPS ; 
#define  LED_CTL_LINK 135 
#define  LED_CTL_NO_LINK 134 
#define  LED_CTL_POWER_OFF 133 
#define  LED_CTL_RX 132 
#define  LED_CTL_START_TO_LINK 131 
#define  LED_CTL_START_WPS 130 
#define  LED_CTL_STOP_WPS 129 
#define  LED_CTL_TX 128 
 void* RTW_LED_OFF ; 
 void* RTW_LED_ON ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SwLedOff (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SwLedOn (TYPE_1__*,TYPE_2__*) ; 
 void* _FALSE ; 
 void* _TRUE ; 
 int /*<<< orphan*/  _cancel_timer_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl8712_led_c_ ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SwLedControlMode0(
	_adapter		*padapter,
	LED_CTL_MODE		LedAction
)
{
	struct led_priv	*ledpriv = &(padapter->ledpriv);
	PLED_871x	pLed = &(ledpriv->SwLed1);

	// Decide led state
	switch(LedAction)
	{
	case LED_CTL_TX:
	case LED_CTL_RX:
		if( pLed->bLedBlinkInProgress == _FALSE )
		{
			pLed->bLedBlinkInProgress = _TRUE;

			pLed->CurrLedState = LED_BLINK_NORMAL;
			pLed->BlinkTimes = 2;

			if( pLed->bLedOn )
				pLed->BlinkingLedState = RTW_LED_OFF; 
			else
				pLed->BlinkingLedState = RTW_LED_ON;
			_set_timer(&(pLed->BlinkTimer), LED_BLINK_NORMAL_INTERVAL);
		}
		break;

	case LED_CTL_START_TO_LINK:
		if( pLed->bLedBlinkInProgress == _FALSE )
		{
			pLed->bLedBlinkInProgress = _TRUE;

			pLed->CurrLedState = LED_BLINK_StartToBlink;
			pLed->BlinkTimes = 24;

			if( pLed->bLedOn )
				pLed->BlinkingLedState = RTW_LED_OFF; 
			else
				pLed->BlinkingLedState = RTW_LED_ON;
			_set_timer(&(pLed->BlinkTimer), LED_BLINK_SLOWLY_INTERVAL);
		}
		else
		{
			pLed->CurrLedState = LED_BLINK_StartToBlink;
		}	
		break;
		
	case LED_CTL_LINK:
		pLed->CurrLedState = RTW_LED_ON;
		if( pLed->bLedBlinkInProgress == _FALSE )
		{
			SwLedOn(padapter, pLed);
		}
		break;

	case LED_CTL_NO_LINK:
		pLed->CurrLedState = RTW_LED_OFF;
		if( pLed->bLedBlinkInProgress == _FALSE )
		{
			SwLedOff(padapter, pLed);
		}
		break;
	
	case LED_CTL_POWER_OFF:
		pLed->CurrLedState = RTW_LED_OFF;
		if(pLed->bLedBlinkInProgress)
		{
			_cancel_timer_ex(&(pLed->BlinkTimer));
			pLed->bLedBlinkInProgress = _FALSE;
		}
		SwLedOff(padapter, pLed);
		break;

	case LED_CTL_START_WPS:
		if( pLed->bLedBlinkInProgress == _FALSE || pLed->CurrLedState == RTW_LED_ON)
		{
			pLed->bLedBlinkInProgress = _TRUE;

			pLed->CurrLedState = LED_BLINK_WPS;
			pLed->BlinkTimes = 20;

			if( pLed->bLedOn )
			{
				pLed->BlinkingLedState = RTW_LED_OFF;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_LONG_INTERVAL);
			}
			else
			{
				pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_LONG_INTERVAL);
			}
		}
		break;

	case LED_CTL_STOP_WPS:
		if(pLed->bLedBlinkInProgress)
		{
			pLed->CurrLedState = RTW_LED_OFF;
			_cancel_timer_ex(&(pLed->BlinkTimer));
			pLed->bLedBlinkInProgress = _FALSE;
		}
		break;
		

	default:
		break;
	}
	
	RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("Led %d\n", pLed->CurrLedState));
	
}