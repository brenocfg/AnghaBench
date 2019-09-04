#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  bBusyTraffic; } ;
struct mlme_priv {TYPE_1__ LinkDetectInfo; } ;
struct TYPE_13__ {void* bLedNoLinkBlinkInProgress; void* bLedLinkBlinkInProgress; void* bLedBlinkInProgress; void* bLedScanBlinkInProgress; int BlinkTimes; void* bLedWPSBlinkInProgress; void* CurrLedState; int /*<<< orphan*/  BlinkTimer; void* BlinkingLedState; int /*<<< orphan*/  bLedOn; } ;
struct led_priv {TYPE_3__ SwLed1; TYPE_3__ SwLed0; } ;
struct TYPE_12__ {struct mlme_priv mlmepriv; struct led_priv ledpriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_14__ {scalar_t__ EEPROMCustomerID; } ;
typedef  TYPE_3__* PLED_871x ;
typedef  int LED_CTL_MODE ;
typedef  TYPE_4__ HAL_DATA_TYPE ;

/* Variables and functions */
 TYPE_4__* GET_HAL_DATA (TYPE_2__*) ; 
 int /*<<< orphan*/  IS_LED_WPS_BLINKING (TYPE_3__*) ; 
 int /*<<< orphan*/  LED_BLINK_FASTER_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_LINK_INTERVAL_ALPHA ; 
 void* LED_BLINK_NORMAL ; 
 int /*<<< orphan*/  LED_BLINK_NO_LINK_INTERVAL_ALPHA ; 
 int /*<<< orphan*/  LED_BLINK_SCAN_INTERVAL_ALPHA ; 
 void* LED_BLINK_SLOWLY ; 
 void* LED_BLINK_WPS ; 
 void* LED_BLINK_WPS_STOP ; 
 int /*<<< orphan*/  LED_BLINK_WPS_SUCESS_INTERVAL_ALPHA ; 
#define  LED_CTL_LINK 139 
#define  LED_CTL_NO_LINK 138 
#define  LED_CTL_POWER_OFF 137 
#define  LED_CTL_POWER_ON 136 
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
SwLedControlMode1(
	_adapter		*padapter,
	LED_CTL_MODE		LedAction
)
{
	HAL_DATA_TYPE		*pHalData = GET_HAL_DATA(padapter);
	struct led_priv		*ledpriv = &(padapter->ledpriv);
	PLED_871x			pLed = &(ledpriv->SwLed0);
	struct mlme_priv		*pmlmepriv = &(padapter->mlmepriv);

	if(pHalData->EEPROMCustomerID == RT_CID_819x_CAMEO)
		pLed = &(ledpriv->SwLed1);
	
	switch(LedAction)
	{		
		case LED_CTL_POWER_ON:
		case LED_CTL_START_TO_LINK:	
		case LED_CTL_NO_LINK:
			if( pLed->bLedNoLinkBlinkInProgress == _FALSE )
			{
				if(pLed->CurrLedState == LED_SCAN_BLINK || IS_LED_WPS_BLINKING(pLed))
				{
					return;
				}
				if( pLed->bLedLinkBlinkInProgress == _TRUE )
				{
					_cancel_timer_ex(&(pLed->BlinkTimer));
					pLed->bLedLinkBlinkInProgress = _FALSE;
				}
	 			if(pLed->bLedBlinkInProgress ==_TRUE)
				{	
					_cancel_timer_ex(&(pLed->BlinkTimer));
					pLed->bLedBlinkInProgress = _FALSE;
	 			}
				
				pLed->bLedNoLinkBlinkInProgress = _TRUE;
				pLed->CurrLedState = LED_BLINK_SLOWLY;
				if( pLed->bLedOn )
					pLed->BlinkingLedState = RTW_LED_OFF; 
				else
					pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_NO_LINK_INTERVAL_ALPHA);
			}
			break;		

		case LED_CTL_LINK:
			if( pLed->bLedLinkBlinkInProgress == _FALSE )
			{
				if(pLed->CurrLedState == LED_SCAN_BLINK || IS_LED_WPS_BLINKING(pLed))
				{
					return;
				}
				if(pLed->bLedNoLinkBlinkInProgress == _TRUE)
				{
					_cancel_timer_ex(&(pLed->BlinkTimer));
					pLed->bLedNoLinkBlinkInProgress = _FALSE;
				}
				if(pLed->bLedBlinkInProgress ==_TRUE)
				{	
					_cancel_timer_ex(&(pLed->BlinkTimer));
					pLed->bLedBlinkInProgress = _FALSE;
	 			}
				pLed->bLedLinkBlinkInProgress = _TRUE;
				pLed->CurrLedState = LED_BLINK_NORMAL;
				if( pLed->bLedOn )
					pLed->BlinkingLedState = RTW_LED_OFF; 
				else
					pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_LINK_INTERVAL_ALPHA);
			}
			break;

