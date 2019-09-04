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
struct TYPE_11__ {scalar_t__ BlinkingLedState; int BlinkTimes; int CurrLedState; int /*<<< orphan*/  BlinkTimer; int /*<<< orphan*/  bLedOn; void* bLedBlinkInProgress; void* bLedNoLinkBlinkInProgress; void* bLedScanBlinkInProgress; int /*<<< orphan*/  bLedWPSBlinkInProgress; TYPE_2__* padapter; } ;
struct led_priv {TYPE_3__ SwLed1; } ;
struct TYPE_9__ {int /*<<< orphan*/  rfoff_reason; int /*<<< orphan*/  rf_pwrstate; } ;
struct TYPE_10__ {TYPE_1__ pwrctrlpriv; struct mlme_priv mlmepriv; struct led_priv ledpriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  TYPE_3__* PLED_871x ;

/* Variables and functions */
 int /*<<< orphan*/  LED_BLINK_FASTER_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_LINK_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_NORMAL_INTERVAL ; 
 int /*<<< orphan*/  LED_BLINK_NO_LINK_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_SCAN_INTERVAL_ALPHA ; 
#define  LED_BLINK_SLOWLY 134 
 int /*<<< orphan*/  LED_BLINK_SLOWLY_INTERVAL ; 
#define  LED_BLINK_StartToBlink 133 
#define  LED_BLINK_WPS 132 
#define  LED_BLINK_WPS_STOP 131 
#define  LED_BLINK_WPS_STOP_OVERLAP 130 
#define  LED_SCAN_BLINK 129 
#define  LED_TXRX_BLINK 128 
 scalar_t__ LED_UNKNOWN ; 
 int /*<<< orphan*/  RF_CHANGE_BY_PS ; 
 void* RTW_LED_OFF ; 
 scalar_t__ RTW_LED_ON ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SwLedOff (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  SwLedOn (TYPE_2__*,TYPE_3__*) ; 
 void* _FALSE ; 
 void* _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl8712_led_c_ ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rf_on ; 

__attribute__((used)) static void
SwLedBlink4(
	PLED_871x			pLed
	)
{
	_adapter			*padapter = pLed->padapter;
	struct led_priv	*ledpriv = &(padapter->ledpriv);
	struct mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	PLED_871x 		pLed1 = &(ledpriv->SwLed1);	
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
		RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("Blinktimes (%d): turn off\n", pLed->BlinkTimes));
	}	

	if(!pLed1->bLedWPSBlinkInProgress && pLed1->BlinkingLedState == LED_UNKNOWN)
	{
		pLed1->BlinkingLedState = RTW_LED_OFF;
		pLed1->CurrLedState = RTW_LED_OFF;
		SwLedOff(padapter, pLed1);
	}	

	switch(pLed->CurrLedState)
	{
		case LED_BLINK_SLOWLY:			
			if( pLed->bLedOn )
				pLed->BlinkingLedState = RTW_LED_OFF; 
			else
				pLed->BlinkingLedState = RTW_LED_ON;
			_set_timer(&(pLed->BlinkTimer), LED_BLINK_NO_LINK_INTERVAL_ALPHA);
			break;

		case LED_BLINK_StartToBlink:
			if( pLed->bLedOn )
			{
				pLed->BlinkingLedState = RTW_LED_OFF;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_SLOWLY_INTERVAL);
			}
			else
			{
				pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_NORMAL_INTERVAL);
			}
			break;			
			
		case LED_SCAN_BLINK:
			pLed->BlinkTimes--;
			if( pLed->BlinkTimes == 0 )
			{
				bStopBlinking = _FALSE;
			}
			
			if(bStopBlinking)
			{
				if( padapter->pwrctrlpriv.rf_pwrstate != rf_on && padapter->pwrctrlpriv.rfoff_reason > RF_CHANGE_BY_PS)
				{
					SwLedOff(padapter, pLed);
				}
				else 
				{
					pLed->bLedNoLinkBlinkInProgress = _FALSE;
					pLed->CurrLedState = LED_BLINK_SLOWLY;
					if( pLed->bLedOn )
						pLed->BlinkingLedState = RTW_LED_OFF; 
					else
						pLed->BlinkingLedState = RTW_LED_ON;
					_set_timer(&(pLed->BlinkTimer), LED_BLINK_NO_LINK_INTERVAL_ALPHA);
				}
				pLed->bLedScanBlinkInProgress = _FALSE;
			}
			else
			{
				if( padapter->pwrctrlpriv.rf_pwrstate != rf_on && padapter->pwrctrlpriv.rfoff_reason > RF_CHANGE_BY_PS)
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
				if( padapter->pwrctrlpriv.rf_pwrstate != rf_on && padapter->pwrctrlpriv.rfoff_reason > RF_CHANGE_BY_PS)
				{
					SwLedOff(padapter, pLed);
				}
				else 
				{
					pLed->bLedNoLinkBlinkInProgress = _TRUE;
					pLed->CurrLedState = LED_BLINK_SLOWLY;
					if( pLed->bLedOn )
						pLed->BlinkingLedState = RTW_LED_OFF; 
					else
						pLed->BlinkingLedState = RTW_LED_ON;
					_set_timer(&(pLed->BlinkTimer), LED_BLINK_NO_LINK_INTERVAL_ALPHA);
				}
				pLed->bLedBlinkInProgress = _FALSE;	
			}
			else
			{
				if( padapter->pwrctrlpriv.rf_pwrstate != rf_on && padapter->pwrctrlpriv.rfoff_reason > RF_CHANGE_BY_PS)
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
			{
				pLed->BlinkingLedState = RTW_LED_OFF;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_SLOWLY_INTERVAL);
			}
			else
			{
				pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_NORMAL_INTERVAL);
			}
			break;

		case LED_BLINK_WPS_STOP:	//WPS authentication fail
			if( pLed->bLedOn )			
				pLed->BlinkingLedState = RTW_LED_OFF; 			
			else			
				pLed->BlinkingLedState = RTW_LED_ON;

			_set_timer(&(pLed->BlinkTimer), LED_BLINK_NORMAL_INTERVAL);
			break;

		case LED_BLINK_WPS_STOP_OVERLAP:	//WPS session overlap		
			pLed->BlinkTimes--;
			if(pLed->BlinkTimes == 0)
			{
				if(pLed->bLedOn)
				{
					pLed->BlinkTimes = 1;							
				}
				else
				{
					bStopBlinking = _TRUE;
				}
			}

			if(bStopBlinking)
			{				
				pLed->BlinkTimes = 10;			
				pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_LINK_INTERVAL_ALPHA);
			}
			else
			{
				if( pLed->bLedOn )			
					pLed->BlinkingLedState = RTW_LED_OFF;			
				else			
					pLed->BlinkingLedState = RTW_LED_ON;

				_set_timer(&(pLed->BlinkTimer), LED_BLINK_NORMAL_INTERVAL);
			}
			break;

					
		default:
			break;
	}

	RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("SwLedBlink4 CurrLedState %d\n", pLed->CurrLedState));


}