		case LED_CTL_SITE_SURVEY:
			 if((pmlmepriv->LinkDetectInfo.bBusyTraffic) && (check_fwstate(pmlmepriv, _FW_LINKED)== _TRUE))
			 	;
			 else if(pLed->bLedScanBlinkInProgress ==_FALSE)
			 {
			 	if(IS_LED_WPS_BLINKING(pLed))
					return;
				
	  			if(pLed->bLedNoLinkBlinkInProgress == _TRUE)
				{
					_cancel_timer_ex(&(pLed->BlinkTimer));
					pLed->bLedNoLinkBlinkInProgress = _FALSE;
				}
				if( pLed->bLedLinkBlinkInProgress == _TRUE )
				{
					_cancel_timer_ex(&(pLed->BlinkTimer));
					 pLed->bLedLinkBlinkInProgress = _FALSE;
				}
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
				if(pLed->CurrLedState == LED_SCAN_BLINK || IS_LED_WPS_BLINKING(pLed))
				{
					return;
				}
				if(pLed->bLedNoLinkBlinkInProgress == _TRUE)
				{
					_cancel_timer_ex(&(pLed->BlinkTimer));
					pLed->bLedNoLinkBlinkInProgress = _FALSE;
				}
				if( pLed->bLedLinkBlinkInProgress == _TRUE )
				{
					_cancel_timer_ex(&(pLed->BlinkTimer));
					pLed->bLedLinkBlinkInProgress = _FALSE;
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

		case LED_CTL_START_WPS: //wait until xinpin finish
		case LED_CTL_START_WPS_BOTTON:
			 if(pLed->bLedWPSBlinkInProgress ==_FALSE)
			 {
				if(pLed->bLedNoLinkBlinkInProgress == _TRUE)
				{
					_cancel_timer_ex(&(pLed->BlinkTimer));
					pLed->bLedNoLinkBlinkInProgress = _FALSE;
				}
				if( pLed->bLedLinkBlinkInProgress == _TRUE )
				{
					_cancel_timer_ex(&(pLed->BlinkTimer));
					 pLed->bLedLinkBlinkInProgress = _FALSE;
				}
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
				pLed->CurrLedState = LED_BLINK_WPS;
				if( pLed->bLedOn )
					pLed->BlinkingLedState = RTW_LED_OFF; 
				else
					pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_SCAN_INTERVAL_ALPHA);
			 }
			break;

		
		case LED_CTL_STOP_WPS:
			if(pLed->bLedNoLinkBlinkInProgress == _TRUE)
			{
				_cancel_timer_ex(&(pLed->BlinkTimer));
				pLed->bLedNoLinkBlinkInProgress = _FALSE;
			}
			if( pLed->bLedLinkBlinkInProgress == _TRUE )
			{
				_cancel_timer_ex(&(pLed->BlinkTimer));
				 pLed->bLedLinkBlinkInProgress = _FALSE;
			}
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
			if(pLed->bLedWPSBlinkInProgress)
			{
				_cancel_timer_ex(&(pLed->BlinkTimer));
			}
			else
			{
				pLed->bLedWPSBlinkInProgress = _TRUE;
			}
			
			pLed->CurrLedState = LED_BLINK_WPS_STOP;
			if(pLed->bLedOn)
			{
				pLed->BlinkingLedState = RTW_LED_OFF;
				_set_timer(&(pLed->BlinkTimer), LED_BLINK_WPS_SUCESS_INTERVAL_ALPHA);
			}
			else
			{
				pLed->BlinkingLedState = RTW_LED_ON;
				_set_timer(&(pLed->BlinkTimer), 0);
			}					
			break;		

		case LED_CTL_STOP_WPS_FAIL:			
			if(pLed->bLedWPSBlinkInProgress)
			{
				_cancel_timer_ex(&(pLed->BlinkTimer));
				pLed->bLedWPSBlinkInProgress = _FALSE;				
			}			

			pLed->bLedNoLinkBlinkInProgress = _TRUE;
			pLed->CurrLedState = LED_BLINK_SLOWLY;
			if( pLed->bLedOn )
				pLed->BlinkingLedState = RTW_LED_OFF;
			else
				pLed->BlinkingLedState = RTW_LED_ON;
			_set_timer(&(pLed->BlinkTimer), LED_BLINK_NO_LINK_INTERVAL_ALPHA);
			break;				

		case LED_CTL_POWER_OFF:
			pLed->CurrLedState = RTW_LED_OFF;
			pLed->BlinkingLedState = RTW_LED_OFF; 
			if( pLed->bLedNoLinkBlinkInProgress)
			{
				_cancel_timer_ex(&(pLed->BlinkTimer));
				pLed->bLedNoLinkBlinkInProgress = _FALSE;
			}
			if( pLed->bLedLinkBlinkInProgress)
			{
				_cancel_timer_ex(&(pLed->BlinkTimer));
				pLed->bLedLinkBlinkInProgress = _FALSE;
			}
			if( pLed->bLedBlinkInProgress)
			{
				_cancel_timer_ex(&(pLed->BlinkTimer));
				pLed->bLedBlinkInProgress = _FALSE;
			}
			if( pLed->bLedWPSBlinkInProgress )
			{
				_cancel_timer_ex(&(pLed->BlinkTimer));
				pLed->bLedWPSBlinkInProgress = _FALSE;
			}
			if( pLed->bLedScanBlinkInProgress)
			{
				_cancel_timer_ex(&(pLed->BlinkTimer));
				pLed->bLedScanBlinkInProgress = _FALSE;
			}			

			SwLedOff(padapter, pLed);
			break;
			
		default:
			break;

	}

	RT_TRACE(_module_rtl8712_led_c_,_drv_info_,("Led %d\n", pLed->CurrLedState));
}